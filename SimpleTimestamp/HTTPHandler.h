#pragma once
class HTTPHandler
{
public:
	HTTPHandler();
	~HTTPHandler();
	static void postRequest(std::string url, std::string additionalHeader, char* bodyData, int bodyLength);
};

