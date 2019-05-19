#include <cstring>
#include <string>
#include <iostream>

int ProcessLogin(const std::string& login);
int ProcessPass(const std::string& password);
bool ProcessCred(const std::string& login, const std::string& password);
bool bruteforce(const std::string& login, char* str, int depth);

int main()
{
	std::string login;
	std::cin >> login;
	char c[32] = {0};
	if(bruteforce(login, c, 3))
		std::cout << c << std::endl;
	system("PAUSE");
}

int ProcessLogin(const std::string &login)
{
	int result = 0xffffffff;
	int temp = 0;

	for (const auto character: login)
	{
		result ^= character;

			for (int i = 7; i >= 0; i--)
			{
				temp = result;

					//--some asm:--
				temp &= 1;
				temp = -temp;
				result >>= 1;
				temp &= 0xedb88320;
					//--asm end--

				result ^= temp;
			}
	}

	return result;
}

int ProcessPass(const std::string &password)
{
	int result = 0;
	for (const auto character: password)
		result += character ^ 0x99;
	return result;
}

bool ProcessCred(const std::string& login, const std::string& password)
{
	int loginResult = ProcessLogin(login);
	int passResult = ProcessPass(password);

	//--some asm:--
	loginResult = ~loginResult;
	loginResult &= 0xff;
	passResult &= 0xff;
	//--asm end--

	if (loginResult == passResult)
	{
		return true;
	}

	return false;
}

bool bruteforce(const std::string& login, char * str, int depth)
{
	if (depth == 0)
		return false;
	if (depth == 1)
		depth = 1;
	auto len = strlen(str);
	for (char c = '0'; c <= 'z'; ++c)
	{
		if ((c > 9 && c < 'A') || (c > 'Z' && c < 'a'))
			continue;
		memset(str + len, 0, 32 - len);
		str[len] = c;
		if (ProcessCred(login, str))
			return str;
	}

	for (char c = '0'; c <= 'z'; ++c)
	{
		if ((c > 9 && c < 'A') || (c > 'Z' && c < 'a'))
			continue;
		memset(str + len, 0, 32 - len);
		str[len] = c;
		if (bruteforce(login, str, depth - 1))
			return true;
	}
	return false;
}
