// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ListenSocket.h"
#include "ClientSocket.h"

// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}

// CListenSocket 멤버 함수

// 서버가 접속을 기다리는 특정 포트로 클라이언트의 TCP 저속이 있을때 자동으로 호출
// 이함수가 호출되면 새로운 클라이언트 접속은 있지만 아직 접속을 승인하지 않은상태
void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket;
	if(Accept(*pClient)) {
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
	} else {
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed t accept new Client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

// 클라이언트 연결 종료함수
void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);

	if(pos != NULL) {
		if(pClient != NULL) {
			// 클라이언트 연결중지후 종료
			pClient->ShutDown();
			pClient->Close();
		}
		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}

void CListenSocket::SendChatDataAll(TCHAR* pszMessage)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while(pos != NULL) {
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if(pClient != NULL) {
			// Send함수의 두번째 인자는 메모리의 크기인데 유니코드를 사용하고 있으므로 *2를 한 크기가 된다.
			// 이 함수는 전송한 데이터의 길이를 반환한다.
			int checkLenOfData = pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
			if(checkLenOfData != lstrlen(pszMessage) * 2) {
				AfxMessageBox(_T("일부 데이터가 정상적을 전송되지 못했습니다!"));
			}
		}
	}
}