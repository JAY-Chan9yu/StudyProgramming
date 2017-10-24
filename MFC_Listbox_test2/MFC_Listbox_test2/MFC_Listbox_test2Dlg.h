
// MFC_Listbox_test2Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CMFC_Listbox_test2Dlg 대화 상자
class CMFC_Listbox_test2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_Listbox_test2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFC_LISTBOX_TEST2_DIALOG };

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
public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedInsertBtn();
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedUpBtn();
	afx_msg void OnBnClickedDown();
private:
	CListBox m_name_list;
};
