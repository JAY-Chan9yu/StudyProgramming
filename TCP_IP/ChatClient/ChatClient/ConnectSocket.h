#pragma once

// CConnectSocket ��� ����Դϴ�.

class CConnectSocket : public CSocket
{
public:
	CConnectSocket();
	virtual ~CConnectSocket();
	void OnClose(int nErrorCode);
	void OnReceive(int nErrorCode);
};


