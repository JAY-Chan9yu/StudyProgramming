
// ChatClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "ConnectSocket.h"

// CChatClientDlg ��ȭ ����
class CChatClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChatClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CConnectSocket m_Socket;
	int SendDataFlag;
	void SendData();
	
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHATCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void SetTImerStart();


	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	afx_msg void OnBnClickedButtonSend();
	CEdit m_strMessageT;
	CString m_test;
	CEdit m_testedit;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	LRESULT OnThemeChanged();
//	afx_msg void OnTimeChange();
};