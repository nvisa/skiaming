// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200


#ifndef _SECURE_ATL
#define _SECURE_ATL	1
#endif

#define _WTL_NO_CSTRING

#include <atlbase.h>

#include <atlwin.h>

#include <atlstr.h>
using namespace ATL;

#include "../../WizGlobals/WTL/atlapp.h"

extern CAppModule _Module;


#include "../../WizGlobals/WTL/atlframe.h"
#include "../../WizGlobals/WTL/atlctrls.h"
#include "../../WizGlobals/WTL/atldlgs.h"
#include "../../WizGlobals/WTL/atlscrl.h"
#include "../../WizGlobals/WTL/atlmisc.h"
#include "../../WizGlobals/WTL/atlsplit.h"
#include "../../WizGlobals/WTL/atlscrl.h"

#include "../WizKMCore/WizKMCore_i.h"
#include "../WizKMControls/WizKMControls_i.h"

#define _WIZCOMHELPER

#include "../../WizGlobals/WizMisc.h"
#include "../../WizGlobals/WizUIBase.h"

#include "../../WizGlobals/WizAtlBrowser.h"

#include "../Globals/WizKMGlobal.h"
#include "../Globals/WizKMDatabaseEx.h"
#include "../Globals/WizKMSettings.h"
#include "../Globals/WizKMUI.h"

#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


class CMainFrame;

CMainFrame* WizGetMainFrame();
CWizKMDatabase* WizGetDatabase();

