#include <iostream>
#include <thread> 
#include "IThread.h"
#include "Server.h"
#include "asio.hpp"
#include"BinFile.h"
#include "Frame.h"
using namespace std;
Server::Server(unsigned short port) : port(port)
{
}


Server::~Server()
{
}


void session(asio::ip::tcp::socket socket)
{
	try
	{
		while (true)
		{
			Frame rframe;
			Frame sframe;
			asio::read(socket, asio::buffer(&rframe, sizeof(Frame)));


			switch (rframe.type) {

			case Frame::Type::ECHO:
				sframe = rframe;
				std::cout << "S: sending echo. " << std::endl;
				asio::write(socket, asio::buffer(&rframe, sizeof(sframe)));
				break;

			case Frame::Type::TEXT:
				std::cout << "S: recieved text: " << std::string((const char*)rframe.data, rframe.len) << std::endl;
				break;

			case Frame::Type::SEND_FILE:
			{
				BinFile file(string((const char*)rframe.data, rframe.len), true);
				do
				{
					asio::read(socket, asio::buffer(&rframe, sizeof(Frame)));
					if (rframe.type == Frame::Type::FILE_DATA)
					{
						file.Append(rframe.data, rframe.len);
					}
				} while (rframe.type == Frame::Type::FILE_DATA);
				cout << "S: File received" << std::endl;
				break;
			}
			case Frame::Type::RECV_FILE:
			{
				BinFile file(string((const char*)rframe.data, rframe.len), false);
				uint8_t* fileBuffer = new uint8_t[1024];
				size_t fsize = 1024;

				fsize = file.Read(fileBuffer, 1024);
				sframe.type = Frame::FILE_DATA;
				std::cout << fsize << " " << string((const char*)rframe.data, rframe.len);
				while (fsize != 0)
				{
					sframe.len = fsize;
					memcpy(sframe.data, fileBuffer, fsize);
					asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
					fsize = file.Read(fileBuffer, 1024);
				}

				sframe.type = Frame::END_OF_FILE;
				sframe.len = 0;
				asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
			}
			break;

			default:
				sframe.type = Frame::Type::INVALID_COMMAND;
				sframe.len = 0;
				asio::write(socket, asio::buffer(&sframe, sizeof(Frame)));
				break;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << std::endl;
	}
	socket.close();
}



void Server::ThreadRoutine()
{
	asio::io_service io_service; // Any program that uses asio need to have at least one io_service object
	asio::ip::tcp::acceptor acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)); //create acceptor for listening purposes
	acceptor.listen(1024);
	while (isRunning())
	{
		asio::ip::tcp::socket socket(io_service); //create a socket for communication purposes
		acceptor.accept(socket); //then accept connection
		
		//read data sent by the client, then send echo
		std::thread(session, std::move(socket)).detach();

		std::this_thread::yield();
	}
}
