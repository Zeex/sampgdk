# Copyright (C) 2012 Zeex
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

import cidl

cidl_to_c_type_in = {
	'int'    : 'int',
	'bool'   : 'bool',
	'float'  : 'float',
	'char'   : 'char',
	'string' : 'const char *'
}

cidl_to_c_type_out = {
	'int'    : 'int *',
	'bool'   : 'bool *',
	'float'  : 'float *',
	'char'   : 'char *',
	'string' : 'char **'
}

def value_to_c_literal(v):
	if v.is_bool():
		return ('false', 'true')[v.data]
	elif v.is_int():
		if v.is_hex():
			return '0x%s' % hex(v.data)[2:].upper()
		elif v.is_oct():
			return oct(v.data)
		return int(v.data)
	elif v.is_char():
		return '\'%s\'' % v.data
	elif v.is_string():
		return '"%s"' % v.data
	return None

def get_param_c_type(p):
	if p.is_in():
		return cidl_to_c_type_in[p.type]
	elif p.is_out():
		return cidl_to_c_type_out[p.type]
	return None

def params_to_string(params):
	return ', '.join(['%s %s' % (get_param_c_type(p), p.name) for p in params])

def params_to_string_no_type(params):
	return ', '.join(['%s' % p.name for p in params])

def is_out_param(p):
	return p.is_out()

def is_ref_param(p):
	return is_out_param(p) or p.type == 'string'

def is_value_param(p):
	return not is_ref_param(p)
