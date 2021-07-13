#pragma once

#include <string>

#include "core/common.hpp"
#include "array.hpp"

#define SOMA_String std::string

struct StringFuncs
{
	template<typename T>
	static inline SOMA_String toString(T val)
	{
		std::ostringstream convert;
		convert << val;
		return convert.str();
	}

	static SOMA_Array<SOMA_String> split(const SOMA_String& s, char delim);
	static SOMA_String getFilePath(const SOMA_String& fileName);
	static bool loadTextFileWithIncludes(SOMA_String& output, const SOMA_String& fileName,
		const SOMA_String& includeKeyword);
};