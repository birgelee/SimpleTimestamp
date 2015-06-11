#include "stdafx.h"
#include "Utils.h"

#include <Windows.h>
#include <algorithm>
#include <stdexcept>

typedef std::codecvt_utf8<wchar_t> convert_type;
std::wstring_convert<convert_type, wchar_t> converter;
std::string convert_wstring(std::wstring str)
{
	return converter.to_bytes(str);
}
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter2;
std::wstring convert_string(std::string str)
{
	return converter2.from_bytes(str);
}


void dumpToFile(std::string filePath, const char* data, int len)
{
	wchar_t fpb[FILENAME_MAX];
	int newPathLength = ExpandEnvironmentStrings(convert_string(filePath).c_str(), fpb, FILENAME_MAX);
	std::wstring wnewFilePath(fpb, newPathLength);
	std::string newFilePath(convert_wstring(wnewFilePath));
	std::ofstream myfile(newFilePath, std::ofstream::binary);

	std::string dataStr = { data, (size_t) len };
	if (myfile.is_open())
	{
		myfile << dataStr;
		myfile.close();
	}
	else std::cout << "Unable to open file";
}



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void rmFile(const std::string& filePath)
{
	wchar_t fpb[FILENAME_MAX];
	int newPathLength = ExpandEnvironmentStrings(convert_string(filePath).c_str(), fpb, FILENAME_MAX);
	std::wstring wnewFilePath(fpb, newPathLength);
	std::string newPath(convert_wstring(wnewFilePath));
	std::remove(newPath.c_str());
}

template<typename T, typename P> T remove_if01(T beg, T end, P pred)
{
	T dest = beg;
	for (T itr = beg; itr != end; ++itr)
		if (!pred(*itr))
			*(dest++) = *itr;
	return dest;
}

void trim(std::string& s)
{
	s.erase(remove_if01(s.begin(), s.end(), isspace), s.end());
}

void removeWhiteSpaceOrHyphen(std::string& s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] == ' ' || s[i] == '-') {
			s.erase(i, 1);
			i--;
		}
	}
}

std::string readFile(const std::string& filePath)
{

	wchar_t fpb[FILENAME_MAX];
	int newPathLength = ExpandEnvironmentStrings(convert_string(filePath).c_str(), fpb, FILENAME_MAX);
	std::wstring wnewFilePath(fpb, newPathLength);
	std::string newPath(convert_wstring(wnewFilePath));

	std::ifstream is(newPath, std::ifstream::binary);
	if (is) {
		// get length of file:
		is.seekg(0, is.end);
		unsigned int length = (unsigned int) is.tellg();
		is.seekg(0, is.beg);

		char * buffer = new char[length];

		//std::cout << "Reading " << length << " characters...\n";
		// read data as a block:
		is.read(buffer, length);

		if (!is)
			std::cout << "error: only " << is.gcount() << " could be read\n";
		is.close();
		std::string file(buffer, length);
		delete[] buffer;
		return file;
	}
	return NULL;
}

bool file_exists(const std::string& fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}


std::string string_to_hex(const std::string& input)
{
	static const char* const lut = "0123456789abcdef";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}


std::string hex_to_string(const std::string& input)
{
	static const char* const lut = "0123456789abcdef";
	size_t len = input.length();
	if (len & 1) throw std::invalid_argument("odd length");

	std::string output;
	output.reserve(len / 2);
	for (size_t i = 0; i < len; i += 2)
	{
		char a = input[i];
		const char* p = std::lower_bound(lut, lut + 16, a);
		if (*p != a) throw std::invalid_argument("not a hex digit");

		char b = input[i + 1];
		const char* q = std::lower_bound(lut, lut + 16, b);
		if (*q != b) throw std::invalid_argument("not a hex digit");

		output.push_back(((p - lut) << 4) | (q - lut));
	}
	return output;
}