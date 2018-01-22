// ListenSocket.cpp : ���� �����Դϴ�.
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

// ������ ������ ��ٸ��� Ư�� ��Ʈ�� Ŭ���̾�Ʈ�� TCP ������ ������ �ڵ����� ȣ��
// ���Լ��� ȣ��Ǹ� ���ο� Ŭ���̾�Ʈ ������ ������ ���� ������ �������� ��������
void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket;
	CString str;
	
	if(Accept(*pClient)) {
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
		
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		str.Format(_T("Client (%d)"), (int)m_ptrClientSocketList.Find(pClient)); // Ŭ���̾�Ʈ ��ȣ(POSITION ��)
		clientList.AddTail(str);
		pMain->clientList->AddString(str); // Ŭ���̾�Ʈ�� �����Ҷ����� ����Ʈ�� Ŭ���̾�Ʈ �̸� �߰�
		AfxMessageBox(str + _T("�� �����Ͽ����ϴ�"));
	} else {
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

// Ŭ���̾�Ʈ ���� �����Լ�
void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);
	
	if(pos != NULL) {
		if(pClient != NULL) {
			// Ŭ���̾�Ʈ ���������� ����
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
			// ���ϸ���Ʈ, Ŭ���̾�Ʈ����Ʈ�� ���ؼ� ������ ������ delete
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
					AfxMessageBox(_T("�Ϻ� �����Ͱ� �������� ���۵��� ���߽��ϴ�!"));
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
			// Send�Լ��� �ι�° ���ڴ� �޸��� ũ���ε� �����ڵ带 ����ϰ� �����Ƿ� *2�� �� ũ�Ⱑ �ȴ�.
			// �� �Լ��� ������ �������� ���̸� ��ȯ�Ѵ�.
			int checkLenOfData = pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
			if(checkLenOfData != lstrlen(pszMessage) * 2) {
				AfxMessageBox(_T("�Ϻ� �����Ͱ� �������� ���۵��� ���߽��ϴ�!"));
			}
		}
	}
}