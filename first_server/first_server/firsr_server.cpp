#include <WinSock2.h> 
// 반드시 winsock2.h를 먼저 include
#include <Windows.h>
#include <stdio.h>


void ErrorHandling(char *Message) {//에러 처리 하는 함수
	fputs(Message, stderr);
	fputc('\n', stderr);
	exit(1);	//오류가 발생했으니 그대로 프로그램 종료
}

int main(int argc, char **argv) {
	WSADATA wsaData;
	SOCKET listen_sock, connect_sock;
	SOCKADDR_IN listen_addr, connect_addr; //SOCKADDR_IN 구조체는 소켓 통신에 사용할 주소와 포트번호를 저장하는 역할을 합니다.
	int sockaddr_in_size;
	char message[100];

	// 프로그램을 시작하기전에 인자들이 잘 들어와있는지 확인하는 작업
	if (argc != 2) {
		printf("다음과 같이 사용하세요 : %s <PORT번호>\n", argv[0]);
		exit(1);
	}

	// 윈도우에서는 소켓을 윈속(winsock)으로 부르는 데, 윈속을 사용하기 위해선 제일 먼저 WSAtartup함수를
	// 호출해서, 윈도우에서 사용하고자 하는 소켓의 버전을 알려야 함. 
	// 즉, 윈속 프로그램의 가장 처음은 WASStartup()의 호출로 시작한다는 이야기.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	//윈속 2.2버전 시작
		ErrorHandling("WSAStartup() error");	//어느 위치에서 오류가 났는지 확인 및 프로그램 종료.

	// PF_INET은 IPv4를, SOCK_STREAM은 TCP 연결을 나타냅니다.
	listen_sock = socket(PF_INET, SOCK_STREAM, 0);//새로운 소켓생성후 대입
	if (listen_sock == INVALID_SOCKET) // 오류검출
		ErrorHandling("socket() error");

	memset(&listen_addr, 0, sizeof(listen_addr));//주소 저장가능한 구조체에 주소 설정중
	// Internet Protocol Version 정보를 입력합니다. 즉 IPv4인지 IPv6에 대한 정보입니다.
	listen_addr.sin_family = AF_INET; // AF_INET을 대입합니다. (IPv4)
	// IP주소를 저장하는 부분
	// INADDR_ANY가 자기 컴퓨터의 IP를 나타내는데, 컴퓨터에 여러개의  네트워크 카드가 있다면 
	// 어느 것으로부터든지 연결을 허용하겠다는 의미이고 이것을 구조체에 맞게 변경(htonl 함수를 통해)해주고 있습니다
	listen_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	// port 번호를 저장하는 부분 
	// 문자열로 전달되 숫자를 atoi함수를 통해 int형 숫자로 바꾼 후 htons함수로 대입
	listen_addr.sin_port = htons(atoi(argv[1]));
	/***********************************여기까지********************************/

	if (bind(listen_sock, (SOCKADDR*)&listen_addr, sizeof(listen_addr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");	//설정된 주소를 bind함수로 소켓에 할당!

	if (listen(listen_sock, 5) == SOCKET_ERROR)	//여기서 클라이언트 접속요청때까지 계속 기다린다!
		ErrorHandling("listen() error");

	sockaddr_in_size = sizeof(connect_addr);
	connect_sock = accept(listen_sock, (SOCKADDR*)&connect_addr, &sockaddr_in_size);
	if (connect_sock == INVALID_SOCKET)
		ErrorHandling("accept() error");
	/************데이터를 이제 주고받을 수 있다***************/
	//~source~//
	
	int bytesRcvd;
	while (1) {
		bytesRcvd = recv(connect_sock, message, 20, 0);
		if (bytesRcvd <= 0)
			break;
		message[bytesRcvd] = '\0';
		printf("서버로부터 메세지 : %s\n", message);
	}
		
	/****************************************************/
	closesocket(connect_sock);	//소켓들을 정리해주고
	closesocket(listen_sock);
	WSACleanup();	//윈속 초기화
	return 0;
}