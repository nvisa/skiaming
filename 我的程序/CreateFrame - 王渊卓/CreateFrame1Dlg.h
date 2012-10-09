// CreateFrame1Dlg.h : header file
//

#if !defined(AFX_CREATEFRAME1DLG_H__88004050_DFCF_45C6_BAE5_66E952462119__INCLUDED_)
#define AFX_CREATEFRAME1DLG_H__88004050_DFCF_45C6_BAE5_66E952462119__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCreateFrame1Dlg dialog

class CCreateFrame1Dlg : public CDialog
{
// Construction
public:
	BOOL AltFileName(CString strSourecFile, CString strDesFile );
	CCreateFrame1Dlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	//{{AFX_DATA(CCreateFrame1Dlg)
	enum { IDD = IDD_CREATEFRAME1_DIALOG };
	CString	m_projectName;
	CString	m_locationDir;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateFrame1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCreateFrame1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditProjectName();
	afx_msg void OnBtnCreatefiles();
	afx_msg void OnBtnChoosedir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEFRAME1DLG_H__88004050_DFCF_45C6_BAE5_66E952462119__INCLUDED_)
