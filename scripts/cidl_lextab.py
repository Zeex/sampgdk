# cidl_lextab.py. This file automatically created by PLY (version 3.11). Don't edit!
_tabversion   = '3.10'
_lextokens    = set(('ACHAR', 'BOOL', 'COMMA', 'CONST', 'ECHAR', 'EQUALS', 'FLOAT', 'HEX', 'IDENT', 'INT', 'LBRACKET', 'LPAREN', 'OCT', 'PCHAR', 'RBRACKET', 'RPAREN', 'SEMICOLON', 'STRING', 'UCHAR'))
_lexreflags   = 64
_lexliterals  = ''
_lexstateinfo = {'INITIAL': 'inclusive'}
_lexstatere   = {'INITIAL': [('(?P<t_BOOL>(true|false))|(?P<t_FLOAT>[+-]?(([0-9]*\\.[0-9]*)([eE][+-]?[0-9]+)?|[0-9]+[eE][+-][0-9]+))|(?P<t_HEX>0(x|X)[0-9a-fA-F]{1,8})|(?P<t_OCT>0[0-7]+)|(?P<t_INT>[+-]?([1-9][0-9]+|[0-9]))|(?P<t_PCHAR>\\\'[^\\a\\b\\f\\n\\r\\t\\v]\\\')|(?P<t_ECHAR>\\\\[abfnrtv\\\'"\\\\?])|(?P<t_ACHAR>\\\'\\\\x[0-9a-fA-F]{2}\\\')|(?P<t_UCHAR>\\\'\\\\x[0-9a-fA-F]{4}\\\')|(?P<t_STRING>\\"(.|\\n)*?\\")|(?P<t_c_comment>/\\*(.|\\n)*?\\*/)|(?P<t_cpp_comment>//[^\\n\\r]*)|(?P<t_newline>\\n)|(?P<t_IDENT>[a-zA-Z_][a-zA-Z_0-9]*)|(?P<t_LPAREN>\\()|(?P<t_LBRACKET>\\[)|(?P<t_RBRACKET>\\])|(?P<t_RPAREN>\\))|(?P<t_COMMA>,)|(?P<t_EQUALS>=)|(?P<t_SEMICOLON>;)', [None, ('t_BOOL', 'BOOL'), None, ('t_FLOAT', 'FLOAT'), None, None, None, ('t_HEX', 'HEX'), None, ('t_OCT', 'OCT'), ('t_INT', 'INT'), None, ('t_PCHAR', 'PCHAR'), ('t_ECHAR', 'ECHAR'), ('t_ACHAR', 'ACHAR'), ('t_UCHAR', 'UCHAR'), ('t_STRING', 'STRING'), None, ('t_c_comment', 'c_comment'), None, ('t_cpp_comment', 'cpp_comment'), ('t_newline', 'newline'), ('t_IDENT', 'IDENT'), (None, 'LPAREN'), (None, 'LBRACKET'), (None, 'RBRACKET'), (None, 'RPAREN'), (None, 'COMMA'), (None, 'EQUALS'), (None, 'SEMICOLON')])]}
_lexstateignore = {'INITIAL': ' \t'}
_lexstateerrorf = {'INITIAL': 't_error'}
_lexstateeoff = {}
