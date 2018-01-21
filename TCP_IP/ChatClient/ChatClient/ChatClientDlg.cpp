﻿
// ChatClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CChatClientDlg 대화 상자



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatClientDlg::IDD, pParent)
	, m_test(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//DDX_Control(pDX, IDC_EDIT5, m_strMessageT);
	
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Button_Send, &CChatClientDlg::OnBnClickedButtonSend)
	ON_WM_TIMER()
//	ON_WM_THEMECHANGED()
//	ON_WM_TIMECHANGE()
END_MESSAGE_MAP()


// CChatClientDlg 메시지 처리기

BOOL CChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SendDataFlag = 0;
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Socket.Create();
	if(m_Socket.Connect(_T("127.0.0.1"), 21000) == FALSE) {
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
		return FALSE;
	}
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChatClientDlg::OnPaint()
{

	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChatClientDlg::SetTImerStart()
{
	SetTimer(1,1000,NULL);
}

void CChatClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1) SendData();
	CDialogEx::OnTimer(nIDEvent);
}


void CALLBACK TestCallbackSend(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime)
{
	// 콜백함수는 Dlg클래스의 멤버함수가 아니기 때문에 Dlg포인터를 선언하여 사용한다.
	CChatClientDlg* chatDlg = (CChatClientDlg*)CDialogEx::FromHandle(hWnd); // 초기화 필수
	chatDlg->SendData();
}

void CChatClientDlg::OnBnClickedButtonSend()
{
	CString str;
	
	if(SendDataFlag == 0) {
		SendDataFlag = 1; // send data flag가 1일때 데이터 전송
		//SetTimer(1,1000,NULL);
		SetTimer(2,1000,(TIMERPROC)TestCallbackSend);
	} else if(SendDataFlag == 1) {
		SendDataFlag = 0;
		//KillTimer(1);	
		KillTimer(2);	
	}
	
	/*// 방법1, 리소스뷰에서 만든 거 그대로 쓸때
	UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT5, str );   
	m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	str.Format(_T(""));
	SetDlgItemText( IDC_EDIT5, str );
	UpdateData(FALSE);*/
	
	// 방법2. 객체생성해서 쓸때
	/*CEdit* test = (CEdit*)GetDlgItem(IDC_EDIT5);
	test->GetWindowTextW(str);
	m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	test->SetWindowTextW(_T(""));*/
}

void CChatClientDlg::SendData() 
{
	CString str;
	WORD Word = 0x1234;
	str.Format(_T("%x:%x:%x:%x"), Word, Word, Word, Word);
	m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength()*2);

	/*CEdit* test = (CEdit*)GetDlgItem(IDC_EDIT5);
	test->GetWindowTextW(str);
	m_Socket.Send((LPVOID)(LPCTSTR)str, str.GetLength() * 2);
	test->SetWindowTextW(_T(""));*/

}

