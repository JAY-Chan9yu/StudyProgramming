#include <WinSock2.h> 
// �ݵ�� winsock2.h�� ���� include
#include <Windows.h>
#include <stdio.h>


void ErrorHandling(char *Message) {//���� ó�� �ϴ� �Լ�
	fputs(Message, stderr);
	fputc('\n', stderr);
	exit(1);	//������ �߻������� �״�� ���α׷� ����
}

int main(int argc, char **argv) {
	WSADATA wsaData;
	SOCKET listen_sock, connect_sock;
	SOCKADDR_IN listen_addr, connect_addr; //SOCKADDR_IN ����ü�� ���� ��ſ� ����� �ּҿ� ��Ʈ��ȣ�� �����ϴ� ������ �մϴ�.
	int sockaddr_in_size;
	char message[100];

	// ���α׷��� �����ϱ����� ���ڵ��� �� �����ִ��� Ȯ���ϴ� �۾�
	if (argc != 2) {
		printf("������ ���� ����ϼ��� : %s <PORT��ȣ>\n", argv[0]);
		exit(1);
	}

	// �����쿡���� ������ ����(winsock)���� �θ��� ��, ������ ����ϱ� ���ؼ� ���� ���� WSAtartup�Լ���
	// ȣ���ؼ�, �����쿡�� ����ϰ��� �ϴ� ������ ������ �˷��� ��. 
	// ��, ���� ���α׷��� ���� ó���� WASStartup()�� ȣ��� �����Ѵٴ� �̾߱�.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	//���� 2.2���� ����
		ErrorHandling("WSAStartup() error");	//��� ��ġ���� ������ ������ Ȯ�� �� ���α׷� ����.

	// PF_INET�� IPv4��, SOCK_STREAM�� TCP ������ ��Ÿ���ϴ�.
	listen_sock = socket(PF_INET, SOCK_STREAM, 0);//���ο� ���ϻ����� ����
	if (listen_sock == INVALID_SOCKET) // ��������
		ErrorHandling("socket() error");

	memset(&listen_addr, 0, sizeof(listen_addr));//�ּ� ���尡���� ����ü�� �ּ� ������
	// Internet Protocol Version ������ �Է��մϴ�. �� IPv4���� IPv6�� ���� �����Դϴ�.
	listen_addr.sin_family = AF_INET; // AF_INET�� �����մϴ�. (IPv4)
	// IP�ּҸ� �����ϴ� �κ�
	// INADDR_ANY�� �ڱ� ��ǻ���� IP�� ��Ÿ���µ�, ��ǻ�Ϳ� ��������  ��Ʈ��ũ ī�尡 �ִٸ� 
	// ��� �����κ��͵��� ������ ����ϰڴٴ� �ǹ��̰� �̰��� ����ü�� �°� ����(htonl �Լ��� ����)���ְ� �ֽ��ϴ�
	listen_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	// port ��ȣ�� �����ϴ� �κ� 
	// ���ڿ��� ���޵� ���ڸ� atoi�Լ��� ���� int�� ���ڷ� �ٲ� �� htons�Լ��� ����
	listen_addr.sin_port = htons(atoi(argv[1]));
	/***********************************�������********************************/

	if (bind(listen_sock, (SOCKADDR*)&listen_addr, sizeof(listen_addr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");	//������ �ּҸ� bind�Լ��� ���Ͽ� �Ҵ�!

	if (listen(listen_sock, 5) == SOCKET_ERROR)	//���⼭ Ŭ���̾�Ʈ ���ӿ�û������ ��� ��ٸ���!
		ErrorHandling("listen() error");

	sockaddr_in_size = sizeof(connect_addr);
	connect_sock = accept(listen_sock, (SOCKADDR*)&connect_addr, &sockaddr_in_size);
	if (connect_sock == INVALID_SOCKET)
		ErrorHandling("accept() error");
	/************�����͸� ���� �ְ���� �� �ִ�***************/
	//~source~//
	
	int bytesRcvd;
	while (1) {
		bytesRcvd = recv(connect_sock, message, 20, 0);
		if (bytesRcvd <= 0)
			break;
		message[bytesRcvd] = '\0';
		printf("�����κ��� �޼��� : %s\n", message);
	}
		
	/****************************************************/
	closesocket(connect_sock);	//���ϵ��� �������ְ�
	closesocket(listen_sock);
	WSACleanup();	//���� �ʱ�ȭ
	return 0;
}