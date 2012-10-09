// CreateProjectDlg.h : header file
//

#if !defined(AFX_CREATEPROJECTDLG_H__7656953A_F0BC_45BB_BCAF_A96F9140C5DF__INCLUDED_)
#define AFX_CREATEPROJECTDLG_H__7656953A_F0BC_45BB_BCAF_A96F9140C5DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectDlg dialog

class CCreateProjectDlg : public CDialog
{
// Construction
public:
	CCreateProjectDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateProjectDlg)
	enum { IDD = IDD_CREATEPROJECT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateProjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCreateProjectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCreate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEPROJECTDLG_H__7656953A_F0BC_45BB_BCAF_A96F9140C5DF__INCLUDED_)
