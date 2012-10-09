// -*-C-*-
////////////////////////////////////////////////////////////////////////////////
//
//File:         twacker.h
//RCS:          $Header: $
//Description:  Exerciser application program for Twain
//Author:       TWAIN Working Group
//Created:      Jan 15,92
//Modified:     "
//Language:     C
//Package:      N/A
//Status:       Test tool
//
//(c) Copyright 1992, Hewlett-Packard Company, all rights reserved.
//
/*	Copyright © 1998 TWAIN Working Group: Adobe Systems Incorporated, 
*	Canon Information Systems, Eastman Kodak Company, 
*	Fujitsu Computer Products of America, Genoa Technology, 
*	Hewlett-Packard Company, Intel Corporation, Kofax Image Products, 
*	JFL Peripheral Solutions Inc., Ricoh Corporation, and Xerox Corporation.  
*	All rights reserved.
*/
//

#ifndef _inc_twacker_h
#define _inc_twacker_h

#ifdef _WIN32
#define HUGE
#else
#define HUGE huge
#endif //_WIN32

//
//--------------------------------------------------------------------
//					V a r i a b l e s
//--------------------------------------------------------------------

extern BOOL g_bSpecialMenu;

//
//--------------------------------------------------------------------
//					F u n c t i o n s
//--------------------------------------------------------------------
//

TW_INT16 InitTwainCombo(HWND hDlg, TW_INT16 Id, 
												pTABLEENTRY pTable, int nSizeTable);
	
void CheckSpecialMenu
	(HWND hWndofApp, TW_INT16 CkMenu);
void CheckIfAcquire(char attribute[]);
void OnScrollBar(HWND, int, UINT, int, SCROLLINFO*);
void OnKeyDown(HWND, UINT);
BOOL CloseApplication(HWND hWnd);
void DrawScrollBar(HWND, SCROLLINFO*, int, BITMAP);
void SaveBitmap(HWND, HGLOBAL _hDIB);

#endif //_inc_twacker_h

