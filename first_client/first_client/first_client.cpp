#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ErrorHandling(char *Message) {//에러 처리 하는 함수
	fputs(Message, stderr);
	fputc('\n', stderr);
	exit(1);	//오류가 발생했으니 그대로 프로그램 종료
}
int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET connect_sock;
	SOCKADDR_IN connect_addr;

	if (argc != 3) {
		printf("다음과 같이 사용하세요 : %s <IP> <PORT번호>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	connect_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (connect_sock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&connect_addr, 0, sizeof(connect_addr));
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_addr.S_un.S_addr = inet_addr(argv[1]);//argv[1]:인수에 입력된 IP
	connect_addr.sin_port = htons(atoi(argv[2]));	//argv[2]:인수에 입력된 port

	if (connect(connect_sock, (SOCKADDR*)&connect_addr, sizeof(connect_addr)))//입력한 주소로 접속
		ErrorHandling("connect() error");

	/************데이터를 이제 주고받을 수 있다***************/
	//~source~//
	char buf[100] = "Test Message";
	char line[100];
	
	while (1)
	{	
		if (getchar() == 'A') {
			send(connect_sock, buf, 20, 0);
		}
	}

	 /* receive the html from the web server */

	//send(connect_sock, "Hello World", 12, 0);	//문자열 전송
	//puts("전송 성공, 프로그램 종료");
	/****************************************************/
	closesocket(connect_sock);
	WSACleanup();
	return 0;
}