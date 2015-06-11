#pragma once
#include "stdafx.h"
std::string convert_wstring(std::wstring str);

std::wstring convert_string(std::string str);

void dumpToFile(std::string filePath, const char* data, int len);

std::vector<std::string> split(const std::string &s, char delim);

void rmFile(const std::string& filePath);

std::string readFile(const std::string& filePath);

void trim(std::string& s);

void removeWhiteSpaceOrHyphen(std::string& s);

bool file_exists(const std::string& fileName);

std::string string_to_hex(const std::string& input);

std::string hex_to_string(const std::string& input);