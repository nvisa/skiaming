// Order.h : main header file for the ORDER application
//

#if !defined(AFX_ORDER_H__13E1BB4D_ABC9_4575_B6C8_9F97B7A3E027__INCLUDED_)
#define AFX_ORDER_H__13E1BB4D_ABC9_4575_B6C8_9F97B7A3E027__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COrderApp:
// See Order.cpp for the implementation of this class
//

class COrderApp : public CWinApp
{
public:
	COrderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COrderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDER_H__13E1BB4D_ABC9_4575_B6C8_9F97B7A3E027__INCLUDED_)
