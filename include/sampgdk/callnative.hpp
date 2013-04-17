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

namespace sampgdk {

class NativeCaller {
public:
	template<typename T> class Arg {
	public:
		Arg(AMX *amx, cell x) {
			amx_Push(amx, x);
		}
	};

	template<> class Arg<float> {
	public:
		Arg(AMX *amx, float x) {
			amx_Push(amx, amx_ftoc(x));
		}
	};

	template<> class Arg<const char *> {
	public:
		Arg(AMX *amx, const char *s) : amx_(amx) {
			amx_PushString(amx, &address_, 0, s, 0, 0);
		}
		~Arg() {
			amx_Release(amx_, address_);
		}
	private:
		AMX *amx_;
		cell address_;
	};

	template<> class Arg<std::string> {
	public:
		Arg(AMX *amx, std::string s) : amx_(amx) {
			amx_PushString(amx, &address_, 0, s.c_str(), 0, 0);
		}
		~Arg() {
			amx_Release(amx_, address_);
		}
	private:
		AMX *amx_;
		cell address_;
	};

	template<typename T> struct ConvertCell {};

	template<> struct ConvertCell<void> {
		static cell Convert(cell x) { return 0; }
	};

	template<> struct ConvertCell<cell> {
		static cell Convert(cell x) { return x; }
	};

	template<> struct ConvertCell<bool> {
		static bool Convert(cell x) { return x != 0; }
	};

	template<> struct ConvertCell<float> {
		static float Convert(cell x) { return amx_ctof(x); }
	};

	template<typename R>
	static R Call(AMX *amx, AMX_NATIVE native, int num_params) {
		int params_size = num_params * sizeof(cell);
		amx_Push(amx, params_size);

		cell *params;
		amx_GetAddr(amx, amx->stk, &params);

		amx->paramcount = 0;

		cell retval = native(amx, params);
		amx->stk += params_size + sizeof(cell);

		return ConvertCell<R>::Convert(retval);
	}
};

template<typename R>
R CallNative(AMX *amx, AMX_NATIVE native) {
	return NativeCaller::Call<R>(amx, native, 0);
}

template<typename R, typename T1>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1) {
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 1);
}

template<typename R, typename T1, typename T2>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2) {
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 2);
}

template<typename R, typename T1, typename T2, typename T3>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3) {
	NativeCaller::Arg<T3> a3(amx, x3);
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 3);
}

template<typename R, typename T1, typename T2, typename T3, typename T4>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4) {
	NativeCaller::Arg<T4> a4(amx, x4);
	NativeCaller::Arg<T3> a3(amx, x3);
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 4);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5) {
	NativeCaller::Arg<T5> a5(amx, x5);
	NativeCaller::Arg<T4> a4(amx, x4);
	NativeCaller::Arg<T3> a3(amx, x3);
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 5);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6) {
	NativeCaller::Arg<T6> a6(amx, x6);
	NativeCaller::Arg<T5> a5(amx, x5);
	NativeCaller::Arg<T4> a4(amx, x4);
	NativeCaller::Arg<T3> a3(amx, x3);
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 6);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7) {
	NativeCaller::Arg<T7> a7(amx, x7);
	NativeCaller::Arg<T6> a6(amx, x6);
	NativeCaller::Arg<T5> a5(amx, x5);
	NativeCaller::Arg<T4> a4(amx, x4);
	NativeCaller::Arg<T3> a3(amx, x3);
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 7);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7, T8 x8) {
	NativeCaller::Arg<T8> a8(amx, x8);
	NativeCaller::Arg<T7> a7(amx, x7);
	NativeCaller::Arg<T6> a6(amx, x6);
	NativeCaller::Arg<T5> a5(amx, x5);
	NativeCaller::Arg<T4> a4(amx, x4);
	NativeCaller::Arg<T3> a3(amx, x3);
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 8);
}

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
R CallNative(AMX *amx, AMX_NATIVE native, T1 x1, T2 x2, T3 x3, T4 x4, T5 x5, T6 x6, T7 x7, T8 x8, T9 x9) {
	NativeCaller::Arg<T9> a9(amx, x8);
	NativeCaller::Arg<T8> a8(amx, x8);
	NativeCaller::Arg<T7> a7(amx, x7);
	NativeCaller::Arg<T6> a6(amx, x6);
	NativeCaller::Arg<T5> a5(amx, x5);
	NativeCaller::Arg<T4> a4(amx, x4);
	NativeCaller::Arg<T3> a3(amx, x3);
	NativeCaller::Arg<T2> a2(amx, x2);
	NativeCaller::Arg<T1> a1(amx, x1);
	return NativeCaller::Call<R>(amx, native, 9);
}

} // namespace sampgdk

#endif // !SAMPGDK_CALLNATIVE_HPP
