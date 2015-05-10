// SimpleTimestamp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utils.h"
#include "sha256.h"
#include "Consts.h"
//#include "HTTPHandler.h"

typedef std::codecvt_utf8<wchar_t> convert_type;
int _tmain(int argc, _TCHAR* argv[])
{

	if (argc < 2 || argc > 3)
	{
		std::cout << "invalid number of arguements.  1 arguement required." << std::endl;
		return 1;
	}
	
	std::string file;
	std::ifstream is(argv[1], std::ifstream::binary);
	if (is) {
		// get length of file:
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		char * buffer = new char[length + 1];

		std::cout << "Reading " << length << " characters...\n";
		// read data as a block:
		is.read(buffer, length);

		if (is)
			std::cout << "all characters read successfully.\n";
		else
			std::cout << "error: only " << is.gcount() << " could be read\n";
		is.close();
		buffer[length] = '\0';
		file = buffer;
		delete[] buffer;
	}


	const int totalLength = 256 / 8 + tsqFooterLength + tsqHeaderLength;
	char tsq[totalLength];

	std::memcpy(tsq, tsqHeader, tsqHeaderLength);


	hex2bin(sha256(file).c_str(), tsq + tsqHeaderLength, 64);


	std::memcpy(tsq + 256 / 8 + tsqHeaderLength, tsqFooter, tsqFooterLength);
	dumpToFile("C:\\Users\\Henry\\Desktop\\output.txt", tsq, totalLength);


	//HTTPHandler::postRequest("http://hvpn.tk/f", "fd", tsq, 1);

	std::string s;
	std::getline(std::cin, s);
}

