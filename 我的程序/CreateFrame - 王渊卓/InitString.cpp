#include "StdAfx.h"
#include "InitString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 	CString strClwDLL = "; CLW file contains information for the MFC ClassWizard\n\
\n\
[General Info]\n\
Version=1\n\
ClassCount=1\n\
Class1=CDocProcess_DLLApp\n\
LastClass=CDocProcess_DLLApp\n\
NewFileInclude2=#include \"DocProcess_DLL.h\"\n\
ResourceCount=0\n\
NewFileInclude1=#include \"stdafx.h\"\n\
\n\
[CLS:CDocProcess_DLLApp]\n\
Type=0\n\
HeaderFile=DocProcess_DLL.h\n\
ImplementationFile=DocProcess_DLL.cpp\n\
Filter=N\n\
";
	CString strDspDLL1 = "# Microsoft Developer Studio Project File - Name=\"DocProcess_DLL\" - Package Owner=<4>\n\
# Microsoft Developer Studio Generated Build File, Format Version 6.00\n\
# ** DO NOT EDIT ** \n\
\n\
# TARGTYPE \"Win32 (x86) Dynamic-Link Library\" 0x0102\n\
\n\
CFG=DocProcess_DLL - Win32 Debug DLL\
!MESSAGE This is not a valid makefile. To build this project using NMAKE,\n\
!MESSAGE use the Export Makefile command and run\n\
!MESSAGE \n\
!MESSAGE NMAKE /f \"DocProcess_DLL.mak\".\n\
!MESSAGE \n\
!MESSAGE You can specify a configuration when running NMAKE\n\
!MESSAGE by defining the macro CFG on the command line. For example:\n\
!MESSAGE \n\
!MESSAGE NMAKE /f \"DocProcess_DLL.mak\" CFG=\"DocProcess_DLL - Win32 Debug DLL\"\n\
!MESSAGE \n\
!MESSAGE Possible choices for configuration are:\n\
!MESSAGE \n\
!MESSAGE \"DocProcess_DLL - Win32 Debug DLL\" (based on \"Win32 (x86) Dynamic-Link Library\")\n\
!MESSAGE \"DocProcess_DLL - Win32 Release DLL\" (based on \"Win32 (x86) Dynamic-Link Library\")\n\
!MESSAGE \n\
\n\
# Begin Project\n\
# PROP AllowPerConfigDependencies 0\n\
# PROP Scc_ProjName \"\"\n\
# PROP Scc_LocalPath \"\"\n\
CPP=cl.exe\n\
MTL=midl.exe\n\
RSC=rc.exe\n\
\n\
!IF  \"$(CFG)\" == \"DocProcess_DLL - Win32 Debug DLL\"\n\
\n\
# PROP BASE Use_MFC 6\n\
# PROP BASE Use_Debug_Libraries 1\n\
# PROP BASE Output_Dir \"Debug DLL\"\n\
# PROP BASE Intermediate_Dir \"Debug DLL\"\n\
# PROP BASE Target_Dir \"\"\n\
# PROP Use_MFC 6\n\
# PROP Use_Debug_Libraries 1\n\
# PROP Output_Dir \"..\\..\\TempFiles\\DocProcess\\Debug DLL\"\n\
# PROP Intermediate_Dir \"..\\..\\TempFiles\\DocProcess\\Debug DLL\"\n\
# PROP Ignore_Export_Lib 0\n\
# PROP Target_Dir \"\"\n\
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /Yu\"stdafx.h\" /FD /GZ    /c\n\
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /FD /GZ    /c\n\
# SUBTRACT CPP /YX /Yc /Yu\n\
# ADD BASE MTL /nologo /D \"_DEBUG\" /mktyplib203 /win32\n\
# ADD MTL /nologo /D \"_DEBUG\" /mktyplib203 /win32\n\
# ADD BASE RSC /l 0x804 /d \"_DEBUG\" /d \"_AFXDLL\"\n\
";
	CString strDspDLL2 ="# ADD RSC /l 0x804 /d \"_DEBUG\" /d \"_AFXDLL\"\n\
BSC32=bscmake.exe\n\
# ADD BASE BSC32 /nologo\n\
# ADD BSC32 /nologo\n\
LINK32=link.exe\n\
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept\n\
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:\"../../LIB/DocProcess_DLL.dll\" /implib:\"..\\..\\LIB\\DocProcess_DLL.lib\" /pdbtype:sept\n\
# SUBTRACT LINK32 /pdb:none\n\
\n\
!ELSEIF  \"$(CFG)\" == \"DocProcess_DLL - Win32 Release DLL\"\n\
\n\
# PROP BASE Use_MFC 6\n\
# PROP BASE Use_Debug_Libraries 0\n\
# PROP BASE Output_Dir \"Release DLL\"\n\
# PROP BASE Intermediate_Dir \"Release DLL\"\n\
# PROP BASE Target_Dir \"\"\n\
# PROP Use_MFC 5\n\
# PROP Use_Debug_Libraries 0\n\
# PROP Output_Dir \"..\\..\\TempFiles\\DocProcess\\Release DLL\"\n\
# PROP Intermediate_Dir \"..\\..\\TempFiles\\DocProcess\\Release DLL\"\n\
# PROP Ignore_Export_Lib 0\n\
# PROP Target_Dir \"\"\n\
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_WINDLL\" /D \"_AFXDLL\" /D \"_MBCS\" /D \"_USRDLL\" /Yu\"stdafx.h\" /FD /c\n\
# ADD CPP /nologo /MT /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_USRDLL\" /D \"FX_READER_DLL\" /D \"UNICODE\" /D \"_UNICODE\" /D \"_WINDLL\" /FD /c\n\
# SUBTRACT CPP /YX /Yc /Yu\n\
# ADD BASE MTL /nologo /D \"NDEBUG\" /mktyplib203 /win32\n\
# ADD MTL /nologo /D \"NDEBUG\" /mktyplib203 /win32\n\
# ADD BASE RSC /l 0x804 /d \"NDEBUG\" /d \"_AFXDLL\"\n\
# ADD RSC /l 0x804 /d \"NDEBUG\"\n\
BSC32=bscmake.exe\n\
# ADD BASE BSC32 /nologo\n\
# ADD BSC32 /nologo\n\
LINK32=link.exe\n\
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386\n\
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:\"../../librel/DocProcess_DLL.dll\" /implib:\"../../librel/DocProcess_DLL.lib\"\n\
# SUBTRACT LINK32 /pdb:none\n\
\n\
!ENDIF\n\
\n\
# Begin Target\n\
\n\
# Name \"DocProcess_DLL - Win32 Debug DLL\"\n\
# Name \"DocProcess_DLL - Win32 Release DLL\"\n\
# Begin Group \"Source Files\"\n\
\n\
# PROP Default_Filter \"cpp;c;cxx;rc;def;r;odl;idl;hpj;bat\"\n\
# Begin Source File\n\
\n\
SOURCE=.\\DocProcess_DLL.cpp\n\
# End Source File\n\
# Begin Source File\n\
\n\
";
	CString strDspDLL3 = "SOURCE=.\\DocProcess_DLL.def\n\
# End Source File\n\
# Begin Source File\n\
\n\
SOURCE=..\\res\\DocProcess_DLL.rc\n\
# End Source File\n\
# Begin Source File\n\
\n\
SOURCE=.\\StdAfx.cpp\n\
# ADD BASE CPP /Yc\"stdafx.h\"\n\
# ADD CPP /Yc\"stdafx.h\"\n\
# End Source File\n\
# End Group\n\
# Begin Group \"Header Files\"\n\
\n\
# PROP Default_Filter \"h;hpp;hxx;hm;inl\"\n\
# Begin Source File\n\
\n\
SOURCE=.\\DocProcess_DLL.h\n\
# End Source File\n\
# Begin Source File\n\
\n\
SOURCE=..\\res\\Resource.h\n\
# End Source File\n\
# Begin Source File\n\
\n\
SOURCE=.\\StdAfx.h\n\
# End Source File\n\
# End Group\n\
# Begin Group \"Resource Files\"\n\
\n\
# PROP Default_Filter \"ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\"\n\
# Begin Source File\n\
\n\
SOURCE=..\\res\\res\\DocProcess_DLL.rc2\n\
# End Source File\n\
# End Group\n\
# Begin Source File\n\
\n\
SOURCE=.\\ReadMe.txt\n\
# End Source File\n\
# End Target\n\
# End Project\n\
";

//DLL.def  存入变量
	CString strDefDLL = "; DocProcess_DLL.def : Declares the module parameters for the DLL.\n\
\n\
LIBRARY      \"DocProcess_DLL\"\n\
DESCRIPTION  'DocProcess_DLL Windows Dynamic Link Library'\n\
\n\
EXPORTS\n\
    ; Explicit exports can go here\n\
";
//DLL.h 存入变量
	CString strHDLL = "// DocProcess_DLL.h : main header file for the DOCPROCESS_DLL DLL\n\
//\n\
\n\
#if !defined(AFX_DOCPROCESS_DLL_H__B8247360_599B_475F_87B2_E0471CA788F8__INCLUDED_)\n\
#define AFX_DOCPROCESS_DLL_H__B8247360_599B_475F_87B2_E0471CA788F8__INCLUDED_\n\
\n\
#if _MSC_VER > 1000\n\
#pragma once\n\
#endif // _MSC_VER > 1000\n\
\n\
#ifndef __AFXWIN_H__\n\
	#error include \'stdafx.h\' before including this file for PCH\n\
#endif\n\
\n\
#include \"../res/resource.h\"		// main symbols\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
// CDocProcess_DLLApp\n\
// See DocProcess_DLL.cpp for the implementation of this class\n\
//\n\
\n\
class CDocProcess_DLLApp : public CWinApp\n\
{\n\
public:\n\
	CDocProcess_DLLApp();\n\
\n\
// Overrides\n\
	// ClassWizard generated virtual function overrides\n\
	//{{AFX_VIRTUAL(CDocProcess_DLLApp)\n\
	//}}AFX_VIRTUAL\n\
\n\
	//{{AFX_MSG(CDocProcess_DLLApp)\n\
		// NOTE - the ClassWizard will add and remove member functions here.\n\
		//    DO NOT EDIT what you see in these blocks of generated code !\n\
	//}}AFX_MSG\n\
	DECLARE_MESSAGE_MAP()\n\
};\n\
\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
\n\
//{{AFX_INSERT_LOCATION}}\n\
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.\n\
\n\
#endif // !defined(AFX_DOCPROCESS_DLL_H__B8247360_599B_475F_87B2_E0471CA788F8__INCLUDED_)\n\
";
	//DLL.CPP 存入变量
	CString	strCppDLL = "// DocProcess_DLL.cpp : Defines the initialization routines for the DLL.\n\
//\n\
\n\
#include \"stdafx.h\"\n\
#include \"DocProcess_DLL.h\"\n\
\n\
#ifdef _DEBUG\n\
#define new DEBUG_NEW\n\
#undef THIS_FILE\n\
static char THIS_FILE[] = __FILE__;\n\
#endif\n\
\n\
//\n\
//	Note!\n\
//\n\
//		If this DLL is dynamically linked against the MFC\n\
//		DLLs, any functions exported from this DLL which\n\
//		call into MFC must have the AFX_MANAGE_STATE macro\n\
//		added at the very beginning of the function.\n\
//\n\
//		For example:\n\
//\n\
//		extern \"C\" BOOL PASCAL EXPORT ExportedFunction()\n\
//		{\n\
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());\n\
//			// normal function body here\n\
//		}\n\
//\n\
//		It is very important that this macro appear in each\n\
//		function, prior to any calls into MFC.  This means that\n\
//		it must appear as the first statement within the\n\
//		function, even before any object variable declarations\n\
//		as their constructors may generate calls into the MFC\n\
//		DLL.\n\
//\n\
//		Please see MFC Technical Notes 33 and 58 for additional\n\
//		details.\n\
//\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
// CDocProcess_DLLApp\n\
\n\
BEGIN_MESSAGE_MAP(CDocProcess_DLLApp, CWinApp)\n\
	//{{AFX_MSG_MAP(CDocProcess_DLLApp)\n\
		// NOTE - the ClassWizard will add and remove mapping macros here.\n\
		//    DO NOT EDIT what you see in these blocks of generated code!\n\
	//}}AFX_MSG_MAP\n\
END_MESSAGE_MAP()\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
// CDocProcess_DLLApp construction\n\
\n\
CDocProcess_DLLApp::CDocProcess_DLLApp()\n\
{\n\
	// TODO: add construction code here,\n\
	// Place all significant initialization in InitInstance\n\
}\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
// The one and only CDocProcess_DLLApp object\n\
\n\
CDocProcess_DLLApp theApp;\n\
";
	CString strStdHDLL = "// stdafx.h : include file for standard system include files,\n\
//  or project specific include files that are used frequently, but\n\
//      are changed infrequently\n\
//\n\
\n\
#if !defined(AFX_STDAFX_H__408DF6B1_DCE5_42C6_B3FB_FEA6A0C22F10__INCLUDED_)\n\
#define AFX_STDAFX_H__408DF6B1_DCE5_42C6_B3FB_FEA6A0C22F10__INCLUDED_\n\
\n\
#if _MSC_VER > 1000\n\
#pragma once\n\
#endif // _MSC_VER > 1000\n\
\n\
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers\n\
\n\
#include <afxwin.h>         // MFC core and standard components\n\
#include <afxext.h>         // MFC extensions\n\
\n\
#ifndef _AFX_NO_OLE_SUPPORT\n\
#include <afxole.h>         // MFC OLE classes\n\
#include <afxodlgs.h>       // MFC OLE dialog classes\n\
#include <afxdisp.h>        // MFC Automation classes\n\
#endif // _AFX_NO_OLE_SUPPORT\n\
\n\
\n\
#ifndef _AFX_NO_DB_SUPPORT\n\
#include <afxdb.h>			// MFC ODBC database classes\n\
#endif // _AFX_NO_DB_SUPPORT\n\
\n\
#ifndef _AFX_NO_DAO_SUPPORT\n\
#include <afxdao.h>			// MFC DAO database classes\n\
#endif // _AFX_NO_DAO_SUPPORT\n\
\n\
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls\n\
#ifndef _AFX_NO_AFXCMN_SUPPORT\n\
#include <afxcmn.h>			// MFC support for Windows Common Controls\n\
#endif // _AFX_NO_AFXCMN_SUPPORT\n\
\n\
\n\
//{{AFX_INSERT_LOCATION}}\n\
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.\n\
\n\
#endif // !defined(AFX_STDAFX_H__408DF6B1_DCE5_42C6_B3FB_FEA6A0C22F10__INCLUDED_)\n\
";
	CString strStdCppDLL = "// stdafx.cpp : source file that includes just the standard includes\n\
//	DocProcess_DLL.pch will be the pre-compiled header\n\
//	stdafx.obj will contain the pre-compiled type information\n\
\n\
#include \"stdafx.h\"\n\
\n\
\n\
\n\
";
// resource.h 存入变量
	CString strRHDLL = "//{{NO_DEPENDENCIES}}\n\
// Microsoft Visual C++ generated include file.\n\
// Used by DOCPROCESS_DLL.RC\n\
//\n\
\n\
// Next default values for new objects\n\
// \n\
#ifdef APSTUDIO_INVOKED\n\
#ifndef APSTUDIO_READONLY_SYMBOLS\n\
\n\
#define _APS_NEXT_RESOURCE_VALUE	3000\n\
#define _APS_NEXT_CONTROL_VALUE		3000\n\
#define _APS_NEXT_SYMED_VALUE		3000\n\
#define _APS_NEXT_COMMAND_VALUE		32771\n\
#endif\n\
#endif\n\
";
// DLL.rc 存入变量
	CString strRCDLL1 = "// Microsoft Visual C++ generated resource script.\n\
//\n\
#include \"resource.h\"\n\
\n\
#define APSTUDIO_READONLY_SYMBOLS\n\
/////////////////////////////////////////////////////////////////////////////\n\
//\n\
// Generated from the TEXTINCLUDE 2 resource.\n\
//\n\
#include \"afxres.h\"\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
#undef APSTUDIO_READONLY_SYMBOLS\n\
\n\
#ifdef APSTUDIO_INVOKED\n\
/////////////////////////////////////////////////////////////////////////////\n\
//\n\
// TEXTINCLUDE\n\
//\n\
\n\
1 TEXTINCLUDE DISCARDABLE \n\
BEGIN\n\
    \"resource.h\\0\"\n\
END\n\
\n\
2 TEXTINCLUDE DISCARDABLE\n\
BEGIN\n\
    \"#include \"\"afxres.h\"\"\\r\\n\"\n\
    \"\\0\"\n\
END\n\
\n\
3 TEXTINCLUDE DISCARDABLE \n\
BEGIN\n\
    \"#define _AFX_NO_SPLITTER_RESOURCES\\r\\n\"\n\
    \"#define _AFX_NO_OLE_RESOURCES\\r\\n\"\n\
    \"#define _AFX_NO_TRACKER_RESOURCES\\r\\n\"\n\
    \"#define _AFX_NO_PROPERTY_RESOURCES\\r\\n\"\n\
	\"\\r\\n\"\n\
	\"#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_CHS)\\r\\n\"\n\
	\"#ifdef _WIN32\\r\\n\"\n\
	\"LANGUAGE 4, 2\\r\\n\"\n\
	\"#pragma code_page(936)\\r\\n\"\n\
	\"#endif //_WIN32\\r\\n\"\n\
	\"#include \"\"res\\\\DocProcess_DLL.rc2\"\"  // non-Microsoft Visual C++ edited resources\\r\\n\"\n\
	\"#include \"\"l.chs\\\\afxres.rc\"\"  	// Standard components\\r\\n\"\n\
	\"#endif\\r\\n\"\n\
    \"\\0\"\n\
END\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
#endif    // APSTUDIO_INVOKED\n\
\n\
\n\
\n\
\n\
#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_CHS)\n\
#ifdef _WIN32\n\
LANGUAGE 4, 2\n\
#pragma code_page(936)\n\
#endif //_WIN32\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
//\n\
// Version\n\
//\n\
\n\
";
	CString strRCDLL2 = "VS_VERSION_INFO     VERSIONINFO\n\
  FILEVERSION       1,0,0,1\n\
  PRODUCTVERSION    1,0,0,1\n\
 FILEFLAGSMASK 0x3fL\n\
#ifdef _DEBUG\n\
 FILEFLAGS 0x1L\n\
#else\n\
 FILEFLAGS 0x0L\n\
#endif\n\
 FILEOS 0x4L\n\
 FILETYPE 0x2L\n\
 FILESUBTYPE 0x0L\n\
BEGIN\n\
	BLOCK \"StringFileInfo\"\n\
	BEGIN\n\
        BLOCK \"080404B0\"\n\
		BEGIN\n\
			VALUE \"CompanyName\",     \"\\0\"\n\
			VALUE \"FileDescription\", \"DocProcess_DLL DLL\\0\"\n\
			VALUE \"FileVersion\",     \"1, 0, 0, 1\\0\"\n\
			VALUE \"InternalName\",    \"DocProcess_DLL\\0\"\n\
			VALUE \"LegalCopyright\",  \"版权所有 (C) 2012\\0\"\n\
			VALUE \"LegalTrademarks\", \"\\0\"\n\
			VALUE \"OriginalFilename\",\"DocProcess_DLL.DLL\\0\"\n\
			VALUE \"ProductName\",     \"DocProcess_DLL Dynamic Link Library\\0\"\n\
			VALUE \"ProductVersion\",  \"1, 0, 0, 1\\0\"\n\
		END\n\
	END\n\
	BLOCK \"VarFileInfo\"\n\
	BEGIN \n\
		VALUE \"Translation\", 0x0804, 1200\n\
    END\n\
END\n\
\n\
#endif\n\
\n\
#ifndef APSTUDIO_INVOKED\n\
/////////////////////////////////////////////////////////////////////////////\n\
//\n\
// Generated from the TEXTINCLUDE 3 resource.\n\
//\n\
#define _AFX_NO_SPLITTER_RESOURCES\n\
#define _AFX_NO_OLE_RESOURCES\n\
#define _AFX_NO_TRACKER_RESOURCES\n\
#define _AFX_NO_PROPERTY_RESOURCES\n\
\n\
#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_CHS)\n\
#ifdef _WIN32\n\
LANGUAGE 4, 2\n\
#pragma code_page(936)\n\
#endif //_WIN32\n\
#include \"res\\\\DocProcess_DLL.rc2\"  // non-Microsoft Visual C++ edited resources\n\
#include \"l.chs\\\\afxres.rc\"  	// Standard components\n\
#endif\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
#endif    // not APSTUDIO_INVOKED\n\
\n\
";

//DLL.rc2 存入变量
	CString strRC2DLL = "//\n\
// DOCPROCESS_DLL.RC2 - resources Microsoft Visual C++ does not edit directly\n\
//\n\
\n\
#ifdef APSTUDIO_INVOKED\n\
	#error this file is not editable by Microsoft Visual C++\n\
#endif //APSTUDIO_INVOKED\n\
\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
// Add manually edited resources here...\n\
\n\
/////////////////////////////////////////////////////////////////////////////\n\
"; 
//LIB.dsp 存入变量
	CString strDspLIB1 = "# Microsoft Developer Studio Project File - Name=\"DocProcess_LIB\" - Package Owner=<4>\n\
# Microsoft Developer Studio Generated Build File, Format Version 6.00\n\
# ** DO NOT EDIT **\n\
\n\
# TARGTYPE \"Win32 (x86) Static Library\" 0x0104\n\
\n\
CFG=DocProcess_LIB - Win32 Debug LIB\n\
!MESSAGE This is not a valid makefile. To build this project using NMAKE,\n\
!MESSAGE use the Export Makefile command and run\n\
!MESSAGE \n\
!MESSAGE NMAKE /f \"DocProcess_LIB.mak\".\n\
!MESSAGE \n\
!MESSAGE You can specify a configuration when running NMAKE\n\
!MESSAGE by defining the macro CFG on the command line. For example:\n\
!MESSAGE \n\
!MESSAGE NMAKE /f \"DocProcess_LIB.mak\" CFG=\"DocProcess_LIB - Win32 Debug LIB\"\n\
!MESSAGE \n\
!MESSAGE Possible choices for configuration are:\n\
!MESSAGE \n\
!MESSAGE \"DocProcess_LIB - Win32 Debug LIB\" (based on \"Win32 (x86) Static Library\")\n\
!MESSAGE \"DocProcess_LIB - Win32 Release LIB\" (based on \"Win32 (x86) Static Library\")\n\
!MESSAGE \n\
\n\
# Begin Project\n\
# PROP AllowPerConfigDependencies 0\n\
# PROP Scc_ProjName \"\"\n\
# PROP Scc_LocalPath \"\"\n\
CPP=cl.exe\n\
RSC=rc.exe\n\
\n\
!IF  \"$(CFG)\" == \"DocProcess_LIB - Win32 Debug LIB\"\n\
\n\
# PROP BASE Use_MFC 2\n\
# PROP BASE Use_Debug_Libraries 1\n\
# PROP BASE Output_Dir \"Debug LIB\"\n\
# PROP BASE Intermediate_Dir \"Debug LIB\"\n\
# PROP BASE Target_Dir \"\"\n\
# PROP Use_MFC 2\n\
# PROP Use_Debug_Libraries 1\n\
# PROP Output_Dir \"..\\..\\TempFiles\\DocProcess\\Debug LIB\"\n\
# PROP Intermediate_Dir \"..\\..\\TempFiles\\DocProcess\\Debug LIB\"\n\
# PROP Target_Dir \"\"\n\
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"_AFXDLL\" /D \"_MBCS\" /YX /FD /GZ  /c\n\
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D \"WIN32\" /D \"_DEBUG\" /D \"_WINDOWS\" /D \"_AFXDLL\" /D \"UNICODE\" /D \"_UNICODE\" /FD /GZ  /c\n\
# SUBTRACT CPP /YX\n\
# ADD BASE RSC /l 0x804 /d \"_DEBUG\" /d \"_AFXDLL\"\n\
# ADD RSC /l 0x804 /d \"_DEBUG\" /d \"_AFXDLL\"\n\
BSC32=bscmake.exe\n\
# ADD BASE BSC32 /nologo\n\
# ADD BSC32 /nologo\n\
LIB32=link.exe -lib\n\
# ADD BASE LIB32 /nologo\n\
# ADD LIB32 /nologo /out:\"../../lib/DocProcess_Lib.lib\"\n\
";
	CString strDspLIB2 = "\n\
!ELSEIF  \"$(CFG)\" == \"DocProcess_LIB - Win32 Release LIB\"\n\
\n\
# PROP BASE Use_MFC 2\n\
# PROP BASE Use_Debug_Libraries 0\n\
# PROP BASE Output_Dir \"Release LIB\"\n\
# PROP BASE Intermediate_Dir \"Release LIB\"\n\
# PROP BASE Target_Dir \"\"\n\
# PROP Use_MFC 1\n\
# PROP Use_Debug_Libraries 0\n\
# PROP Output_Dir \"..\\..\\TempFiles\\DocProcess\\Release LIB\"\n\
# PROP Intermediate_Dir \"..\\..\\TempFiles\\DocProcess\\Release LIB\"\n\
# PROP Target_Dir \"\"\n\
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_AFXDLL\" /D \"_MBCS\" /YX /FD /c\n\
# ADD CPP /nologo /MT /W3 /GX /O2 /D \"WIN32\" /D \"NDEBUG\" /D \"_WINDOWS\" /D \"_MBCS\" /YX /FD /c\n\
# ADD BASE RSC /l 0x804 /d \"NDEBUG\" /d \"_AFXDLL\"\n\
# ADD RSC /l 0x804 /d \"NDEBUG\"\n\
BSC32=bscmake.exe\n\
# ADD BASE BSC32 /nologo\n\
# ADD BSC32 /nologo\n\
LIB32=link.exe -lib\n\
# ADD BASE LIB32 /nologo\n\
# ADD LIB32 /nologo /out:\"../../librel/DocProcess_Librel.lib\"\n\
\n\
!ENDIF \n\
\n\
# Begin Target\n\
\n\
# Name \"DocProcess_LIB - Win32 Debug LIB\"\n\
# Name \"DocProcess_LIB - Win32 Release LIB\"\n\
# Begin Group \"Source Files\"\n\
\n\
# PROP Default_Filter \"cpp;c;cxx;rc;def;r;odl;idl;hpj;bat\"\n\
# Begin Source File\n\
\n\
SOURCE=..\\src\\DocProcess.cpp\n\
# End Source File\n\
# End Group\n\
# Begin Group \"Header Files\"\n\
\n\
# PROP Default_Filter \"h;hpp;hxx;hm;inl\"\n\
# Begin Source File\n\
\n\
SOURCE=..\\include\\DocProcess.h\n\
# End Source File\n\
# End Group\n\
# End Target\n\
# End Project\n\
";

//.h文件存入变量
	CString strH = "#ifndef _DocProcess_H_\n\
#define _DocProcess_H_\n\
\n\
#define VC_EXTRALEAN\n\
#include <afx.h>\n\
#include <afxwin.h>\n\
#include <afxext.h>\n\
#include <afxcmn.h>\n\
#ifndef _INC_PDFAPI\n\
	#define _INC_PDFAPI\n\
\n\
	#include \"../../ExternalModule/fxcore/include/FPDFAPI/fpdf_module.h\"\n\
	#include \"../../ExternalModule/fxcore/include/FPDFDOC/fpdf_doc.h\"\n\
	#include \"../../ExternalModule/fxcore/include/FPDFDOC/fpdf_vt.h\"\n\
	#include \"../../ExternalModule/fxcore/include/FXCRT/fx_xml.h\"\n\
\n\
	#include \"../../InternalSDK/include/fr_sdk.h\"\n\
	#include \"../../InternalSDK/include/fr_resource.h\"\n\
	#include \"../../InternalSDK/include/FX_SystemHandler.h\"\n\
\n\
#endif\n\
\n\
#endif //_DocProcess_H_\n\
 ";
	//.cpp文件存入变量
	CString strCpp = "#include \"../include/DocProcess.h\"\n\
\n\
#ifdef FX_READER_DLL\n\
	#ifdef _DEBUG\n\
		#pragma comment(lib,\"X:/pdf/fxcore/Lib/dbg_w32_vc6/fxcoredll[dbg,w32,vc6].lib\")\n\
		#pragma comment(lib,\"X:/pdf/fxcore/Lib/dbg_w32_vc6/fpdfdocdll[dbg,w32,vc6].lib\")\n\
		#pragma comment(lib,\"X:/pdf/lib/fxreslib.lib\")\n\
\n\
	#endif\n\
\n\
#endif\n\
";