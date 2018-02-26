
// calc_Expression.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ccalc_ExpressionApp:
// See calc_Expression.cpp for the implementation of this class
//

class Ccalc_ExpressionApp : public CWinApp
{
public:
	Ccalc_ExpressionApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ccalc_ExpressionApp theApp;