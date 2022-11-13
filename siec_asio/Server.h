#pragma once
#include "IThread.h"
class Server :
	public IThread
{
	unsigned short port;
public:
	Server(unsigned short);
	virtual ~Server();
	void ThreadRoutine();
	
};

