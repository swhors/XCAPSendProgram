// XCAPSendProgram.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CXCAPSendProgramApp:
// �� Ŭ������ ������ ���ؼ��� XCAPSendProgram.cpp�� �����Ͻʽÿ�.
//

class CXCAPSendProgramApp : public CWinApp
{
public:
	CXCAPSendProgramApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CXCAPSendProgramApp theApp;