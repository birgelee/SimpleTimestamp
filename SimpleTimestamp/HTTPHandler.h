#pragma once
class HTTPHandler
{
public:
	HTTPHandler();
	~HTTPHandler();
	static void postRequest(std::string url, char* bodyData, int bodyLength);
};

