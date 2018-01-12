#pragma once

// CListenSocket ��� ����Դϴ�.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendChatDataAll(TCHAR* pszMessage);

	CPtrList	m_ptrClientSocketList;	// ����� CClientSocketŬ���� ��ü�� ��ũ�帮��Ʈ�� �����ϴ� ���
	
};