
// ChatServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"

// CChatServerDlg 대화 상자
class CChatServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CChatServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	void OnDestroy();
	CListenSocket m_ListenSocket;
	CListBox* clientList;
	CEdit* textBuffer[8]; // Text이름 설정 관련 
	char testA;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	
public:
	CListBox m_List;
	afx_msg void OnBnClickedMessageBtn();
};
