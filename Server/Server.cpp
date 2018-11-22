#include "Server.h"
#include <iostream>
#include <cstring>

#define ERROR_BUF_OVERFLOW 2
#define ERROR_WRONG_COMMAND 3
#define ERROR_REQUEST 5

#define BUF_SIZE 2048


void Respond(SOCKET, LogContainer*, std::mutex*, std::stack<std::list<std::thread>::iterator>*, std::list<std::thread>::iterator);
void PeriodicFunction(LogContainer*);
int Handler(SOCKET, LogContainer*, char*, int);

#define COMMAND(request) int RESPOND_##request(SOCKET, LogContainer*, char*, int);
#include "RequestCommand.h"
#undef COMMAND


int Server::FreeThreadResourses()
{
	StackMutex.lock();
	while (!FinishedThead.empty())
	{
		std::list<std::thread>::iterator it = FinishedThead.top();
		it->join();
		ThreadList.erase(it);
		FinishedThead.pop();
	}
	StackMutex.unlock();
	return 0;
}

Server::Server(USHORT port):Port(port)
{}

int Server::Start()
{
	WORD wVersion;
	WSAData WsaData;
	wVersion = MAKEWORD(2, 0);
int err = WSAStartup(wVersion, &WsaData);
if (err != 0)
return err;
Socket = socket(AF_INET, SOCK_STREAM, 0);
if (Socket == INVALID_SOCKET)
{
	WSACleanup();
	return INVALID_SOCKET;
}

SOCKADDR_IN addr;
addr.sin_addr.S_un.S_addr = INADDR_ANY;
addr.sin_port = htons(Port);
addr.sin_family = AF_INET;

err = bind(Socket, (SOCKADDR *)&addr, sizeof(addr));
if (err == SOCKET_ERROR)
{
	closesocket(Socket);
	WSACleanup();
	return SOCKET_ERROR;
}

err = listen(Socket, SOMAXCONN);
if (err == SOCKET_ERROR)
{
	closesocket(Socket);
	WSACleanup();
	return SOCKET_ERROR;
}

std::thread PeriodicUpdater(PeriodicFunction, &Container);

while (true)
{
	SOCKET NewSocket = accept(Socket, nullptr, nullptr);
	ThreadList.push_front(std::thread());
	ThreadList.front() = std::thread(Respond, NewSocket, &Container, &StackMutex, &FinishedThead, ThreadList.begin());
	FreeThreadResourses();
}

PeriodicUpdater.join();
closesocket(Socket);
WSACleanup();
}

Server::~Server()
{}

void Respond(SOCKET sock, LogContainer* base, std::mutex* mute, std::stack<std::list<std::thread>::iterator>* stack, std::list<std::thread>::iterator it)
{
	char buf[BUF_SIZE] = { 0 };
	int len = recv(sock, buf, BUF_SIZE, 0);
//	base->Lock();
	Handler(sock, base, buf, len);
//	base->Unlock();
	closesocket(sock);
	mute->lock();
	stack->push(it);
	mute->unlock();
}

void PeriodicFunction(LogContainer* base)
{
	while (true)
	{
//		base->Lock();
		base->SomeAction();
//		base->Unlock();
		Sleep(450);
	}
}

#define BAD {\
send(sock, "HTTP/1.1 409 Bad Request\r\n\r\n", 28, 0);\
return ERROR_REQUEST;\
}

#define COMMAND(request) if((start = strstr(buf, #request " ")) != nullptr)\
	return RESPOND_##request(sock, data, start, length);\
	else

int Handler(SOCKET sock, LogContainer *data, char *buf, int length)
{
	buf[length] = '\0';
	std::cout << buf;
	char *start = nullptr;
#include "RequestCommand.h"
	BAD

	//	send(sock, "HTTP/1.1 200 OK\r\n\r\nhello\r\n\r\n", 28, 0);
}
#undef COMMAND



int RESPOND_PUT(SOCKET sock, LogContainer* data, char* start, int length)
{
	if ((start = strstr(start, "/Log/")) == nullptr)
		BAD
		start += sizeof("/Log/") - 1;
	uint32_t id = static_cast<uint32_t>(atoi(start));
	if (data->ForceFlush(id))
		BAD
	send(sock, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
	return 0;
}

int RESPOND_POST(SOCKET sock, LogContainer* data, char* start, int length)
{
	if((start = strstr(start, "/Log/")) == nullptr)
		BAD
	start += sizeof("/Log/") - 1;
	uint32_t id = static_cast<uint32_t>(atoi(start));
	
	char* Update = strstr(start, "UpdatePeriod=");
	if (Update == nullptr)
		BAD
	Update += sizeof("UpdatePeriod=") - 1;
	uint32_t UpdatePeriod = static_cast<uint32_t>(atoi(Update));

	char* path = strstr(start, "Path=");
	if(path == nullptr)
		BAD
	path += sizeof("Path=") - 1;
	char key[] = " \n\r\0";
	char *end = strpbrk(path, key);
	if (end == nullptr)
		BAD
	*end = '\0';

	if (data->Register(path, id, UpdatePeriod))
		BAD
	send(sock, "HTTP/1.1 201 Created\r\n\r\n", 24, 0);
	return 0;
}

int RESPOND_DELETE(SOCKET sock, LogContainer* data, char* start, int length)
{
	if ((start = strstr(start, "/Log/")) == nullptr)
		BAD
		start += sizeof("/Log/") - 1;
	uint32_t id = static_cast<uint32_t>(atoi(start));
	if (data->Unregister(id))
		BAD
	send(sock, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
	return 0;
}
#undef BAD
