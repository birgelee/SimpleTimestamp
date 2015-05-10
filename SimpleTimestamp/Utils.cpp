#include "stdafx.h"




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



int char2int(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	std::cout << "Invalid hex string.\n";
	return -1;
}

// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters, and target to be sufficiently large
void hex2bin(const char* src, char* target, int size)
{
	if (size % 2 != 0) {
		std::cout << "Hex string can not be odd number of chars.\n";
		return;
	}
	const char* originalScr = src;
	while (src - originalScr < size)
	{
		*(target++) = char2int(*src) * 16 + char2int(src[1]);
		src += 2;
	}
}


void dumpToFile(std::string filePath, const char* data, int len)
{
	std::ofstream myfile(filePath);
	if (myfile.is_open())
	{
		myfile.write(data, len);
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