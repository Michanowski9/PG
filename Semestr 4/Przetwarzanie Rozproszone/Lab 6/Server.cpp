#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

string toUpperCase(char input[80]) {
	string result = "";
	for (int i = 0; i < 80; i++)
	{
		if (input[i] >= 'a' && input[i] <= 'z')
		{
			char temp = input[i];
			temp += ('A' - 'a');
			result += temp;
		}
		else {
			result += input[i];
		}
	}
	return result;
}

int main()
{
	WSADATA wsas;
	int result;
	WORD wersja;
	wersja = MAKEWORD(1, 1);
	result = WSAStartup(wersja, &wsas);
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in sa;
	memset((void*)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(3000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	result = bind(s, (struct sockaddr FAR*) & sa, sizeof(sa));

	result = listen(s, 5);

	SOCKET si;
	struct sockaddr_in sc;
	int lenc;
	while(true)
	{
		lenc = sizeof(sc);
		si = accept(s, (struct sockaddr FAR*) & sc, &lenc);

		char buf[80];
		while (recv(si, buf, 80, 0) > 0)
		{
			if (strcmp(buf, "KONIEC") == 0)
			{
				closesocket(si);
				WSACleanup();
				return 0;
			}

			printf("FromClient:\t%s\n", buf);
			string str = toUpperCase(buf);
			printf("ToClient:\t%s\n", str.c_str());
			send(si, str.c_str(), 80, 0);
		};

	}
	return 0;
}
