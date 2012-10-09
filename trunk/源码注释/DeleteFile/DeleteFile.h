// DeleteFile.h : main header file for the DELETEFILE application
//

#if !defined(AFX_DELETEFILE_H__24E4B47C_76E3_46AD_B21E_BD8488D1BA8B__INCLUDED_)
#define AFX_DELETEFILE_H__24E4B47C_76E3_46AD_B21E_BD8488D1BA8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDeleteFileApp:
// See DeleteFile.cpp for the implementation of this class
//

class CDeleteFileApp : public CWinApp
{
public:
	CDeleteFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDeleteFileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEFILE_H__24E4B47C_76E3_46AD_B21E_BD8488D1BA8B__INCLUDED_)
