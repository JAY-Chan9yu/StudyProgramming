// ListenSocket.cpp : ���� �����Դϴ�.
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

// CListenSocket ��� �Լ�

// ������ ������ ��ٸ��� Ư�� ��Ʈ�� Ŭ���̾�Ʈ�� TCP ������ ������ �ڵ����� ȣ��
// ���Լ��� ȣ��Ǹ� ���ο� Ŭ���̾�Ʈ ������ ������ ���� ������ �������� ��������
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
			// Send�Լ��� �ι�° ���ڴ� �޸��� ũ���ε� �����ڵ带 ����ϰ� �����Ƿ� *2�� �� ũ�Ⱑ �ȴ�.
			// �� �Լ��� ������ �������� ���̸� ��ȯ�Ѵ�.
			int checkLenOfData = pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
			if(checkLenOfData != lstrlen(pszMessage) * 2) {
				AfxMessageBox(_T("�Ϻ� �����Ͱ� �������� ���۵��� ���߽��ϴ�!"));
			}
		}
	}
}