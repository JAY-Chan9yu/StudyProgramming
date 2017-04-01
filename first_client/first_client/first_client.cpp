#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ErrorHandling(char *Message) {//���� ó�� �ϴ� �Լ�
	fputs(Message, stderr);
	fputc('\n', stderr);
	exit(1);	//������ �߻������� �״�� ���α׷� ����
}
int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET connect_sock;
	SOCKADDR_IN connect_addr;

	if (argc != 3) {
		printf("������ ���� ����ϼ��� : %s <IP> <PORT��ȣ>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error");

	connect_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (connect_sock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&connect_addr, 0, sizeof(connect_addr));
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_addr.S_un.S_addr = inet_addr(argv[1]);//argv[1]:�μ��� �Էµ� IP
	connect_addr.sin_port = htons(atoi(argv[2]));	//argv[2]:�μ��� �Էµ� port

	if (connect(connect_sock, (SOCKADDR*)&connect_addr, sizeof(connect_addr)))//�Է��� �ּҷ� ����
		ErrorHandling("connect() error");

	/************�����͸� ���� �ְ���� �� �ִ�***************/
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

	//send(connect_sock, "Hello World", 12, 0);	//���ڿ� ����
	//puts("���� ����, ���α׷� ����");
	/****************************************************/
	closesocket(connect_sock);
	WSACleanup();
	return 0;
}