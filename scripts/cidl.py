#!/usr/bin/env python
#
# cidl.py - parser for a simple IDL-like language where you can
# declare only functions and constants (no interfaces, etc).
#
# Copyright (C) 2012-2013 Zeex
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import codecs
import os
import ply.lex
import ply.yacc
import sys

try:
  basestring = basestring
except NameError:
  basestring = (str,bytes)

class Value(object):
  def __init__(self, type, data):
    self._type = type
    self._data = data

  @property
  def type(self):
    return self._type

  def is_bool(self):
    return self._type == 'bool'

  def is_int(self):
    return self._type in ('dec', 'hex', 'oct')

  def is_dec(self):
    return self._type == 'dec'

  def is_hex(self):
    return self._type == 'hex'

  def is_oct(self):
    return self._type == 'oct'

  def is_float(self):
    return self._type == 'float'

  def is_char(self):
    return self._type in ('achar', 'cchar', 'uchar')

  # Printable character
  def is_pchar(self):
    return self._type == 'pchar'

  # Escape sequence
  def is_echar(self):
    return self._type == 'echar'

  # ASCII escape (\xXX)
  def is_achar(self):
    return self._type == 'achar'

  # Unicode escape (\uXXXX)
  def is_uchar(self):
    return self._type == 'uchar'

  def is_string(self):
    return self._type == 'string'

  @property
  def data(self):
    return self._data

class Attribute(object):
  def __init__(self, name, value=None):
    self._name = name
    self._value = value

  def __eq__(self, other):
    return self._name == other._name

  @property
  def name(self):
    return self._name

  @property
  def value(self):
    return self._value

  def __eq__(self, other):
    if isinstance(other, str):
      return self._name == other
    return self._name == other._name

class Parameter(object):
  def __init__(self, type, name, default=None, attrlist=None):
    self._type = type
    self._name = name
    self._default = default
    self._attrlist = attrlist

  @property
  def type(self):
    return self._type

  @property
  def name(self):
    return self._name

  @property
  def default(self):
    return self._default

  @property
  def attrs(self):
    return self._attrlist

  def has_attr(self, name):
    if self._attrlist is None:
      return False
    return Attribute(name) in self._attrlist

  def get_attr(self, name, default=None):
    if self._attrlist is None:
      return Attribute(name, default)
    try:
      return self._attrlist[self._attrlist.index(Attribute(name))]
    except ValueError:
      return Attribute(name, default)

  @property
  def is_in(self):
    return self.has_attr("in")

  @property
  def is_out(self):
    return self.has_attr("out")

  def __eq__(self, other):
    if isinstance(other, basestring):
      return self._name == other
    return self._name == other._name

class Constant(object):
  def __init__(self, type, name, value):
    self._type = type
    self._name = name
    self._value = value

  @property
  def type(self):
    return self._type

  @property
  def name(self):
    return self._name

  @property
  def value(self):
    return self._value

  def __eq__(self, other):
    if isinstance(other, basestring):
      return self._name == other
    return self._name == other._name

class NoneConstant(Constant):
  def __init__(self, name):
    super(NoneConstant, self).__init__(None, name, None)

  def __eq__(self, other):
    return super(NoneConstant, self).__eq__(other)

class Function(object):
  def __init__(self, type, name, paramlist=None, attrlist=None):
    self._attrlist = attrlist
    self._type = type
    self._name = name
    self._paramlist = paramlist

  @property
  def attrs(self):
    return self._attrlist

  @property
  def type(self):
    return self._type

  @property
  def name(self):
    return self._name

  @property
  def params(self):
    return self._paramlist

  def has_attr(self, name):
    if self._attrlist is None:
      return False
    return Attribute(name) in self._attrlist

  def get_attr(self, name, default=None):
    if self._attrlist is None:
      return Attribute(name, default)
    try:
      return self._attrlist[self._attrlist.index(Attribute(name))]
    except ValueError:
      return Attribute(name, default)

  def __eq__(self, other):
    if isinstance(other, basestring):
      return self._name == other
    return self._name == other._name

class Unit(object):
  def __init__(self, funclist, constlist):
    self._funclist = funclist
    self._constlist = constlist

  @property
  def functions(self):
    return self._funclist

  @property
  def constants(self):
    return self._constlist

class Location(object):
  def __init__(self, data, lineno, lexpos):
    self._data = data
    self._lineno = lineno
    self._lexpos = lexpos

    linestart = self._data.rfind('\n', 0, self._lexpos) + 1
    linestart = (linestart, 0)[linestart == -1]
    self._linestart = linestart

    lineend = self._data.find('\n', self._lexpos)
    lineend = (lineend, 0)[lineend == -1]
    self._lineend = lineend

  @property
  def lineno(self):
    return self._lineno

  @property
  def line(self):
    return self._data[self._linestart:self._lineend]

  @property
  def colno(self):
    return self._lexpos - self._linestart + 1

  def __str__(self):
    return '%s\n%s^' % (self.line, ' ' * (self.colno - 2))

class Error(Exception):
  def __init__(self):
    pass

class LexError(Error):
  def __init__(self, char, location):
    super(LexError, self).__init__()
    self._char = char
    self._location = location

  @property
  def char(self):
    return self._char

  @property
  def location(self):
    return self._location

  def __str__(self):
    return "Illegal character '%s' at line %d:\n%s" %  (self._char,
                                                        self._location.lineno,
                                                        self._location)

class SyntaxError(Error):
  def __init__(self, token, location):
    super(SyntaxError, self).__init__()
    self._token = token
    self._location = location

  @property
  def token(self):
    return self._token

  @property
  def location(self):
    return self._location

  def __str__(self):
    return "Syntax error in '%s' at line %d:\n%s" % (self._token,
                                                     self._location.lineno,
                                                     self._location)

class UndeclaredConstError(Error):
  def __init__(self, constname, location):
    super(UndeclaredConstError, self).__init__()
    self._constname = constname
    self._location = location

  @property
  def location(self):
    return self._location

  @property
  def constname(self):
    return self._constname

  def __str__(self):
    return "Undeclared constant '%s':\n%s" % (self._constname, self._location)

class Logger(ply.yacc.PlyLogger):
  def __init__(self):
    super(Logger, self).__init__(sys.stderr)

  def debug(self, msg, *args, **kwargs):
    pass

class Parser(object):
  keywords = {
    'const' : 'CONST',
  }

  tokens = [
    'BOOL',
    'FLOAT',
    'HEX',
    'OCT',
    'INT',
    'PCHAR',
    'ECHAR',
    'ACHAR',
    'UCHAR',
    'STRING',
    'IDENT',
    'LPAREN',
    'RPAREN',
    'LBRACKET',
    'RBRACKET',
    'EQUALS',
    'COMMA',
    'SEMICOLON',
  ] + list(keywords.values())

  def t_BOOL(self, t):
    r'(true|false)'
    if t.value =='true':
      t.value = True
    elif t.value == 'false':
      t.value = False
    return t

  def t_FLOAT(self, t):
    r'[+-]?(([0-9]*\.[0-9]*)([eE][+-]?[0-9]+)?|[0-9]+[eE][+-][0-9]+)'
    t.value = float(t.value)
    return t

  def t_HEX(self, t):
    r'0(x|X)[0-9a-fA-F]{1,8}'
    t.value = int(t.value, 16)
    return t

  def t_OCT(self, t):
    r'0[0-7]+'
    t.value = int(t.value, 8)
    return t

  def t_INT(self, t):
    r'[+-]?([1-9][0-9]+|[0-9])'
    t.value = int(t.value, 10)
    return t

  def t_PCHAR(self, t):
    r'\'[^\a\b\f\n\r\t\v]\''
    t.value = t.value[1:-1]
    return t

  def t_ECHAR(self, t):
    r'\\[abfnrtv\'"\\?]'
    t.value = codecs.decode(t.value[1:-1], 'unicode_escape')
    return t

  def t_ACHAR(self, t):
    r'\'\\x[0-9a-fA-F]{2}\''
    t.value = codecs.decode(t.value[1:-1], 'unicode_escape')
    return t

  def t_UCHAR(self, t):
    r'\'\\x[0-9a-fA-F]{4}\''
    t.value = codecs.decode(t.value[1:-1], 'unicode_escape')
    return t

  def t_STRING(self, t):
    r'\"(.|\n)*?\"'
    t.value = codecs.decode(t.value[1:-1], 'unicode_escape')
    t.lineno += t.value.count('\n')
    return t

  def t_c_comment(self, t):
    r'/\*(.|\n)*?\*/'
    t.lexer.lineno += t.value.count('\n')
    pass

  def t_cpp_comment(self, t):
    r'//[^\n\r]*'
    t.lexer.lineno += 1
    pass

  def t_newline(self, t):
    r'\n'
    t.lexer.lineno += 1
    pass

  def t_IDENT(self, t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = self.keywords.get(t.value, 'IDENT')
    return t

  t_LPAREN   = r'\('
  t_RPAREN   = r'\)'
  t_LBRACKET = r'\['
  t_RBRACKET = r'\]'

  t_EQUALS = r'='

  t_COMMA     = r','
  t_SEMICOLON = r';'

  t_ignore = ' \t'

  def t_error(self, t):
    raise LexError(t.value[0], self.get_location())

  def p_text(self, p):
    """text :
            | code"""

  def p_code(self, p):
    """code : stat SEMICOLON
            | stat SEMICOLON code"""

  def p_stat(self, p):
    """stat : decl"""

  def p_decl(self, p):
    """decl : constdecl
            | funcdecl"""

  def p_constdecl(self, p):
    """constdecl : CONST typename IDENT EQUALS constexpr"""
    p[0] = Constant(p[2], p[3], p[5])
    self._constlist.append(p[0])

  def p_constexpr(self, p):
    """constexpr : number
                 | bool
                 | char
                 | string
                 | constref"""
    p[0] = p[1]

  def p_int(self, p):
    """number : dec
              | oct
              | hex
              | float"""
    p[0] = p[1]

  def p_dec(self, p):
    """dec : INT"""
    p[0] = self._value_class('dec', p[1])

  def p_oct(self, p):
    """oct : OCT"""
    p[0] = self._value_class('oct', p[1])

  def p_hex(self, p):
    """hex : HEX"""
    p[0] = self._value_class('hex', p[1])

  def p_float(self, p):
    """float : FLOAT"""
    p[0] = self._value_class('float', p[1])

  def p_char(self, p):
    """char : pchar
            | echar
            | achar
            | uchar """
    p[0] = p[1]

  def p_pchar(self, p):
    """pchar : PCHAR"""
    p[0] = self._value_class('pchar', p[1])

  def p_echar(self, p):
    """echar : ECHAR"""
    p[0] = self._value_class('echar', p[1])

  def p_achar(self, p):
    """achar : ACHAR"""
    p[0] = self._value_class('achar', p[1])

  def p_uchar(self, p):
    """uchar : UCHAR"""
    p[0] = self._value_class('uchar', p[1])

  def p_bool(self, p):
    """bool : BOOL"""
    p[0] = self._value_class('bool', p[1])

  def p_string(self, p):
    """string : STRING"""
    p[0] = self._value_class('string', p[1])

  def p_constref(self, p):
    """constref : IDENT"""
    if not NoneConstant(p[1]) in self._constlist:
       raise UndeclaredConstError(p[1], self.get_location())
    p[0] = p[1]

  def p_funcdecl(self, p):
    """funcdecl :       typename IDENT params
                | attrs typename IDENT params"""
    if len(p) == 4:
      p[0] = self._func_class(p[1], p[2], p[3])
    else:
      p[0] = self._func_class(p[2], p[3], p[4], p[1])
    self._funclist.append(p[0])

  def p_attrs(self, p):
    """attrs : LBRACKET attrlist RBRACKET"""
    p[0] = p[2]
    self._attrlist = []

  def p_attrlist(self, p):
    """attrlist : attr
                | attr COMMA attrlist"""
    p[0] = self._attrlist

  def p_attr(self, p):
    """attr : IDENT
            | IDENT LPAREN constexpr RPAREN"""
    if len(p) == 2:
      p[0] = self._attr_class(p[1], None)
    else:
      p[0] = self._attr_class(p[1], p[3])
    self._attrlist.append(p[0])

  def p_params(self, p):
    """params : LPAREN paramlist RPAREN"""
    p[0] = p[2]
    self._paramlist = []

  def p_paramlist(self, p):
    """paramlist :
                 | param
                 | param COMMA paramlist"""
    p[0] = self._paramlist

  def p_param(self, p):
    """param :       typename IDENT
             |       typename IDENT EQUALS constexpr
             | attrs typename IDENT
             | attrs typename IDENT EQUALS constexpr"""
    if len(p) == 3:
      p[0] = self._param_class(p[1], p[2])
    elif len(p) == 5:
      p[0] = self._param_class(p[1], p[2], default=p[4])
    elif len(p) == 4:
      p[0] = self._param_class(p[2], p[3], attrlist=p[1])
    elif len(p) == 6:
      p[0] = self._param_class(p[2], p[3], default=p[5], attrlist=p[1])
    self._paramlist.append(p[0])

  def p_typename(self, p):
    """typename : IDENT"""
    p[0] = p[1]

  def p_error(self, p):
    raise SyntaxError(p.value, self.get_location())

  def __init__(self, value_class=Value,
                     attr_class=Attribute,
                     param_class=Parameter,
                     func_class=Function,
                     const_class=Constant,
  ):
    self._value_class = value_class
    self._attr_class = attr_class
    self._param_class = param_class
    self._func_class = func_class
    self._const_class = const_class

    self._data = None
    self._paramlist = []
    self._attrlist = []
    self._constlist = []
    self._funclist = []

    self._lexer = ply.lex.lex(
      object=self,
      optimize=True,
      lextab='cidl_lextab'
    )

    self._parser = ply.yacc.yacc(
      module=self,
      errorlog=Logger(),
      debugfile='cidl_parser.out',
      tabmodule='cidl_parsetab'
    )

  def token(self):
    return self._lexer.token()

  def parse(self, data):
    self._data = data
    self._lexer.lineno = 1
    self._lexer.input(data)
    self._parser.parse(lexer=self)
    return Unit(self._funclist, self._constlist)

  def get_location(self):
    return Location(self._data, self._lexer.lineno, self._lexer.lexpos)

if __name__ == '__main__':
  parser = Parser()
  for f in sys.argv[1:]:
    print('Parsing \'%s\'...'  % f)
    try:
      unit = parser.parse(open(f).read())
    except Error as e:
      print(e)
