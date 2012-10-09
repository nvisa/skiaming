// CreateFrame1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CreateFrame1.h"
#include "CreateFrame1Dlg.h"

#include "InitString.h"

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
// CCreateFrame1Dlg dialog

CCreateFrame1Dlg::CCreateFrame1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateFrame1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateFrame1Dlg)
	m_projectName = _T("");
	m_locationDir = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CCreateFrame1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateFrame1Dlg)
	DDX_Text(pDX, IDC_EDIT_PROJECT_NAME, m_projectName);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_locationDir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateFrame1Dlg, CDialog)
	//{{AFX_MSG_MAP(CCreateFrame1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_PROJECT_NAME, OnChangeEditProjectName)
	ON_BN_CLICKED(IDC_BTN_CREATEFILES, OnBtnCreatefiles)
	ON_BN_CLICKED(IDC_BTN_CHOOSEDIR, OnBtnChoosedir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateFrame1Dlg message handlers

BOOL CCreateFrame1Dlg::OnInitDialog()
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
//DocProcess_DLL.dsp存入变量
	strDspDLL1 += strDspDLL2;
	strDspDLL1 += strDspDLL3;
	strRCDLL1 += strRCDLL2;
	strDspLIB1 += strDspLIB2;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCreateFrame1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCreateFrame1Dlg::OnPaint() 
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
HCURSOR CCreateFrame1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCreateFrame1Dlg::OnChangeEditProjectName() 
{
	// 实现IDC_LOACTION的目录名同步
	int iInsert = m_locationDir.ReverseFind('\\') ;
	int iLength = m_locationDir.GetLength();
	
	UpdateData();
	if(m_projectName.Find('\\') >= 0)
	{
		AfxMessageBox("Please make sure the project name is legality!");
		return ;
	}
	m_locationDir.Delete(iInsert+1,iLength - iInsert - 1);
	m_locationDir += m_projectName;
	UpdateData(FALSE);
}

void CCreateFrame1Dlg::OnBtnCreatefiles() 
{
	
	UpdateData();
	CFileFind   finder; 
	BOOL   bWorking   =   finder.FindFile( m_locationDir);//把参数用你的字符串代替 
	if(bWorking) 
	{ 
			AfxMessageBox( "Folder exist,Please choose another!"); 
			return;
	} 

	if (m_locationDir.Find(':') < 1)
	{
		AfxMessageBox("Folder path invalidte,please choose another!");
		return;
	}
	if (!CreateDirectory(m_locationDir,NULL))
	{
		AfxMessageBox("Failed create folder,please set correct path!");
		return;
	}

	//创建include文件夹
	m_locationDir += "\\";
	int iInsert = m_locationDir.ReverseFind('\\') ;
	m_locationDir += "include";
	CreateDirectory(m_locationDir,NULL);
	AltFileName(strH,m_locationDir+"\\"+m_projectName+".h");
	//创建res文件夹
	int iLength = m_locationDir.GetLength();
	m_locationDir.Delete(iInsert+1,iLength - iInsert - 1);
	m_locationDir += "res";
	CreateDirectory(m_locationDir,NULL);
	AltFileName(strRCDLL1,m_locationDir+"\\"+m_projectName+"_DLL.rc");
	AltFileName(strRHDLL,m_locationDir+"\\resource.h");
	m_locationDir += "\\res";
	CreateDirectory(m_locationDir,NULL);
	AltFileName(strRC2DLL,m_locationDir+"\\"+m_projectName+"_DLL.rc2");

	//创建src文件夹
	iLength = m_locationDir.GetLength();
	m_locationDir.Delete(iInsert+1,iLength - iInsert - 1);
	m_locationDir += "src";
	CreateDirectory(m_locationDir,NULL);
	AltFileName(strCpp,m_locationDir+"\\"+m_projectName+".cpp");

	//创建DLL文件夹
	iLength = m_locationDir.GetLength();
	m_locationDir.Delete(iInsert+1,iLength - iInsert - 1);
	m_locationDir += m_projectName+"_DLL";
	CreateDirectory(m_locationDir,NULL);
	AltFileName(strDspDLL1,m_locationDir+"\\"+m_projectName+"_DLL.dsp");
	AltFileName(strClwDLL,m_locationDir+"\\"+m_projectName+"_DLL.clw");
	AltFileName(strDefDLL,m_locationDir+"\\"+m_projectName+"_DLL.def");
 	AltFileName(strHDLL,m_locationDir+"\\"+m_projectName+"_DLL.h");
 	AltFileName(strCppDLL,m_locationDir+"\\"+m_projectName+"_DLL.cpp");
 	AltFileName(strStdHDLL,m_locationDir+"\\StdAfx.h");
 	AltFileName(strStdCppDLL,m_locationDir+"\\StdAfx.cpp");

	//创建LIB文件夹
	iLength = m_locationDir.GetLength();
	m_locationDir.Delete(iInsert+1,iLength - iInsert - 1);
	m_locationDir += m_projectName+"_LIB";
	CreateDirectory(m_locationDir,NULL);
	AltFileName(strDspLIB1,m_locationDir+"\\"+m_projectName+".dsp");

	iLength = m_locationDir.GetLength();
	m_locationDir.Delete(iInsert+1,iLength - iInsert - 1);
	AfxMessageBox("Success to create module!");

}

BOOL CCreateFrame1Dlg::AltFileName(CString strSourecFile, CString strDesFile )
{

	CStdioFile desFile;
	CFileException ex;

	if (!desFile.Open(strDesFile,CFile::modeWrite |
		CFile::shareExclusive | CFile::modeCreate,&ex))
	{
		TCHAR szError[1024];
		ex.GetErrorMessage(szError,1024);
		return FALSE;
	}
	else
	{
		strSourecFile.Replace("DocProcess",m_projectName);
		desFile.WriteString(strSourecFile);
		desFile.WriteString("\n");
		desFile.Close();
	}
	return TRUE;
}



void CCreateFrame1Dlg::OnBtnChoosedir() 
{
	// TODO: Add your control notification handler code here
	BROWSEINFO bi;
	char szPathName[MAX_PATH];
	char szTitle[] = "Choose path";
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.pszDisplayName = szPathName;
	bi.lpszTitle = szTitle;
	bi.ulFlags = 0x0040 ; 
	CString str;
	CString strDir; //选择的目录 

	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
	{
		 strDir= "";
		 return;
	}
	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH * 2));
	str.ReleaseBuffer();
	if(str != "" && str.GetAt(str.GetLength() - 1) != '\\')
	str += "\\";
	m_locationDir = str; 
	m_locationDir += m_projectName;
	UpdateData(FALSE);
}
