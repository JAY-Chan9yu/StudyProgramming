#pragma once

// CConnectSocket 명령 대상입니다.

class CConnectSocket : public CSocket
{
public:
	CConnectSocket();
	virtual ~CConnectSocket();
	void OnClose(int nErrorCode);
	void OnReceive(int nErrorCode);
};


