
// MFC_Listbox_test2Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMFC_Listbox_test2Dlg ��ȭ ����
class CMFC_Listbox_test2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFC_Listbox_test2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFC_LISTBOX_TEST2_DIALOG };

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
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedInsertBtn();
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedUpBtn();
	afx_msg void OnBnClickedDown();
private:
	CListBox m_name_list;
};
