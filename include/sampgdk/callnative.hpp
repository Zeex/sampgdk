// Copyright (C) 2013 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SAMPGDK_CALLNATIVE_HPP
#define SAMPGDK_CALLNATIVE_HPP

#include <string>

#include <sampgdk/amx.h>

template<typename T>
class NativeArgument {
public:
	NativeArgument(AMX *amx, cell x) {
		amx_Push(amx, x);
	}
};

template<>
class NativeArgument<float> {
public:
	NativeArgument(AMX *amx, float x) {
		amx_Push(amx, amx_ftoc(x));
	}
};

template<>
class NativeArgument<const char *> {
public:
	NativeArgument(AMX *amx, const char *s) : amx_(amx) {
		amx_PushString(amx, &address_, 0, s, 0, 0);
	}
	~NativeArgument() {
		amx_Release(amx_, address_);
	}
private:
	AMX *amx_;
	cell address_;
};

template<>
class NativeArgument<std::string> {
public:
	NativeArgument(AMX *amx, std::string s) : amx_(amx) {
		amx_PushString(amx, &address_, 0, s.c_str(), 0, 0);
	}
	~NativeArgument() {
		amx_Release(amx_, address_);
	}
private:
	AMX *amx_;
	cell address_;
};

template<typename T>
struct ConvertCell {
};

template<>
struct ConvertCell<void> {
	static cell Convert(cell x) {
		return 0;
	}
};

template<>
struct ConvertCell<cell> {
	static cell Convert(cell x) {
		return x;
	}
};

template<>
struct ConvertCell<bool> {
	static bool Convert(cell x) {
		return x != 0;
	}
};

template<>
struct ConvertCell<float> {
	static float Convert(cell x) {
		return amx_ctof(x);
	}
};

template<typename R>
R DoCallNative(AMX *amx, AMX_NATIVE native, int num_params) {
	int params_size = num_params * sizeof(cell);
	amx_Push(amx, params_size);

	cell *params;
	amx_GetAddr(amx, amx->stk, &params);

	amx->paramcount = 0;

	cell retval = native(amx, params);
	amx->stk += params_size + sizeof(cell);

	return ConvertCell<R>::Convert(retval);
}

template<typename R>
R CallNative(AMX *amx, AMX_NATIVE native) {
	return DoCallNative<R>(amx, native, 0);
}

template<typename R, typename T1>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1) {
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 1);
}

template<typename R, typename T1, typename T2>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2) {
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 2);
}

template<typename R, typename T1, typename T2, typename T3>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3) {
	NativeArgument<T3> a3(amx, x3);
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 3);
}

template<typename R, typename T1, typename T2, typename T3, typename T4>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4) {
	NativeArgument<T4> a4(amx, x4);
	NativeArgument<T3> a3(amx, x3);
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 4);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5) {
	NativeArgument<T5> a5(amx, x5);
	NativeArgument<T4> a4(amx, x4);
	NativeArgument<T3> a3(amx, x3);
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 5);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6) {
	NativeArgument<T6> a6(amx, x6);
	NativeArgument<T5> a5(amx, x5);
	NativeArgument<T4> a4(amx, x4);
	NativeArgument<T3> a3(amx, x3);
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 6);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7) {
	NativeArgument<T7> a7(amx, x7);
	NativeArgument<T6> a6(amx, x6);
	NativeArgument<T5> a5(amx, x5);
	NativeArgument<T4> a4(amx, x4);
	NativeArgument<T3> a3(amx, x3);
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 7);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7, T8 x8) {
	NativeArgument<T8> a8(amx, x8);
	NativeArgument<T7> a7(amx, x7);
	NativeArgument<T6> a6(amx, x6);
	NativeArgument<T5> a5(amx, x5);
	NativeArgument<T4> a4(amx, x4);
	NativeArgument<T3> a3(amx, x3);
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 8);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7, T8 x8, T9 x9) {
	NativeArgument<T9> a9(amx, x8);
	NativeArgument<T8> a8(amx, x8);
	NativeArgument<T7> a7(amx, x7);
	NativeArgument<T6> a6(amx, x6);
	NativeArgument<T5> a5(amx, x5);
	NativeArgument<T4> a4(amx, x4);
	NativeArgument<T3> a3(amx, x3);
	NativeArgument<T2> a2(amx, x2);
	NativeArgument<T1> a1(amx, x1);
	return DoCallNative<R>(amx, native, 9);
}

#endif // !SAMPGDK_CALLNATIVE_HPP
