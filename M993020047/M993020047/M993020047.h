// M993020047.h : main header file for the M993020047 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CM993020047App:
// See M993020047.cpp for the implementation of this class
//

class CM993020047App : public CWinApp
{
public:
	CM993020047App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CM993020047App theApp;