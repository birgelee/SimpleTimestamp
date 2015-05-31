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

cmd one command version
cmd /C echo curl -H @{"Content-Type"="application/timestamp-query"} -InFile request2.tsq -OutFile data.tsr -Method POST "http://timestamp.globalsign.com/scripts/timestamp.dll"  | PowerShell.exe -noprofile -
*/

void HTTPHandler::postRequest(std::string url, char* bodyData, int bodyLength)
{
	dumpToFile("%TEMP%\\request.tsq", bodyData, bodyLength);
	std::stringstream st;
	st << "cmd /C echo curl -H @{\"Content-Type\"=\"application/timestamp-query\"} -InFile $env:temp\\request.tsq -OutFile $env:temp\\response.tsr -Method POST \"";
	st << url;
	st << "\"  | PowerShell.exe -noprofile -";
	system(st.str().c_str());

	rmFile("%TEMP%\\request.tsq");
}