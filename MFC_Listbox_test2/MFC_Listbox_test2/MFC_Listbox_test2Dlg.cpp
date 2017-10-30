
// MFC_Listbox_test2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_Listbox_test2.h"
#include "MFC_Listbox_test2Dlg.h"
#include "afxdialogex.h"
#include "CppSQLite3U.h"
#include <iostream>
	
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString DB_FILE_NAME	= _T("test.db");//tmp

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_Listbox_test2Dlg ��ȭ ����



CMFC_Listbox_test2Dlg::CMFC_Listbox_test2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_Listbox_test2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Listbox_test2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_name_list);
	DDX_Control(pDX, IDC_LIST2, m_move_list);
}

BEGIN_MESSAGE_MAP(CMFC_Listbox_test2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFC_Listbox_test2Dlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMFC_Listbox_test2Dlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_INSERT_BTN, &CMFC_Listbox_test2Dlg::OnBnClickedInsertBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, &CMFC_Listbox_test2Dlg::OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_UP_BTN, &CMFC_Listbox_test2Dlg::OnBnClickedUpBtn)
	ON_BN_CLICKED(IDC_DOWN, &CMFC_Listbox_test2Dlg::OnBnClickedDown)
	ON_LBN_DBLCLK(IDC_LIST1, &CMFC_Listbox_test2Dlg::OnLbnDblclkList1)
	ON_LBN_DBLCLK(IDC_LIST2, &CMFC_Listbox_test2Dlg::OnLbnDblclkList2)
END_MESSAGE_MAP()


// CMFC_Listbox_test2Dlg �޽��� ó����

BOOL CMFC_Listbox_test2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ���� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_name_list.AddString(L"�׽�Ʈ");
	m_name_list.AddString(L"������");
	m_name_list.AddString(L"����");
	scanDB();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMFC_Listbox_test2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_Listbox_test2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// DB���� �����͸� �о ����Ʈ�� �ѷ���(������)
void CMFC_Listbox_test2Dlg::scanDB()
{
	CString sTmp;
	CListBox* pListPage;

	CppSQLite3DB db;
	try {
		db.open(DB_FILE_NAME);
	
		sTmp.Format(_T("select name, region from customer;"));
		CppSQLite3Query q = db.execQuery(sTmp);
		while (!q.eof())
        {	
			CString nIdx = q.getStringField(0);	
			sTmp.Format(_T("%s"), nIdx);
			m_name_list.AddString(sTmp);
			q.nextRow();
		}
		
	} catch (CppSQLite3Exception& e) {
		m_name_list.AddString(_T("����"));
	}

	db.close();
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFC_Listbox_test2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// DB�� �ִ� ������ �����ִ� ����Ʈ �ڽ�
void CMFC_Listbox_test2Dlg::OnLbnSelchangeList1()
{
}

// �������� �߰� ������ ����Ʈ �ڽ�, ���������� DB�� �����ؼ� ������
void CMFC_Listbox_test2Dlg::OnLbnSelchangeList2()
{

}

// Ŭ���� �������� �߰��ϴ� ��ư
void CMFC_Listbox_test2Dlg::OnBnClickedInsertBtn()
{
	CString sTmp;
	if(m_name_list.GetCurSel() < 0) return;
	BeginWaitCursor();

	try {
		m_name_list.GetText(m_name_list.GetCurSel(), sTmp);
		m_move_list.AddString(sTmp);
	}catch (CppSQLite3Exception& e) {
		m_move_list.AddString(_T("����"));
	}

	EndWaitCursor();
}

// Ŭ���� �������� �����ϴ� ��ư
void CMFC_Listbox_test2Dlg::OnBnClickedDeleteBtn()
{
	CString sTmp;
	if(m_move_list.GetCurSel() < 0) return;
	BeginWaitCursor();

	try {
		m_move_list.DeleteString(m_move_list.GetCurSel());
	}catch (CppSQLite3Exception& e) {
		m_move_list.AddString(_T("����"));
	}

	EndWaitCursor();
}

// �������� ������ ���� �÷��ִ� ��ư
void CMFC_Listbox_test2Dlg::OnBnClickedUpBtn()
{
	CString sTmp, tmpText;
	if(m_move_list.GetCurSel() < 0) return;
	int curSelPos = m_move_list.GetCurSel(); // Ŀ�� ��ġ ����

	BeginWaitCursor();

	try {
		if(curSelPos > 0) {
			m_move_list.GetText(m_move_list.GetCurSel() - 1, tmpText);
			m_move_list.GetText(m_move_list.GetCurSel(), sTmp);

			m_move_list.DeleteString(curSelPos - 1);
			m_move_list.InsertString(curSelPos - 1, sTmp);

			m_move_list.DeleteString(curSelPos);
			m_move_list.InsertString(curSelPos, tmpText);
		}
	} catch (CppSQLite3Exception& e) {
		m_move_list.AddString(_T("����"));
	}

	if(curSelPos != 0) m_move_list.SetCurSel(curSelPos - 1); // Ŀ���� �� ĭ �����̵�
	EndWaitCursor();
}

// �������� ������ �Ʒ��� �����ִ� ��ư
void CMFC_Listbox_test2Dlg::OnBnClickedDown()
{
	CString sTmp, tmpText;
	if(m_move_list.GetCurSel() < 0) return;
	int curSelPos = m_move_list.GetCurSel(); // Ŀ�� ��ġ ����

	BeginWaitCursor();

	try {
		if(curSelPos + 1 < m_move_list.GetCount()) {
			m_move_list.GetText(curSelPos + 1, tmpText);
			m_move_list.GetText(curSelPos, sTmp);

			m_move_list.DeleteString(curSelPos + 1);
			m_move_list.InsertString(curSelPos + 1, sTmp);
			m_move_list.DeleteString(curSelPos);
			m_move_list.InsertString(curSelPos, tmpText);
			
		}
	} catch (CppSQLite3Exception& e) {
		m_move_list.AddString(_T("����"));
	}

	m_move_list.SetCurSel(curSelPos + 1); // Ŀ���� �� ĭ �����̵�
	EndWaitCursor();
}

void CMFC_Listbox_test2Dlg::OnLbnDblclkList1()
{
	OnBnClickedInsertBtn();
}


void CMFC_Listbox_test2Dlg::OnLbnDblclkList2()
{
	OnBnClickedDeleteBtn();
}