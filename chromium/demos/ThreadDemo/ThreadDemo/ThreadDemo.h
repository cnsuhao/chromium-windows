// ThreadDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "base/tracked_objects.h"
// CThreadDemoApp:
// See ThreadDemo.cpp for the implementation of this class
//

class CThreadDemoApp : public CWinApp
{
	friend class tracked_objects::ThreadData;
public:
	CThreadDemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CThreadDemoApp theApp;