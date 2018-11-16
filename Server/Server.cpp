#include "Server.h"
#include <iostream>
#include <cstring>

#define ERROR_BUF_OVERFLOW 2
#define ERROR_WRONG_COMMAND 3

#define BUF_SIZE 2048


void Respond(SOCKET, LogContainer*, std::mutex*, std::stack<std::list<std::thread>::iterator>*, std::list<std::thread>::iterator);
void PeriodicFunction(LogContainer*);
int Handler(SOCKET, LogContainer*, char*, int);
char* SplitStr(char*);


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
//	Container.Register("prev");
//	Container.Register("pal");
//	Container.Update("pal", 5);
//	Container.Register("next");
//	Container.Update("next", 3);

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
	char buf[BUF_SIZE] = {0};
	int len = recv(sock, buf, BUF_SIZE, 0);
	while ((len > 0) && (len != SOCKET_ERROR))
	{
		//		std::cout << "new client\n";
		printf("length: %d\n%s\n", len, buf);
		//	Sleep(100);
			//responds on http requests
		base->Lock();
		Handler(sock, base, buf, len);
		base->Unlock();
		len = recv(sock, buf, 2048, 0);
	}
	closesocket(sock);
	mute->lock();
	stack->push(it);
	mute->unlock();
}

void PeriodicFunction(LogContainer* base)
{
	while (true)
	{
		base->Lock();
		base->SomeAction();
		base->Unlock();
		Sleep(450);
	}
}



#define WRONG_COM() {\
send(sock, "400 Bad Request\r\n\r\n", 19, 0);\
return ERROR_WRONG_COMMAND;\
}

#define ANS_REG(num) {\
	int err = num;\
	if(err == 0)\
		send(sock, "201 Created\r\n\r\n", 15, 0);\
	else\
		send(sock, "409 Conflict\r\n\r\n", 16, 0);\
	buf = strstr(end + 1, "\r\n\r\n") + 4;\
}


#define ANS_UNREG(num) {\
	int err = num;\
	if(err == 0)\
		send(sock, "200 OK\r\n\r\n", 10, 0);\
	else\
		send(sock, "404 Not Found\r\n\r\n", 17, 0);\
	buf = strstr(end + 1, "\r\n\r\n") + 4;\
}

#define ANS_SET(num) {\
int err = num;\
	if(err == 0)\
		send(sock, "200 OK\r\n\r\n", 10, 0);\
	else\
		send(sock, "404 Not Found\r\n\r\n", 17, 0);\
	buf = strstr(end + 1, "\r\n\r\n") + 4;\
}

int Handler(SOCKET sock, LogContainer *base, char *buf, int len)
{
	if(len == BUF_SIZE)
		return ERROR_BUF_OVERFLOW;
	buf[len] = '\0';
	while ((buf != nullptr) && (*buf != '\0'))
	{

		if (strncmp(buf, "REGISTER", 8) == 0)
		{
			char *end = SplitStr(buf);
			if (end == nullptr)
				WRONG_COM();

			buf = strchr(buf, ' ') + 1;
			*end = '\0';
			ANS_REG(base->Register(buf));
		}
		else if (strncmp(buf, "UNREGISTER", 10) == 0)
		{
			char *end = SplitStr(buf);
			if (end == nullptr)
				WRONG_COM();

			buf = strchr(buf, ' ') + 1;
			*end = '\0';
			ANS_UNREG(base->Unregister(buf));
		}
		else if (strncmp(buf, "SET", 3) == 0)
		{
			char *end = strchr(buf, '?');
			if (end == nullptr)
				WRONG_COM();

			buf = strchr(buf, ' ') + 1;
			*end = '\0';
			char* num = strstr(end + 1, "UpdatePeriod=");
			if (num == nullptr)
				WRONG_COM();
			num += 13;
			uint32_t Period = atoi(num);
			if(!Period)
				WRONG_COM();
			ANS_SET(base->Update(buf, Period));
		}
		else
			WRONG_COM();
	}
	return 0;
}
#undef ANS_REG
#undef ANS_UNREG
#undef WRONG_COM

char* SplitStr(char* str)
{
	if (str == nullptr)
		return nullptr;
	str = strchr(str, ' ');
	if (str == nullptr)
		return nullptr;
	return strchr(str + 1, ' ');
}
