
// MFC_Listbox_test2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_Listbox_test2.h"
#include "MFC_Listbox_test2Dlg.h"
#include "afxdialogex.h"
#include "CppSQLite3U.h"
#include "XLEzAutomation.h"

#include <iostream>
	
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString DB_FILE_NAME	= _T("test.db");//tmp

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.s

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


// CMFC_Listbox_test2Dlg 대화 상자



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
	ON_BN_CLICKED(IDC_INSERT_BTN, &CMFC_Listbox_test2Dlg::OnBnClickedInsertBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, &CMFC_Listbox_test2Dlg::OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_UP_BTN, &CMFC_Listbox_test2Dlg::OnBnClickedUpBtn)
	ON_BN_CLICKED(IDC_DOWN, &CMFC_Listbox_test2Dlg::OnBnClickedDown)
	ON_LBN_DBLCLK(IDC_LIST1, &CMFC_Listbox_test2Dlg::OnLbnDblclkList1)
	ON_LBN_DBLCLK(IDC_LIST2, &CMFC_Listbox_test2Dlg::OnLbnDblclkList2)
	ON_BN_CLICKED(IDC_SAVEBTN, &CMFC_Listbox_test2Dlg::OnBnClickedSavebtn)
	ON_BN_CLICKED(IDC_EXCELBTN, &CMFC_Listbox_test2Dlg::OnBnClickedExcelbtn)
	ON_BN_CLICKED(IDC_VIEW_EXCEL, &CMFC_Listbox_test2Dlg::OnBnClickedViewExcel)
END_MESSAGE_MAP()


// CMFC_Listbox_test2Dlg 메시지 처리기

BOOL CMFC_Listbox_test2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	scanDB();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_Listbox_test2Dlg::OnPaint()
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

// DB에서 데이터를 읽어서 리스트에 뿌려줌(더해줌)
void CMFC_Listbox_test2Dlg::scanDB()
{
	CString sTmp;
	CListBox* pListPage;

	CppSQLite3DB db;

	try {
		db.open(DB_FILE_NAME);
	
		sTmp.Format(_T("select name, region from customer;"));
		CppSQLite3Query q = db.execQuery(sTmp);
		
		while (!q.eof()) {	
			CString nIdx = q.getStringField(0);	
			sTmp.Format(_T("%s"), nIdx);
			m_name_list.AddString(sTmp);
			q.nextRow();
		}		
	} catch (CppSQLite3Exception &e) {
		m_name_list.AddString(_T("에러"));
	}

	db.close();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFC_Listbox_test2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 클릭한 아이템을 추가하는 버튼
void CMFC_Listbox_test2Dlg::OnBnClickedInsertBtn()
{
	CString sTmp;
	if(m_name_list.GetCurSel() < 0) return;

	// 마우스 커서를 모래시계로 변환
	BeginWaitCursor();

	try {
		m_name_list.GetText(m_name_list.GetCurSel(), sTmp);
		m_move_list.AddString(sTmp);
	}catch (CppSQLite3Exception& e) {
		m_move_list.AddString(_T("에러"));
	}

	// 마우스 커서를 기본 커서로 변환
	EndWaitCursor();
}

// 클릭한 아이템을 제거하는 버튼
void CMFC_Listbox_test2Dlg::OnBnClickedDeleteBtn()
{
	CString sTmp;
	if(m_move_list.GetCurSel() < 0) return;
	BeginWaitCursor();

	try {
		m_move_list.DeleteString(m_move_list.GetCurSel());
	}catch (CppSQLite3Exception& e) {
		m_move_list.AddString(_T("에러"));
	}

	EndWaitCursor();
}

// 아이템의 순서를 위로 올려주는 버튼
void CMFC_Listbox_test2Dlg::OnBnClickedUpBtn()
{
	CString sTmp, tmpText;
	if(m_move_list.GetCurSel() < 0) return;
	int curSelPos = m_move_list.GetCurSel(); // 커서 위치 저장

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
		m_move_list.AddString(_T("에러"));
	}

	if(curSelPos != 0) m_move_list.SetCurSel(curSelPos - 1); // 커서셀 한 칸 위로이동
	EndWaitCursor();
}

// 아이템의 순서를 아래로 내려주는 버튼
void CMFC_Listbox_test2Dlg::OnBnClickedDown()
{
	CString sTmp, tmpText;
	if(m_move_list.GetCurSel() < 0) return;
	int curSelPos = m_move_list.GetCurSel(); // 커서 위치 저장

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
		m_move_list.AddString(_T("에러"));
	}

	m_move_list.SetCurSel(curSelPos + 1); // 커서셀 한 칸 위로이동
	EndWaitCursor();
}

// 왼쪽 리스트뷰 더블클릭 이벤트
void CMFC_Listbox_test2Dlg::OnLbnDblclkList1()
{
	OnBnClickedInsertBtn();
}

// 오른쪽 리스트뷰 더블클릭 이벤트
void CMFC_Listbox_test2Dlg::OnLbnDblclkList2()
{
	OnBnClickedDeleteBtn();
}

// 리스트 내용 DB로 저장하기
void CMFC_Listbox_test2Dlg::OnBnClickedSavebtn()
{
	sqlite3 *db;
	int retv;

    CString db_path = _T("saveDB.db") ;
	// LPSTR(LPCTSTR(db_path) CString을 char*로 변환해주는 코드(내용 찾아보기)
    retv = sqlite3_open(LPSTR(LPCTSTR(db_path)), &db);// open database			

	CppSQLite3DB sdb;
	try {
		sdb.open(_T("saveDB.db"));
		sdb.execDML(_T("CREATE TABLE IF NOT EXISTS People(name VARCHAR(20));"));	

		CString sTmp, sList;
		CppSQLite3Query q;
		for(int i = 0; i < m_move_list.GetCount(); i++) {
			m_move_list.GetText(i, sList);
			sTmp.Format(_T("insert into People (name) values ('%s');"), sList);
			q = sdb.execQuery(sTmp);
		}
	} catch(CppSQLite3Exception & e) {

	}		
}

void CMFC_Listbox_test2Dlg::OnBnClickedExcelbtn()
{
	char chThisPath[_MAX_PATH];
    GetCurrentDirectory( _MAX_PATH, LPWSTR((chThisPath)));
    
    UpdateData(TRUE);
    CString strThisPath ;
    strThisPath.Format(_T("testEE.xlsx"));

    CXLEzAutomation XL(FALSE); // FALSE: 처리 과정을 화면에 보이지 않는다
	
	CString sList;
	for(int i = 0; i < m_move_list.GetCount(); i++) {
		m_move_list.GetText(i, sList);
		XL.SetCellValue(1,i,sList);	
	}
    XL.SaveFileAs(strThisPath);

    XL.ReleaseExcel();
}

// 엑셀에 저장된 내용 보기
void CMFC_Listbox_test2Dlg::OnBnClickedViewExcel()
{
	 char chThisPath[_MAX_PATH];
	 GetCurrentDirectory( _MAX_PATH, LPWSTR(chThisPath));
	 UpdateData(TRUE);

	 CString strThisPath ;
	 CString strData;
	 strThisPath.Format(_T("E:\\Documents\\Documents\\Visual Studio 2012\\Projects\\MFC_Listbox_test2\\MFC_Listbox_test2\\TEST.xls"));
	 GetModuleFileName( NULL, LPWSTR(chThisPath), _MAX_PATH);

	 CXLEzAutomation XL(FALSE); // FALSE: 처리 과정을 화면에 보이지 않는다
	 XL.OpenExcelFile(strThisPath);
	 /*for(int i = 0; i < m_move_list.GetCount(); i++) {

	 }*/

	 strData +="\n(1,1) = ";
	 strData +=XL.GetCellValue(1,1);
	 strData +="\n(1,2) = ";
	 strData +=XL.GetCellValue(1,2);
	 strData +="\n(1,3) = ";
	 strData +=XL.GetCellValue(1,3);
	 strData +="\n(1,4) = ";
	 strData +=XL.GetCellValue(1,4);
	 strData +="\n(4,4) = ";
	 strData +=XL.GetCellValue(4,4);
	 strData +="\n(7,4) = ";
	 strData +=XL.GetCellValue(7,4);
	 
	 XL.ReleaseExcel();

	 MessageBox(strData);	
}
