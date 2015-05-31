// SimpleTimestamp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utils.h"
#include "sha256.h"
#include "Consts.h"
#include "HTTPHandler.h"
#include "base64.h"

//#include "HTTPHandler.h"

typedef std::codecvt_utf8<wchar_t> convert_type;
int _tmain(int argc, _TCHAR* argv[])
{

	if (argc < 2 || argc > 3)
	{
		std::cout << "invalid number of arguements.  1 arguement required." << std::endl;
		return 1;
	}
	std::string file = readFile(convert_wstring(argv[1]));

	const int totalLength = 256 / 8 + tsqFooterLength + tsqHeaderLength;
	char tsq[totalLength];

	std::memcpy(tsq, tsqHeader, tsqHeaderLength);


	hex2bin(sha256(file).c_str(), tsq + tsqHeaderLength, 64);


	std::memcpy(tsq + 256 / 8 + tsqHeaderLength, tsqFooter, tsqFooterLength);
	

	HTTPHandler::postRequest("http://timestamp.globalsign.com/scripts/timestamp.dll", tsq, totalLength);

	std::string response = readFile("%TEMP%\\response.tsr");
	rmFile("%TEMP%\\response.tsr");
	
	std::string b64 = base64_encode((unsigned char*) response.c_str(), response.length());
	std::vector<std::string> infileparts = split(convert_wstring(argv[1]), '\\');
	std::string inFileName = infileparts[infileparts.size() - 1];

	std::stringstream outFile;
	outFile << "<base64_data>\n";
	outFile << b64;
	outFile << "\n</base64_data>\n";
	outFile << "<file>\n";
	outFile << inFileName;
	outFile << "\n</file>\n";
	outFile << "<sha256>\n";
	outFile << sha256(file);
	outFile << "\n</sha256>\n";

	std::stringstream outFileName;
	outFileName << ".\\" << inFileName << ".sts";
	dumpToFile(outFileName.str(), outFile.str().c_str(), outFile.str().length());



	//std::string s;
	//std::getline(std::cin, s);
}

