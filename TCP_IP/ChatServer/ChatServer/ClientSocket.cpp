// ClientSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ClientSocket.h"
#include "ListenSocket.h"
#include "ChatServerDlg.h"

// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

// CClientSocket 멤버 함수
void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}

void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}

void CClientSocket::OnReceive(int nErrorCode)
{
	CString strTmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer)); // :: 붙이고 안붙이고 차이 알아보기

	GetPeerName(strIPAddress, uPortNumber); // 연결된 클라이언트의 정보를 알아내주는 함수
	if(Receive(szBuffer, sizeof(szBuffer)) > 0) { // 전달된 데이터(문자열)가 있을 경우
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		strTmp.Format(_T("[%s:%d]: %s"), strIPAddress, uPortNumber, szBuffer);
		pMain->m_List.AddString(strTmp);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->SendChatDataAll(szBuffer);		
	}

	CSocket::OnReceive(nErrorCode);
}