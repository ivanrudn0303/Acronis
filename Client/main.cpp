#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

int main()
{
	WSADATA	ws;
	SOCKET	s;
	sockaddr_in	adr;
	hostent*	hn;
	char	buff[2048];

	if (WSAStartup(0x202, &ws) != 0)
	{
		// Error
		return -1;
	}

	// Создаем сокет
	if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, 0)))
	{
		// Error
		return -1;
	}

	DWORD a = inet_addr("127.0.0.1");

	adr.sin_addr.S_un.S_addr = a;
	adr.sin_family = AF_INET;
	int port = 7800;
	adr.sin_port = htons(port);

	if (SOCKET_ERROR == connect(s, (sockaddr*)&adr, sizeof(adr)))
	{
		// Error
		return -1;
	}
	while (true)
	{
		char buf[2048] = { 0 };
		gets_s(buf);
		strcat(buf, "\r\n\r\n");
		if (SOCKET_ERROR == send(s, buf, strlen(buf), 0))
		{
			std::cout << "error 2\n";
			// Error
			system("PAUSE");
			return -1;
		}
		
		int len = recv(s, buf, 2048, 0);
		buf[len] = '\0';
		std::cout << buf << std::endl << len <<std::endl;
	}
	if (SOCKET_ERROR == closesocket(s))
	{
		// Error
		return -1;
	}
	system("PAUSE");
	return 0;
}
