// ListenSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "ListenSocket.h"
#include "ClientSocket.h"
#include <string.h>

// CListenSocket

CListenSocket::CListenSocket()
{
	acceptFlag = FALSE;
}

CListenSocket::~CListenSocket()
{
}

// 서버가 접속을 기다리는 특정 포트로 클라이언트의 TCP 저속이 있을때 자동으로 호출
// 이함수가 호출되면 새로운 클라이언트 접속은 있지만 아직 접속을 승인하지 않은상태
void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket;
	CString str;
	
	if(Accept(*pClient)) {
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
		
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		str.Format(_T("Client (%d)"), (int)m_ptrClientSocketList.Find(pClient)); // 클라이언트 번호(POSITION 값)
		clientList.AddTail(str);
		pMain->clientList->AddString(str); // 클라이언트가 접속할때마다 리스트에 클라이언트 이름 추가
		AfxMessageBox(str + _T("가 접속하였습니다"));
	} else {
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
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
		
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		CString str1, str2;		
		UINT indx = 0, posNum;	
		pMain->clientList->SetCurSel(0);
		while(indx < pMain->clientList->GetCount()) {
			posNum = (int)m_ptrClientSocketList.Find(pClient); 
			pMain->clientList->GetText(indx, str1);
			str2.Format(_T("%d"), posNum);
			// 소켓리스트, 클라이언트리스트를 비교해서 같은게 있으면 delete
			if(str1.Find(str2) != -1) {
				AfxMessageBox(str1 + str2);
				pMain->clientList->DeleteString(indx);
				break;
			}
			indx ++;
		}

		m_ptrClientSocketList.RemoveAt(pos);

		delete pClient;
	}
}

void CListenSocket::SendSecretChatData(CString pszMessage)
{
	CClientSocket* pClient = NULL;
	UINT indx = 0, posNum;
	CString str1, str2;
	POSITION pos;
		
	pos = m_ptrClientSocketList.GetHeadPosition();
	CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
	indx = pMain->clientList->GetCurSel();
	pMain->clientList->GetText(indx, str1);
	while(pos != NULL) {
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		posNum = (int)m_ptrClientSocketList.Find(pClient); 
		str2.Format(_T("%d"), posNum);
		if(str1.Find(str2) != -1) {
			AfxMessageBox(str1+str2);
			if(pClient != NULL) {
				int checkLenOfData = pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
				if(checkLenOfData != lstrlen(pszMessage) * 2) {
					AfxMessageBox(_T("일부 데이터가 정상적을 전송되지 못했습니다!"));
				}
			}
			break;
		}
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