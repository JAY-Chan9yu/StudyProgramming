
// sqliteTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CsqliteTestApp:
// �� Ŭ������ ������ ���ؼ��� sqliteTest.cpp�� �����Ͻʽÿ�.
//

class CsqliteTestApp : public CWinApp
{
public:
	CsqliteTestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CsqliteTestApp theApp;