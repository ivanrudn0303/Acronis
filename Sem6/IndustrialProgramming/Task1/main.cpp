#pragma warning(disable : 4996)
#include <iostream>
#include <cstring>
#include <vector>


void fizbuzz(char* pointer);
int Mod3(int num);

int main()
{
	std::vector<std::string> res;

	char buf[256] = {};
	std::cin >> buf;
	while (strcmp(buf, "stop") != 0)
	{
		fizbuzz(buf);
		res.push_back(buf);
		std::cin >> buf;
	}

	for (const auto& el : res)
		std::cout << el.c_str() << '\n';
	system("PAUSE");
	return 0;
}

void fizbuzz(char* pointer)
{
	char *input = pointer;
	int sumMod3 = 0;
	while ((*pointer > '9') || (*pointer < '0'))
		if (*++pointer == '\0')
			return;
	int sum = 0;
	for (; (*pointer <= '9') && (*pointer >= '0'); ++pointer)
	{
		sum += *pointer - '0';
		sumMod3 += Mod3(*pointer - '0');
		sumMod3 = Mod3(sumMod3);
	}
	if (sum)
	{
		int lastdigid = *--pointer - '0';
		if ((sumMod3 == 0) && ((lastdigid == 5) || (lastdigid == 0)))
			strcpy(input, "fizzbuzz");
		else if (sumMod3 == 0)
			strcpy(input, "fizz");
		else if ((lastdigid == 0) || (lastdigid == 5))
			strcpy(input, "buzz");
	}
}

int Mod3(int num)
{
	if ((num == 0) || (num == 3) || (num == 6) || (num == 9))
		return 0;
	else if ((num == 1) || (num == 4) || (num == 7))
		return 1;
	else
		return 2;

}
