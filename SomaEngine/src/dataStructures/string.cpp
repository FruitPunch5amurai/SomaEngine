#include "somapch.hpp"


#include <fstream>

SOMA_Array<SOMA_String> StringFuncs::split(const SOMA_String& s, char delim)
{
	SOMA_Array<SOMA_String> elems;

	const char* cstr = s.c_str();
	unsigned int strLength = (unsigned int)s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength) {
		while (end <= strLength) {
			if (cstr[end] == delim) {
				break;
			}
			end++;
		}

		elems.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return elems;
}

SOMA_String StringFuncs::getFilePath(const SOMA_String& fileName)
{
	const char* cstr = fileName.c_str();
	unsigned int strLength = (unsigned int)fileName.length();
	unsigned int end = strLength - 1;

	while (end != 0) {
		if (cstr[end] == '/') {
			break;
		}
		end--;
	}

	if (end == 0) {
		return fileName;
	}
	else {
		unsigned int start = 0;
		end = end + 1;
		return fileName.substr(start, end - start);
	}
}

SOMA_String StringFuncs::getFileName(const SOMA_String& filePath)
{
	const char* cstr = filePath.c_str();
	unsigned int strLength = (unsigned int)filePath.length();
	unsigned int end = strLength - 1;
	unsigned int trueEnd = end;

	while (end != 0) {
		if (cstr[end] == '/') {
			break;
		}
		if (cstr[end] == '.')
			trueEnd = end;
		end--;
	}

	if (end == 0) {
		return filePath;
	}
	else {
		end++;
		return filePath.substr(end, (strLength - 1 - end) - (strLength - 1 - trueEnd));
	}
}

bool StringFuncs::loadTextFileWithIncludes(SOMA_String& output, const SOMA_String& fileName,
	const SOMA_String& includeKeyword)
{
	std::ifstream file;
	file.open(fileName.c_str());

	SOMA_String filePath = getFilePath(fileName);
	std::stringstream ss;
	SOMA_String line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);

			if (line.find(includeKeyword) == SOMA_String::npos) {
				ss << line << "\n";
			}
			else {
				SOMA_String includeFileName = StringFuncs::split(line, ' ')[1];
				includeFileName =
					includeFileName.substr(1, includeFileName.length() - 2);

				SOMA_String toAppend;
				loadTextFileWithIncludes(toAppend, filePath + includeFileName,
					includeKeyword);
				ss << toAppend << "\n";
			}
		}
	}
	else {
		DEBUG_LOG(LOG_TYPE_IO, LOG_ERROR, "Unable to load shader: %s",
			fileName.c_str());
		return false;
	}

	output = ss.str();
	return true;
}