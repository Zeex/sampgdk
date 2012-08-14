// Copyright (C) 2012, Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>

#include <sampgdk/config.h>
#include <sampgdk/amx.h>

#include "util.h"

namespace {

inline unsigned char *GetAmxDataPtr(AMX *amx) {
	unsigned char *dataPtr = amx->data;
	if (dataPtr == 0) {
		AMX_HEADER *hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
		dataPtr = amx->base + hdr->dat;
	}
	return dataPtr;
}

} // namespace

namespace sampgdk {
namespace util {

cell AmxStackReader::GetCell(int index) const {
	cell *stackPtr = reinterpret_cast<cell*>(GetAmxDataPtr(amx_) + amx_->stk);
	return stackPtr[index];
}

std::string AmxStackReader::GetString(int index) const {
	cell address = GetCell(index);
	cell *stringPtr = reinterpret_cast<cell*>(GetAmxDataPtr(amx_) + address);

	std::string string;
	for (cell c; (c = *stringPtr) != '\0'; stringPtr++) {
		string.push_back(static_cast<char>(c & 0xFF));
	}

	return string;
}

} // namespace util
} // namespace sampgdk
