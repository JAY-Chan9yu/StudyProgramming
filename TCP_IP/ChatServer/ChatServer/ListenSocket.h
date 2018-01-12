#pragma once

// CListenSocket 명령 대상입니다.

class CListenSocket : public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	void OnAccept(int nErrorCode);
	void CloseClientSocket(CSocket* pClient);
	void SendChatDataAll(TCHAR* pszMessage);

	CPtrList	m_ptrClientSocketList;	// 연결된 CClientSocket클래스 객체를 링크드리스트로 관리하는 멤버
	
};