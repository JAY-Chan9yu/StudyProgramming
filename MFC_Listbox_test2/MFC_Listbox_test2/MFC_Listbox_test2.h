
// MFC_Listbox_test2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_Listbox_test2App:
// �� Ŭ������ ������ ���ؼ��� MFC_Listbox_test2.cpp�� �����Ͻʽÿ�.
//

class CMFC_Listbox_test2App : public CWinApp
{
public:
	CMFC_Listbox_test2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_Listbox_test2App theApp;