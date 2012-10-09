// CreateProject.h : main header file for the CREATEPROJECT application
//

#if !defined(AFX_CREATEPROJECT_H__BA898ADD_05F2_4451_B3F3_B026AE3B455E__INCLUDED_)
#define AFX_CREATEPROJECT_H__BA898ADD_05F2_4451_B3F3_B026AE3B455E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectApp:
// See CreateProject.cpp for the implementation of this class
//

class CCreateProjectApp : public CWinApp
{
public:
	CCreateProjectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateProjectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCreateProjectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEPROJECT_H__BA898ADD_05F2_4451_B3F3_B026AE3B455E__INCLUDED_)
