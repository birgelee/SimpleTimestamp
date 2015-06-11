#include "stdafx.h"
#include "TimestampHandler.h"
#include "base64.h"
#include "sha256.h"
#include <stdio.h>
#include <algorithm>

std::string getTagContense(const std::string& file, const std::string& startTag, const std::string& endTag);
std::string validateTsq(const std::string& path, const std::string& osslPath, std::string& responseText, std::string& dateTimestampped);

std::wstring GetTimestampResponseString(std::wstring path) {
	std::stringstream res;

	std::string nPath = convert_wstring(path);
	int last = nPath.find_last_of('\\');
	std::string nPathPrefix = nPath.substr(0, last);
	std::string file = readFile(nPath);

	std::string fileName = getTagContense(file, "<file>", "</file>");
	std::stringstream comp;
	comp << nPathPrefix << "\\" << fileName;

	std::string stamppedFilePath = comp.str();
	std::string stampedFile;
	std::string givenSha256;
	if (file_exists(stamppedFilePath)) {
		res << "File Status: Found                  (Good)" << std::endl;
		stampedFile = readFile(stamppedFilePath);
		givenSha256 = getTagContense(file, "<sha256>", "</sha256>");
	}
	else {
		stampedFile = "";
		givenSha256 = "";
		res << "File Status: Not Found              (Fail)" << std::endl;
	}

	

	std::string originalTimestamp = base64_decode(getTagContense(file, "<base64_data>", "</base64_data>"));
	dumpToFile("%TEMP%\\timestampresponse.tsr", originalTimestamp.c_str(), originalTimestamp.length());
	std::string tsqResult, dateTimestampped;
	std::string sha256Res = validateTsq("%TEMP%\\timestampresponse.tsr", "C:\\Users\\Henry\\Desktop\\openssl-1.0.2a-i386-win32\\openssl.exe", tsqResult, dateTimestampped);
	res << tsqResult << std::endl;
	rmFile("%TEMP%\\timestampresponse.tsr");

	std::string fileSha256 = sha256(stampedFile);
	std::transform(fileSha256.begin(), fileSha256.end(), fileSha256.begin(), ::tolower);
	if (givenSha256 == sha256Res || sha256Res == fileSha256) {
		res << "File Contense: Verified           (Good)" << std::endl;
	}
	else {
		res << "File Contense: Invalid            (Fail)" << std::endl;
	}

	res << "Time Given: " << dateTimestampped << std::endl;
	return convert_string(res.str());
}

std::string getTagContense(const std::string& file, const std::string& startTag, const std::string& endTag) {
	int startx = file.find(startTag) + startTag.length();
	std::string res = file.substr(startx, file.find(endTag) - startx);
	trim(res);
	return res;
}

std::string validateTsq(const std::string& path, const std::string& osslPath, std::string& responseText, std::string& dateTimestampped) {
	
	if (!file_exists(osslPath)) {
		responseText = "Error: Could not find open ssl binary.";
		return "";
	}
	
	std::stringstream cmd;
	cmd << "cmd /C echo \"" << osslPath << "\" ts -reply -in \"" << path << "\" -text | cmd > %TEMP%\\tsout.txt" << '\0';
	
	system(cmd.str().c_str());


	std::string cmdOut = readFile("%TEMP%\\tsout.txt");
	rmFile("%TEMP%\\tsout.txt");


	int index1 = cmdOut.find("TSA: DirName:/C=SG/O=GMO GlobalSign Pte Ltd/CN=GlobalSign TSA for Standard - G2"),
		index2 = cmdOut.find("Status: Granted."),
		index3 = cmdOut.find("Failure info: unspecified");
	

	if (index1 == -1 || index2 == -1 || index3 == -1) {
		responseText = "Timestamp Status: Invalid     (Fail)";
	}
	else {
		responseText = "Timestamp Status: Valid        (Good)";
	}

	int dateStartx = cmdOut.find("Time stamp: ") + 12;
	int dateEndx = cmdOut.find("\n", dateStartx);
	dateTimestampped = cmdOut.substr(dateStartx, dateEndx - dateStartx);

	std::ostringstream sha256Hex;

	int shaStartx = cmdOut.find("0000 - ") + 7;
	int shaEndx = cmdOut.find("   ", shaStartx);
	sha256Hex << cmdOut.substr(shaStartx, shaEndx - shaStartx);

	shaStartx = cmdOut.find("0010 - ") + 7;
	shaEndx = cmdOut.find("   ", shaStartx);
	sha256Hex << cmdOut.substr(shaStartx, shaEndx - shaStartx);
	std::string sha256HexString = sha256Hex.str();
	removeWhiteSpaceOrHyphen(sha256HexString);
	//std::string sha256Bin = hex_to_string(sha256HexString);

	return sha256HexString;
}