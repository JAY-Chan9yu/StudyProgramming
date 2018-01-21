#pragma once

// CListenSocket ��� ����Դϴ�.
//#include "ChatServerDlg.h"
class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendChatDataAll(TCHAR* pszMessage);
	void SendSecretChatData(CString pszMessage);

	bool acceptFlag;
	CStringList clientList;
	CPtrList m_ptrClientSocketList;	// ����� CClientSocketŬ���� ��ü�� ��ũ�帮��Ʈ�� �����ϴ� ���
};