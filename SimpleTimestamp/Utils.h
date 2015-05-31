#pragma once
std::string convert_wstring(std::wstring str);

std::wstring convert_string(std::string str);

void hex2bin(const char* src, char* target, int size);

void dumpToFile(std::string filePath, const char* data, int len);

std::vector<std::string> split(const std::string &s, char delim);

void rmFile(const std::string& filePath);

std::string readFile(const std::string& filePath);