// CreateFrame1.h : main header file for the CREATEFRAME1 application
//

#if !defined(AFX_CREATEFRAME1_H__DC049D90_3BB8_4225_B847_492D67C6856F__INCLUDED_)
#define AFX_CREATEFRAME1_H__DC049D90_3BB8_4225_B847_492D67C6856F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreateFrame1App:
// See CreateFrame1.cpp for the implementation of this class
//

class CCreateFrame1App : public CWinApp
{
public:
	CCreateFrame1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateFrame1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCreateFrame1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEFRAME1_H__DC049D90_3BB8_4225_B847_492D67C6856F__INCLUDED_)
