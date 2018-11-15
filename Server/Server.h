#ifndef SERVER_H
#define SERVER_H
#pragma comment (lib, "ws2_32.lib")
#include <winsock2.h>  
#include "LogContainer.h"
#include <mutex>
#include <stack>
#include <list>
#include <thread>

class Server
{
private:
	USHORT Port;
	SOCKET Socket;
	LogContainer Container;
	std::mutex StackMutex;
	std::list<std::thread> ThreadList;
	std::stack<std::list<std::thread>::iterator> FinishedThead;
	int FreeThreadResourses();
public:
	Server(USHORT);
	int Start();
	~Server();
};
#endif // !SERVER_H
