#include "stdafx.h"
#include "HTTPHandler.h"
#include "Utils.h"

HTTPHandler::HTTPHandler()
{
}


HTTPHandler::~HTTPHandler()
{
}

//Valid powershell command to do thing.
/*
PS C:\cygwin64\home\Henry> curl -H @{"Content-Type"="application/timestamp-query"} –InFile request2.tsq -OutFile data.tsr -Method POST “http://timestamp.globalsign.com/scripts/timestamp.dll”
*/

void HTTPHandler::postRequest(std::string url, std::string additionalHeader, char* bodyData, int bodyLength)
{
	system("cmd /C powershell curl -H @{\"Content-Type\"=\"application/timestamp-query\"} –InFile request2.tsq -OutFile data.tsr -Method POST \"http://timestamp.globalsign.com/scripts/timestamp.dll\"");
}