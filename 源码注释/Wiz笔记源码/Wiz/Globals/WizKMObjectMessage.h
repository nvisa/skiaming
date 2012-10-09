#pragma once

#include "../../WizGlobals/WizWindowMessage.h"

#define WIZKM_OBJECT_MESSAGE_WM_COPYDATA_DATA		1000


enum WizKMObjectType
{
	objecttypeTag,
	objecttypeStyle,
	objecttypeDocument,
	objecttypeAttachment,
	objecttypeFolder
};

enum WizKMObjectMessageType
{
	messagetypeNew,
	messagetypeModify,
	messagetypeDelete
};

class CWizKMObjectMessage : public CWizWindowMessage
{
public:
	CWizKMObjectMessage(LPCTSTR lpszMessageName)
		: CWizWindowMessage(lpszMessageName, WM_COPYDATA)
	{
	}
public:
	virtual BOOL Send(WizKMObjectType objectType, WizKMObjectMessageType messageType, LPCTSTR lpszGUID)
	{
		if (_tcslen(lpszGUID) > 40)
			return FALSE;
		//
		const UINT nGUIDSize = 40;
		WCHAR szGUID[nGUIDSize] = {0};
		wcscpy_s(szGUID, nGUIDSize, lpszGUID);
		//
		COPYDATASTRUCT data;
		data.dwData = MAKELONG(WIZKM_OBJECT_MESSAGE_WM_COPYDATA_DATA, MAKEWORD(objectType, messageType));
		data.cbData = nGUIDSize * sizeof(WCHAR);
		data.lpData = szGUID;
		//
		return CWizWindowMessage::Send(NULL, (LPARAM)&data);
	}
	//
	virtual BOOL SendFolderCreateDelete(WizKMObjectMessageType messageType, LPCTSTR lpszNewLocation)
	{
		ATLASSERT(messagetypeNew == messageType || messagetypeDelete == messageType);
		//
		const UINT nBufferSize = MAX_PATH;
		WCHAR szLocation[nBufferSize] = {0};
		wcscpy_s(szLocation, nBufferSize, lpszNewLocation);
		//
		COPYDATASTRUCT data;
		data.dwData = MAKELONG(WIZKM_OBJECT_MESSAGE_WM_COPYDATA_DATA, MAKEWORD(objecttypeFolder, messageType));
		data.cbData = nBufferSize * sizeof(WCHAR);
		data.lpData = szLocation;
		//
		return CWizWindowMessage::Send(NULL, (LPARAM)&data);
	}
	virtual BOOL SendFolderRename(LPCTSTR lpszOldLocation, LPCTSTR lpszNewLocation)
	{
		const UINT nBufferSize = MAX_PATH * 2;
		WCHAR szLocation[nBufferSize] = {0};
		wcscpy_s(szLocation, nBufferSize, lpszOldLocation);
		wcscat_s(szLocation, nBufferSize, _T("\\"));
		wcscat_s(szLocation, nBufferSize, lpszNewLocation);
		//
		COPYDATASTRUCT data;
		data.dwData = MAKELONG(WIZKM_OBJECT_MESSAGE_WM_COPYDATA_DATA, MAKEWORD(objecttypeFolder, messagetypeModify));
		data.cbData = nBufferSize * sizeof(WCHAR);
		data.lpData = szLocation;
		//
		return CWizWindowMessage::Send(NULL, (LPARAM)&data);
	}
public:
	static LPCTSTR GetObjectMessageName(WizKMObjectType objectType)
	{
		static const LPCTSTR lpszMessageNameTag = _T("WizKMObjectMessage_Tag");
		static const LPCTSTR lpszMessageNameStyle = _T("WizKMObjectMessage_Style");
		static const LPCTSTR lpszMessageNameDocument = _T("WizKMObjectMessage_Document");
		static const LPCTSTR lpszMessageNameAttachment = _T("WizKMObjectMessage_Attachment");
		static const LPCTSTR lpszMessageNameFolder = _T("WizKMObjectMessage_Folder");
		//
		switch (objectType)
		{
		case objecttypeTag:
			{
				return lpszMessageNameTag;
			}
		case objecttypeStyle:
			{
				return lpszMessageNameStyle;
			}
		case objecttypeDocument:
			{
				return lpszMessageNameDocument;
			}
		case objecttypeAttachment:
			{
				return lpszMessageNameAttachment;
			}
		case objecttypeFolder:
			{
				return lpszMessageNameFolder;
			}
		}
		//
		ATLASSERT(FALSE);
		static const LPCTSTR lpszMessageNameUnknown = _T("WizKMObjectMessage_Unknown");
		return lpszMessageNameUnknown;
	}
};

inline BOOL WizKMObjectSendMessage(WizKMObjectType objectType, WizKMObjectMessageType messageType, LPCTSTR lpszGUID)
{
	CWizKMObjectMessage msg(CWizKMObjectMessage::GetObjectMessageName(objectType));
	//
	return msg.Send(objectType, messageType, lpszGUID);
}

inline BOOL WizKMObjectSendMessage_New(WizKMObjectType objectType, LPCTSTR lpszGUID)
{
	return WizKMObjectSendMessage(objectType, messagetypeNew, lpszGUID);
}
inline BOOL WizKMObjectSendMessage_Modify(WizKMObjectType objectType, LPCTSTR lpszGUID)
{
	return WizKMObjectSendMessage(objectType, messagetypeModify, lpszGUID);
}
inline BOOL WizKMObjectSendMessage_Delete(WizKMObjectType objectType, LPCTSTR lpszGUID)
{
	return WizKMObjectSendMessage(objectType, messagetypeDelete, lpszGUID);
}


inline BOOL WizKMFolderSendMessage_New(LPCTSTR lpszLocation)
{
	CWizKMObjectMessage msg(CWizKMObjectMessage::GetObjectMessageName(objecttypeFolder));
	return msg.SendFolderCreateDelete(messagetypeNew, lpszLocation);
}
inline BOOL WizKMFolderSendMessage_Modify(WizKMObjectType objectType, LPCTSTR lpszOldLocation, LPCTSTR lpszNewLocation)
{
	CWizKMObjectMessage msg(CWizKMObjectMessage::GetObjectMessageName(objecttypeFolder));
	return msg.SendFolderRename(lpszOldLocation, lpszNewLocation);
}
inline BOOL WizKMFolderSendMessage_Delete(LPCTSTR lpszLocation)
{
	CWizKMObjectMessage msg(CWizKMObjectMessage::GetObjectMessageName(objecttypeFolder));
	return msg.SendFolderCreateDelete(messagetypeDelete, lpszLocation);
}



inline BOOL WizKMObjectMessageRegisterReceiver(WizKMObjectType objectType, HWND hWnd)
{
	CWizKMObjectMessage msg(CWizKMObjectMessage::GetObjectMessageName(objectType));
	return msg.RegisterReceiver(hWnd);
}
inline BOOL WizKMObjectMessageUnregisterReceiver(WizKMObjectType objectType, HWND hWnd)
{
	CWizKMObjectMessage msg(CWizKMObjectMessage::GetObjectMessageName(objectType));
	return msg.UnregisterReceiver(hWnd);
}



template <class T>
class CWizKMObjectMessageHandler
{
public:
	BEGIN_MSG_MAP(CWizKMObjectMessageHandler< T >)
		MESSAGE_HANDLER(WM_COPYDATA, OnCopyData)
	END_MSG_MAP()
public:
	LRESULT OnCopyData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//
		bHandled = FALSE;
		//
		COPYDATASTRUCT* pData = (COPYDATASTRUCT *)lParam;
		if (!pData)
			return TRUE;
		//
		WORD nMessage = LOWORD(pData->dwData);
		if (WIZKM_OBJECT_MESSAGE_WM_COPYDATA_DATA != nMessage)
			return TRUE;
		//
		WORD nObject = HIWORD(pData->dwData);
		//
		BYTE nObjectType = LOBYTE(nObject);
		BYTE nMessageType = HIBYTE(nObject);
		//
		if (nObjectType < objecttypeTag
			|| nObjectType > objecttypeFolder)
			return TRUE;
		//
		if (nMessageType < messagetypeNew
			|| nMessageType > messagetypeDelete)
			return TRUE;
		//
		WizKMObjectType objectType = (WizKMObjectType)nObjectType;
		WizKMObjectMessageType messageType = (WizKMObjectMessageType)nMessageType;
		LPCWSTR lpszData = (LPCWSTR)(pData->lpData);
		//
		bHandled = TRUE;
		//
		switch (objectType)
		{
		case objecttypeTag:
			{
				switch (nMessageType)
				{
				case messagetypeNew:
					return pT->OnNewTag(lpszData);
				case messagetypeModify:
					return pT->OnModifyTag(lpszData);
				case messagetypeDelete:
					return pT->OnDeleteTag(lpszData);
				}
			}
			break;
		case objecttypeStyle:
			{
				switch (nMessageType)
				{
				case messagetypeNew:
					return pT->OnNewStyle(lpszData);
				case messagetypeModify:
					return pT->OnModifyStyle(lpszData);
				case messagetypeDelete:
					return pT->OnDeleteStyle(lpszData);
				}
			}
			break;
		case objecttypeDocument:
			{
				switch (nMessageType)
				{
				case messagetypeNew:
					return pT->OnNewDocument(lpszData);
				case messagetypeModify:
					return pT->OnModifyDocument(lpszData);
				case messagetypeDelete:
					return pT->OnDeleteDocument(lpszData);
				}
			}
			break;
		case objecttypeAttachment:
			{
				switch (nMessageType)
				{
				case messagetypeNew:
					return pT->OnNewAttachment(lpszData);
				case messagetypeModify:
					return pT->OnModifyAttachment(lpszData);
				case messagetypeDelete:
					return pT->OnDeleteAttachment(lpszData);
				}
			}
			break;
		case objecttypeFolder:
			{
				switch (nMessageType)
				{
				case messagetypeNew:
					return pT->OnNewFolder(lpszData);
				case messagetypeModify:
					{
						CWizStdStringArray arrayLocation;
						WizSplitTextToArray(lpszData, '\\', arrayLocation);
						if (arrayLocation.size() == 2)
						{
							return pT->OnRenameFolder(arrayLocation[0], arrayLocation[1]);
						}
						else
						{
							ATLASSERT(FALSE);
							return TRUE;
						}
					}
				case messagetypeDelete:
					return pT->OnDeleteFolder(lpszData);
				}
			}
			break;
		}
		//
		ATLASSERT(FALSE);
		return (LRESULT)TRUE;
	}
	//
	BOOL OnNewTag(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnModifyTag(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnDeleteTag(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnNewStyle(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnModifyStyle(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnDeleteStyle(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnNewDocument(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnModifyDocument(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnDeleteDocument(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnNewAttachment(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnModifyAttachment(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnDeleteAttachment(LPCTSTR lpszGUID){ return TRUE; }
	BOOL OnNewFolder(LPCTSTR lpszLocation) { return TRUE; }
	BOOL OnDeleteFolder(LPCTSTR lpszLocation) { return TRUE; }
	BOOL OnRenameFolder(LPCTSTR lpszOldLocation, LPCTSTR lpszNewLocation) { return TRUE; }
};

