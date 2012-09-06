// DeleteFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DeleteFile.h"
#include "DeleteFileDlg.h"

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
// CDeleteFileDlg dialog

CDeleteFileDlg::CDeleteFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeleteFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteFileDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDeleteFileDlg, CDialog)
	//{{AFX_MSG_MAP(CDeleteFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON, &CDeleteFileDlg::OnBnClickedButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteFileDlg message handlers

BOOL CDeleteFileDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDeleteFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDeleteFileDlg::OnPaint() 
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
HCURSOR CDeleteFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void FindInAll(::LPCTSTR lpszPath);
void CDeleteFileDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString strFilePath;
	GetModuleFileName(NULL, strFilePath.GetBuffer(MAX_PATH), MAX_PATH);
	strFilePath.ReleaseBuffer();
	CString strFolder = strFilePath.Left(strFilePath.ReverseFind('\\'));
	FindInAll(strFolder);
	MessageBox("OK", NULL, MB_OK);
	
	return;
	CDialog::OnOK();
}









// 建立文件夹
BOOL CreateFolder(LPCTSTR lpszPath)
{
	CString strPath = lpszPath;
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
	return ::CreateDirectory(strPath, &attrib);
}
// 文件夹是否存在
BOOL FolderExist(LPCTSTR lpszPath)
{
	CString strPath = lpszPath;
	WIN32_FIND_DATA wfd;
	BOOL rValue = FALSE;
	HANDLE hFind = FindFirstFile(strPath, &wfd);
	if ((hFind!=INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;
	}
	FindClose(hFind);
	return rValue;
}
// 删除文件夹
bool DeleteDirectory(CString strDirPath)
{
	int iRet;
	CFileFind tempFind; 
	char tempFileFind[200]; 
	if(strDirPath.GetAt(strDirPath.GetLength()-1) != '\\')
	{
		strDirPath += "\\";
	}
	sprintf(tempFileFind,"%s*.*",(LPCTSTR)strDirPath); 
	
	BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind); 
	while(IsFinded) 
	{ 
		IsFinded=(BOOL)tempFind.FindNextFile(); 
		if(!tempFind.IsDots()) 
		{ 
			char foundFileName[200]; 
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(200)); 
			if(tempFind.IsDirectory()) 
			{ 
				char tempDir[200]; 
				sprintf(tempDir,"%s%s",(LPCTSTR)strDirPath,foundFileName); 
				DeleteDirectory(tempDir); 
			} 
			else 
			{ 
				char tempFileName[200]; 
				sprintf(tempFileName,"%s%s",(LPCTSTR)strDirPath,foundFileName); 
				SetFileAttributes(tempFileName,FILE_ATTRIBUTE_NORMAL);
				iRet = DeleteFile(tempFileName); 
				if(!iRet)
				{
					int err = GetLastError();
					printf("error");
				}
			} 
		} 
	} 
	tempFind.Close(); 
	if(!RemoveDirectory(strDirPath)) 
	{ 
		//        MessageBox(0,"删除目录失败！","警告信息",MK_OK); 
		return false; 
	} 
	return true; 
}

void DeleteFolder(LPCTSTR lpszPath)	//不正确
{
	if(FolderExist(lpszPath))
		RemoveDirectory(lpszPath);	//只能删除空文件
}
// 文件是否存在
BOOL FileExist(LPCTSTR lpszFilePath)
{
	CFileFind fFind;
	return fFind.FindFile(lpszFilePath);
}
// 文件名
CString GetFileName(LPCTSTR lpszFilePath)
{
CString FileName = lpszFilePath;
int n = FileName.ReverseFind('\\');
if(n>=0)
{
FileName = FileName.Right(FileName.GetLength()-n-1);
}
return FileName;
}
// 文件扩展名
CString GetFileExt(LPCTSTR lpszFilePath)
{
	CString FileName = GetFileName(lpszFilePath);
	int n = FileName.ReverseFind('.');
	if(n>=0)
	{
	return FileName.Right(FileName.GetLength()-n-1);
	}
	return _T("");
}
// 获取相对于当前Exe文件的绝对路径
/*
CString szPath = "\\Data";
GetAbsolutePath(szPath);
如果当前Exe文件的路径为   C:\Demo\Debug
那么szPath返回的结果就是 C:\Demo\Debug\Data
*/
void GetAbsolutePath(CString& rString)
{
	CString str = rString;
	if(str.GetLength()<1)
	return;
	if(str.GetLength()>1)
	if(str[1]==':')
	return;
	if(str[str.GetLength()-1]=='\\')
	str = str.Left(str.GetLength()-1);
	CString path = GetCommandLine();
	if(path[0]=='\"')
	{
		path = path.Right(path.GetLength()-1);
	}
	path = path.Left(path.ReverseFind('\\'));
	int n = 0;

	BOOL bOK = FALSE;
	while(!bOK)
	{
		if(str.Left(1)=="\\")
		{
			str = str.Right(str.GetLength()-1);
			continue;
		}
		if(str.Left(2)==".\\")
		{
			str = str.Right(str.GetLength()-2);
			continue;
		}
		if(str.Left(3)=="..\\")
		{
			str = str.Right(str.GetLength()-3);
			n++;
			continue;
		}
		if(str.Left(1)=="/")
		{
			str = str.Right(str.GetLength()-1);
			continue;
		}
		if(str.Left(2)=="./")
		{
			str = str.Right(str.GetLength()-2);
			continue;
		}
		if(str.Left(3)=="../")
		{
			str = str.Right(str.GetLength()-3);
			n++;
			continue;
		}
		bOK = TRUE;
	}
	int i;
	int pos;
	for(i=0;i<n;i++)
	{
		pos = path.ReverseFind('\\');
		if(pos>=0)
		path = path.Left(pos);
	}
	rString.Format("%s\\%s",path,str);
}
// 反之下面有获取相对路径
void GetRelativePath(CString& rString)
{
	CString str = rString;
	if(str.GetLength()<2)
	return;
	if(str[1]!=':')
	return;
	if(str[str.GetLength()-1]=='\\')
	str = str.Left(str.GetLength()-1);
	CString path = GetCommandLine();
	if(path[0]=='\"')
	{
		path = path.Right(path.GetLength()-1);
	}
	path = path.Left(path.ReverseFind('\\'));
	if(path[0]!=str[0])
	return;
	BOOL bOK = FALSE;
	CString s0 = "", s1="";
	int pos0=0,pos1=0,pos00=0,pos10=0;
	while(!bOK)
	{
		pos0 = path.Find('\\',pos0+1);
		pos1 = str.Find('\\',pos1+1);
		if((pos0>=0)&&(pos1>=0))
		{
			s0 = path.Left(pos0);
			s1 = str.Left(pos1);
			if(s0==s1)
			{
				pos00 = pos0;
				pos10 = pos1;
			}
			else
			{
				path = path.Right(path.GetLength()-pos00-1);
				str = str.Right(str.GetLength()-pos10-1);
				bOK = TRUE;
			}
		}
		else
		{
			path = path.Right(path.GetLength()-pos00-1);
			str = str.Right(str.GetLength()-pos10-1);
			bOK = TRUE;
		}
	}
	if(path.GetLength()==0)
	{
		rString = str;
	}
	else
	{
		pos0 = path.Find('\\');
		if(pos0>=0)
		{
			s0 = path.Left(pos0);
			if(s0.Compare(str)==0)
			{
				str = "";
				path = path.Right(path.GetLength()-pos0-1);
			}
		}
		s1 = "..";
		do
		{
			pos0 = path.ReverseFind('\\');
			if(pos0>=0)
			{
				path = path.Left(pos0);
				s1+="\\..";
			}
		}while(pos0>=0);
		rString.Format("%s\\%s",s1,str);
	}
}

BOOL IsRoot(LPCTSTR lpszPath)
{
	TCHAR szRoot[4];
	wsprintf(szRoot, "%c:\\", lpszPath[0]);
	return (lstrcmp(szRoot, lpszPath) == 0);
}
void FindInAll(::LPCTSTR lpszPath)
{
	TCHAR szFind[MAX_PATH];
	lstrcpy(szFind, lpszPath);
	if (!IsRoot(szFind)) 
		lstrcat(szFind, "\\");
	lstrcat(szFind, "*.*"); // 找所有文件
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(szFind, &wfd);
	if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败
		return;	
	do
	{
		if (wfd.cFileName[0] == '.')
			continue; // 过滤这两个目录
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	//为文件夹
		{
			TCHAR szFile[MAX_PATH];
			if (IsRoot(lpszPath))
				wsprintf(szFile, "%s%s", lpszPath, wfd.cFileName);
			else
				wsprintf(szFile, "%s\\%s", lpszPath, wfd.cFileName);
			CString strDelete(szFile);
			CString strFolder = strDelete.Right(strDelete.GetLength() - strDelete.ReverseFind('\\') - 1);
			if(!strFolder.CompareNoCase(TEXT(".svn")))
			{
				DeleteDirectory(strDelete);
				continue;
			}
			FindInAll(szFile); // 如果找到的是目录，则进入此目录进行递归
		}
// 		else
// 		{
// 			TCHAR szFile[MAX_PATH];
// 			if (IsRoot(lpszPath))
// 				wsprintf(szFile, "%s%s", lpszPath, wfd.cFileName);
// 			else
// 				wsprintf(szFile, "%s\\%s", lpszPath, wfd.cFileName);
// 			printf("%s\n",szFile);
// 			// 对文件进行操作
// 			CString strFilePath(szFile);
// 			CString sSuffix = strFilePath.Right(4);
// 			if( !sSuffix.CompareNoCase(".ncb") || !sSuffix.CompareNoCase(".opt"))
// 			{
// 				DeleteFile(strFilePath);
// 			}
// 		}
	} while (FindNextFile(hFind, &wfd));
	FindClose(hFind); // 关闭查找句柄	
}


void CDeleteFileDlg::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilePath;
	GetModuleFileName(NULL, strFilePath.GetBuffer(MAX_PATH), MAX_PATH);
	strFilePath.ReleaseBuffer();
	CString strFolder = strFilePath.Left(strFilePath.ReverseFind('\\'));
	FindInAll(strFolder);
	MessageBox("OK", NULL, MB_OK);
}
