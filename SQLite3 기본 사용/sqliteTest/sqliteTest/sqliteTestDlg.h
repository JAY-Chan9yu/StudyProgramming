
// sqliteTestDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CsqliteTestDlg ��ȭ ����
class CsqliteTestDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CsqliteTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	void scanDB();
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SQLITETEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox viewDB;
};
