#include "Server.h"
#include <iostream>
void Respond(SOCKET, LogContainer*, std::mutex*, std::stack<std::list<std::thread>::iterator>*, std::list<std::thread>::iterator);

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

	while (true)
	{
		SOCKET NewSocket = accept(Socket, nullptr, nullptr);
		ThreadList.push_front(std::thread());
		ThreadList.front() = std::thread(Respond, NewSocket, &Container, &StackMutex, &FinishedThead, ThreadList.begin());
		FreeThreadResourses();
	}

	closesocket(Socket);
	WSACleanup();
}

Server::~Server()
{}

void Respond(SOCKET sock, LogContainer* base, std::mutex* mute, std::stack<std::list<std::thread>::iterator>* stack, std::list<std::thread>::iterator it)
{
	char buf[2048] = {0};
	recv(sock, buf, 2048, 0);
	std::cout << "new client\n";
	printf(buf);
	Sleep(100);
	//responds on http requests
	closesocket(sock);
	mute->lock();
	stack->push(it);
	mute->unlock();
}
