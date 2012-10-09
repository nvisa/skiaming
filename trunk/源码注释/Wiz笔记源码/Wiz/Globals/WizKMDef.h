#pragma once

#ifndef __WIZKMDEF_H__
#define __WIZKMDEF_H__


const  UINT WIZKM_SYNC_BEGIN = ::RegisterWindowMessage(_T("WizKMSyncBegin"));
const  UINT WIZKM_SYNC_END = ::RegisterWindowMessage(_T("WizKMSyncEnd"));
const  UINT WIZKM_SYNC_PROGRESS = ::RegisterWindowMessage(_T("WizKMSyncProgress"));
const  UINT WIZKM_SYNC_STEP = ::RegisterWindowMessage(_T("WizKMSyncStep"));



#define WIZKM_REG_KEY_ROOT		WizGetRegKeyRoot()

#define FOLDER_MY_NOTES			_T("My Notes")
#define FOLDER_MY_JOURNALS		_T("My Journals")
#define FOLDER_MY_EVENTS		_T("My Events")
#define FOLDER_MY_CONTACTS		_T("My Contacts")
#define FOLDER_MY_PHOTOS		_T("My Photos")
#define FOLDER_MY_MOBILES		_T("My Mobiles")
#define FOLDER_MY_DRAFTS		_T("My Drafts")
#define FOLDER_DELETED_ITEMS	_T("Deleted Items")


const UINT WIZKM_FREE_USER_TRAFFIC_LIMIT		= 88 * 1024 * 1024;


#endif