#include "Client.h"
#include "asio.hpp"
#include <iostream>
#include "BinFile.h"
#include "Frame.h"
#include<string>
Client::Client()
{

}

Client::~Client()
{
}

bool Client::RecvFile(const std::string serverFilepath, const std::string clientFilepath, const asio::ip::address_v4 ip, const unsigned short port)
{
	bool retVal = false;
	Frame sframe;
	sframe.type = Frame::Type::RECV_FILE;
	sframe.len = serverFilepath.size();
	memcpy(sframe.data, serverFilepath.data(), serverFilepath.size());
	asio::io_service io_service; // Any program that uses asio need to have at least one io_service object
	asio::ip::tcp::socket socket(io_service); //create client socket
	socket.connect(asio::ip::tcp::endpoint(ip, port)); //connect to server
	asio::write(socket, asio::buffer(&sframe, sizeof(sframe)));

	Frame rframe;
	BinFile file(clientFilepath, true);
	if (file.IsOpen()) {
		asio::io_service io_service; // Any program that uses asio need to have at least one io_service object
		asio::ip::tcp::socket socket(io_service); //create client socket
		socket.connect(asio::ip::tcp::endpoint(ip, port)); //connect to server
		asio::write(socket, asio::buffer(&rframe, sizeof(rframe)));

		do {
			asio::read(socket, asio::buffer(&rframe, sizeof(rframe)));
			if (rframe.type == Frame::Type::FILE_DATA) {
				file.Append(rframe.data, rframe.len);
			}
		} while (rframe.type == Frame::Type::FILE_DATA);
		retVal = rframe.type == Frame::Type::END_OF_FILE;
	}
	return retVal;
}

bool Client::SendFile(const std::string SFile, const std::string CFile, const asio::ip::address_v4 ip, const unsigned short port)
{
	Frame fframe;

	BinFile file(CFile, false);
	uint8_t* fileBuffer = new uint8_t[1024];
	size_t fsize = 1024;
	asio::io_service io_service;
	asio::ip::tcp::socket socket(io_service);


	std::cout << "C: Connecting to server " << ip.to_string() << ":" << port << std::endl;
	socket.connect(asio::ip::tcp::endpoint(ip, port));

	fframe.type = Frame::SEND_FILE;
	fframe.len = SFile.size();
	memcpy(fframe.data, SFile.data(), SFile.size());
	asio::write(socket, asio::buffer(&fframe, sizeof(Frame)));

	fsize = file.Read(fileBuffer, 1024);
	fframe.type = Frame::FILE_DATA;

	while (fsize != 0)
	{
		fframe.len = fsize;
		memcpy(fframe.data, fileBuffer, fsize);
		asio::write(socket, asio::buffer(&fframe, sizeof(Frame)));
		fsize = file.Read(fileBuffer, 1024);
	}
	fframe.type = Frame::END_OF_FILE;
	fframe.len = 0;
	asio::write(socket, asio::buffer(&fframe, sizeof(Frame)));
	socket.close();
	return true;
}

void Client::SendText(const std::string text, const asio::ip::address_v4 ip, const unsigned short port)
{
	asio::io_service io_service;
	asio::ip::tcp::socket socket(io_service);
	Frame tframe;

	tframe.type = Frame::Type::TEXT;
	tframe.len = text.size();
	memcpy(tframe.data, text.data(), text.length());

	std::cout << "C: Connecting to server " << ip.to_string() << ":" << port << std::endl;
	socket.connect(asio::ip::tcp::endpoint(ip, port));
	std::cout << "C: Sending text " << text.size() << " bytes long" << std::endl;
	asio::write(socket, asio::buffer(&tframe, sizeof(Frame)));
	socket.close();

}

void Client::Echo(std::string text, const asio::ip::address_v4 ip, const unsigned short port)
{
	//prepare frame
	Frame sframe;
	sframe.type = Frame::Type::ECHO;
	sframe.len = text.size();
	memcpy(sframe.data, text.data(),text.size());

	//send frame to server
	asio::io_service io_service; // Any program that uses asio need to have at least one io_service object
	asio::ip::tcp::socket socket(io_service); //create client socket
	socket.connect(asio::ip::tcp::endpoint(ip, port)); //connect to server

	std::cout << "C: Send echo request with data: " << text << std::endl;
	asio::write(socket, asio::buffer(&sframe, sizeof(sframe)));

	//receive echo
	Frame rframe;
	asio::read(socket, asio::buffer(&rframe, sizeof(rframe)));
	std::string text2((const char*)rframe.data, rframe.len);
	std::cout << "C: Echo is: " << text2 << std::endl;
}