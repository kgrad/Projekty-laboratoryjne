#pragma once
#include <string>
#include "asio.hpp"

class Client
{
public:
	Client();
	virtual ~Client();
	void Echo(std::string text, const asio::ip::address_v4 ip, const unsigned short port);
	static bool RecvFile(const std::string, const std::string, const asio::ip::address_v4 ip, const unsigned short);
	bool SendFile(const std::string, const std::string, const asio::ip::address_v4 ip, const unsigned short);
	void SendText(const std::string text, const asio::ip::address_v4 ip, const unsigned short port);
};

