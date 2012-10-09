// CreateProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CreateProject.h"
#include "CreateProjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectDlg dialog

CCreateProjectDlg::CCreateProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateProjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateProjectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateProjectDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateProjectDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateProjectDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, OnButtonCreate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateProjectDlg message handlers

BOOL CCreateProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString sAppPath;
	GetModuleFileName(NULL, sAppPath.GetBuffer(MAX_PATH), MAX_PATH);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCreateProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCreateProjectDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCreateProjectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCreateProjectDlg::OnButtonCreate() 
{
	// TODO: Add your control notification handler code here
	CString sProjectName;
	GetDlgItem(IDC_EDIT)->GetWindowText(sProjectName);
	CString sAppPath;
	GetModuleFileName(NULL, sAppPath.GetBuffer(MAX_PATH), MAX_PATH);
	sAppPath.ReleaseBuffer();
	CString sAppFolder = sAppPath.Left(sAppPath.ReverseFind('\\'));
	//dsp
	CString sDSP = sAppFolder + "\\" + sProjectName + ".dsp";
	CString sDSW = sAppFolder + "\\" + sProjectName + ".dsw";
	CString sTestDSP = sAppFolder + "\\" + "test.dsp";
	CString sTestDSW = sAppFolder + "\\" + "test.dsw";
	CFileFind filefind;
	if(!(filefind.FindFile(sTestDSP) && filefind.FindFile(sTestDSW)))
	{
		MessageBox("test.dsw and test.dsp file can't be found!", "Warning", MB_OK | MB_ICONWARNING);
		return;
	}
	CFile fDSP(sDSP, CFile::modeCreate | CFile::modeRead | CFile::modeWrite);
	CFile fTestDSP(sTestDSP, CFile::modeRead);
	DWORD dTestDSPLength = fTestDSP.GetLength();
	CString sWritingDSP;
	fTestDSP.Read(sWritingDSP.GetBuffer(dTestDSPLength), dTestDSPLength);
	sWritingDSP.ReleaseBuffer();
	sWritingDSP.Replace("test", sProjectName);
	fDSP.Write(sWritingDSP.GetBuffer(sWritingDSP.GetLength()), sWritingDSP.GetLength());
	sWritingDSP.ReleaseBuffer();
	fDSP.Close();
	fTestDSP.Close();
	CFile fDSW(sDSW, CFile::modeCreate | CFile::modeRead | CFile::modeWrite);
	CFile fTestDSW(sTestDSW, CFile::modeRead);
	DWORD dTestDSWLength = fTestDSW.GetLength();
	CString sWritingDSW;
	fTestDSW.Read(sWritingDSW.GetBuffer(dTestDSWLength), dTestDSWLength);
	sWritingDSW.ReleaseBuffer();
	sWritingDSW.Replace("test", sProjectName);
	fDSW.Write(sWritingDSW.GetBuffer(sWritingDSW.GetLength()), sWritingDSW.GetLength());
	sWritingDSW.ReleaseBuffer();
	fDSW.Close();
	fTestDSW.Close();
	MessageBox("Sucess!", "Over", MB_OK);
}
