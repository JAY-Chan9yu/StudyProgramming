
// htmlView.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// ChtmlViewApp:
// �� Ŭ������ ������ ���ؼ��� htmlView.cpp�� �����Ͻʽÿ�.
//

class ChtmlViewApp : public CWinApp
{
public:
	ChtmlViewApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern ChtmlViewApp theApp;