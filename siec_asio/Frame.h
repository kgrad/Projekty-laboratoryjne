#pragma once
#include "asio.hpp"
struct Frame{

	enum Type {
		ECHO = 0x00,
		TEXT=0x01,
		RECV_FILE=0x02,
		SEND_FILE=0x03,
		FILE_DATA=0x04,
		END_OF_FILE=0x05,
		INVALID_COMMAND=0x06
};
	uint8_t type;
	uint16_t len;
	uint8_t data[1024];
	
};