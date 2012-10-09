

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Jun 08 14:13:24 2011
 */
/* Compiler settings for .\WizKMCore.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WizKMCore_i_h__
#define __WizKMCore_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWizDatabase_FWD_DEFINED__
#define __IWizDatabase_FWD_DEFINED__
typedef interface IWizDatabase IWizDatabase;
#endif 	/* __IWizDatabase_FWD_DEFINED__ */


#ifndef __IWizTagCollection_FWD_DEFINED__
#define __IWizTagCollection_FWD_DEFINED__
typedef interface IWizTagCollection IWizTagCollection;
#endif 	/* __IWizTagCollection_FWD_DEFINED__ */


#ifndef __IWizTag_FWD_DEFINED__
#define __IWizTag_FWD_DEFINED__
typedef interface IWizTag IWizTag;
#endif 	/* __IWizTag_FWD_DEFINED__ */


#ifndef __IWizDocumentCollection_FWD_DEFINED__
#define __IWizDocumentCollection_FWD_DEFINED__
typedef interface IWizDocumentCollection IWizDocumentCollection;
#endif 	/* __IWizDocumentCollection_FWD_DEFINED__ */


#ifndef __IWizDocument_FWD_DEFINED__
#define __IWizDocument_FWD_DEFINED__
typedef interface IWizDocument IWizDocument;
#endif 	/* __IWizDocument_FWD_DEFINED__ */


#ifndef __IWizDocumentAttachmentCollection_FWD_DEFINED__
#define __IWizDocumentAttachmentCollection_FWD_DEFINED__
typedef interface IWizDocumentAttachmentCollection IWizDocumentAttachmentCollection;
#endif 	/* __IWizDocumentAttachmentCollection_FWD_DEFINED__ */


#ifndef __IWizDocumentAttachment_FWD_DEFINED__
#define __IWizDocumentAttachment_FWD_DEFINED__
typedef interface IWizDocumentAttachment IWizDocumentAttachment;
#endif 	/* __IWizDocumentAttachment_FWD_DEFINED__ */


#ifndef __IWizFolderCollection_FWD_DEFINED__
#define __IWizFolderCollection_FWD_DEFINED__
typedef interface IWizFolderCollection IWizFolderCollection;
#endif 	/* __IWizFolderCollection_FWD_DEFINED__ */


#ifndef __IWizFolder_FWD_DEFINED__
#define __IWizFolder_FWD_DEFINED__
typedef interface IWizFolder IWizFolder;
#endif 	/* __IWizFolder_FWD_DEFINED__ */


#ifndef __IWizStyle_FWD_DEFINED__
#define __IWizStyle_FWD_DEFINED__
typedef interface IWizStyle IWizStyle;
#endif 	/* __IWizStyle_FWD_DEFINED__ */


#ifndef __IWizStyleCollection_FWD_DEFINED__
#define __IWizStyleCollection_FWD_DEFINED__
typedef interface IWizStyleCollection IWizStyleCollection;
#endif 	/* __IWizStyleCollection_FWD_DEFINED__ */


#ifndef __IWizKMProtocol_FWD_DEFINED__
#define __IWizKMProtocol_FWD_DEFINED__
typedef interface IWizKMProtocol IWizKMProtocol;
#endif 	/* __IWizKMProtocol_FWD_DEFINED__ */


#ifndef __IWizDocumentParam_FWD_DEFINED__
#define __IWizDocumentParam_FWD_DEFINED__
typedef interface IWizDocumentParam IWizDocumentParam;
#endif 	/* __IWizDocumentParam_FWD_DEFINED__ */


#ifndef __IWizDocumentParamCollection_FWD_DEFINED__
#define __IWizDocumentParamCollection_FWD_DEFINED__
typedef interface IWizDocumentParamCollection IWizDocumentParamCollection;
#endif 	/* __IWizDocumentParamCollection_FWD_DEFINED__ */


#ifndef __IWizMeta_FWD_DEFINED__
#define __IWizMeta_FWD_DEFINED__
typedef interface IWizMeta IWizMeta;
#endif 	/* __IWizMeta_FWD_DEFINED__ */


#ifndef __IWizMetaCollection_FWD_DEFINED__
#define __IWizMetaCollection_FWD_DEFINED__
typedef interface IWizMetaCollection IWizMetaCollection;
#endif 	/* __IWizMetaCollection_FWD_DEFINED__ */


#ifndef __IWizSettings_FWD_DEFINED__
#define __IWizSettings_FWD_DEFINED__
typedef interface IWizSettings IWizSettings;
#endif 	/* __IWizSettings_FWD_DEFINED__ */


#ifndef __IWizSettingsSection_FWD_DEFINED__
#define __IWizSettingsSection_FWD_DEFINED__
typedef interface IWizSettingsSection IWizSettingsSection;
#endif 	/* __IWizSettingsSection_FWD_DEFINED__ */


#ifndef __IWizDeletedGUID_FWD_DEFINED__
#define __IWizDeletedGUID_FWD_DEFINED__
typedef interface IWizDeletedGUID IWizDeletedGUID;
#endif 	/* __IWizDeletedGUID_FWD_DEFINED__ */


#ifndef __IWizDeletedGUIDCollection_FWD_DEFINED__
#define __IWizDeletedGUIDCollection_FWD_DEFINED__
typedef interface IWizDeletedGUIDCollection IWizDeletedGUIDCollection;
#endif 	/* __IWizDeletedGUIDCollection_FWD_DEFINED__ */


#ifndef __IWizKMTools_FWD_DEFINED__
#define __IWizKMTools_FWD_DEFINED__
typedef interface IWizKMTools IWizKMTools;
#endif 	/* __IWizKMTools_FWD_DEFINED__ */


#ifndef __IWizIndexZiwGDSPlugin_FWD_DEFINED__
#define __IWizIndexZiwGDSPlugin_FWD_DEFINED__
typedef interface IWizIndexZiwGDSPlugin IWizIndexZiwGDSPlugin;
#endif 	/* __IWizIndexZiwGDSPlugin_FWD_DEFINED__ */


#ifndef __IWizZiwIFilter_FWD_DEFINED__
#define __IWizZiwIFilter_FWD_DEFINED__
typedef interface IWizZiwIFilter IWizZiwIFilter;
#endif 	/* __IWizZiwIFilter_FWD_DEFINED__ */


#ifndef __IWizTodoItem_FWD_DEFINED__
#define __IWizTodoItem_FWD_DEFINED__
typedef interface IWizTodoItem IWizTodoItem;
#endif 	/* __IWizTodoItem_FWD_DEFINED__ */


#ifndef __IWizTodoItemCollection_FWD_DEFINED__
#define __IWizTodoItemCollection_FWD_DEFINED__
typedef interface IWizTodoItemCollection IWizTodoItemCollection;
#endif 	/* __IWizTodoItemCollection_FWD_DEFINED__ */


#ifndef __IWizEvent_FWD_DEFINED__
#define __IWizEvent_FWD_DEFINED__
typedef interface IWizEvent IWizEvent;
#endif 	/* __IWizEvent_FWD_DEFINED__ */


#ifndef __IWizEventCollection_FWD_DEFINED__
#define __IWizEventCollection_FWD_DEFINED__
typedef interface IWizEventCollection IWizEventCollection;
#endif 	/* __IWizEventCollection_FWD_DEFINED__ */


#ifndef __IWizRowset_FWD_DEFINED__
#define __IWizRowset_FWD_DEFINED__
typedef interface IWizRowset IWizRowset;
#endif 	/* __IWizRowset_FWD_DEFINED__ */


#ifndef __IWizSQLiteDatabase_FWD_DEFINED__
#define __IWizSQLiteDatabase_FWD_DEFINED__
typedef interface IWizSQLiteDatabase IWizSQLiteDatabase;
#endif 	/* __IWizSQLiteDatabase_FWD_DEFINED__ */


#ifndef __WizDatabase_FWD_DEFINED__
#define __WizDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDatabase WizDatabase;
#else
typedef struct WizDatabase WizDatabase;
#endif /* __cplusplus */

#endif 	/* __WizDatabase_FWD_DEFINED__ */


#ifndef __WizTagCollection_FWD_DEFINED__
#define __WizTagCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizTagCollection WizTagCollection;
#else
typedef struct WizTagCollection WizTagCollection;
#endif /* __cplusplus */

#endif 	/* __WizTagCollection_FWD_DEFINED__ */


#ifndef __WizTag_FWD_DEFINED__
#define __WizTag_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizTag WizTag;
#else
typedef struct WizTag WizTag;
#endif /* __cplusplus */

#endif 	/* __WizTag_FWD_DEFINED__ */


#ifndef __WizDocumentCollection_FWD_DEFINED__
#define __WizDocumentCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentCollection WizDocumentCollection;
#else
typedef struct WizDocumentCollection WizDocumentCollection;
#endif /* __cplusplus */

#endif 	/* __WizDocumentCollection_FWD_DEFINED__ */


#ifndef __WizDocument_FWD_DEFINED__
#define __WizDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocument WizDocument;
#else
typedef struct WizDocument WizDocument;
#endif /* __cplusplus */

#endif 	/* __WizDocument_FWD_DEFINED__ */


#ifndef __WizDocumentAttachmentCollection_FWD_DEFINED__
#define __WizDocumentAttachmentCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentAttachmentCollection WizDocumentAttachmentCollection;
#else
typedef struct WizDocumentAttachmentCollection WizDocumentAttachmentCollection;
#endif /* __cplusplus */

#endif 	/* __WizDocumentAttachmentCollection_FWD_DEFINED__ */


#ifndef __WizDocumentAttachment_FWD_DEFINED__
#define __WizDocumentAttachment_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentAttachment WizDocumentAttachment;
#else
typedef struct WizDocumentAttachment WizDocumentAttachment;
#endif /* __cplusplus */

#endif 	/* __WizDocumentAttachment_FWD_DEFINED__ */


#ifndef __WizFolderCollection_FWD_DEFINED__
#define __WizFolderCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizFolderCollection WizFolderCollection;
#else
typedef struct WizFolderCollection WizFolderCollection;
#endif /* __cplusplus */

#endif 	/* __WizFolderCollection_FWD_DEFINED__ */


#ifndef __WizFolder_FWD_DEFINED__
#define __WizFolder_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizFolder WizFolder;
#else
typedef struct WizFolder WizFolder;
#endif /* __cplusplus */

#endif 	/* __WizFolder_FWD_DEFINED__ */


#ifndef __WizStyle_FWD_DEFINED__
#define __WizStyle_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizStyle WizStyle;
#else
typedef struct WizStyle WizStyle;
#endif /* __cplusplus */

#endif 	/* __WizStyle_FWD_DEFINED__ */


#ifndef __WizStyleCollection_FWD_DEFINED__
#define __WizStyleCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizStyleCollection WizStyleCollection;
#else
typedef struct WizStyleCollection WizStyleCollection;
#endif /* __cplusplus */

#endif 	/* __WizStyleCollection_FWD_DEFINED__ */


#ifndef __WizKMProtocol_FWD_DEFINED__
#define __WizKMProtocol_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizKMProtocol WizKMProtocol;
#else
typedef struct WizKMProtocol WizKMProtocol;
#endif /* __cplusplus */

#endif 	/* __WizKMProtocol_FWD_DEFINED__ */


#ifndef __WizDocumentParam_FWD_DEFINED__
#define __WizDocumentParam_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentParam WizDocumentParam;
#else
typedef struct WizDocumentParam WizDocumentParam;
#endif /* __cplusplus */

#endif 	/* __WizDocumentParam_FWD_DEFINED__ */


#ifndef __WizDocumentParamCollection_FWD_DEFINED__
#define __WizDocumentParamCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentParamCollection WizDocumentParamCollection;
#else
typedef struct WizDocumentParamCollection WizDocumentParamCollection;
#endif /* __cplusplus */

#endif 	/* __WizDocumentParamCollection_FWD_DEFINED__ */


#ifndef __WizMeta_FWD_DEFINED__
#define __WizMeta_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizMeta WizMeta;
#else
typedef struct WizMeta WizMeta;
#endif /* __cplusplus */

#endif 	/* __WizMeta_FWD_DEFINED__ */


#ifndef __WizMetaCollection_FWD_DEFINED__
#define __WizMetaCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizMetaCollection WizMetaCollection;
#else
typedef struct WizMetaCollection WizMetaCollection;
#endif /* __cplusplus */

#endif 	/* __WizMetaCollection_FWD_DEFINED__ */


#ifndef __WizSettings_FWD_DEFINED__
#define __WizSettings_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizSettings WizSettings;
#else
typedef struct WizSettings WizSettings;
#endif /* __cplusplus */

#endif 	/* __WizSettings_FWD_DEFINED__ */


#ifndef __WizSettingsSection_FWD_DEFINED__
#define __WizSettingsSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizSettingsSection WizSettingsSection;
#else
typedef struct WizSettingsSection WizSettingsSection;
#endif /* __cplusplus */

#endif 	/* __WizSettingsSection_FWD_DEFINED__ */


#ifndef __WizDeletedGUID_FWD_DEFINED__
#define __WizDeletedGUID_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDeletedGUID WizDeletedGUID;
#else
typedef struct WizDeletedGUID WizDeletedGUID;
#endif /* __cplusplus */

#endif 	/* __WizDeletedGUID_FWD_DEFINED__ */


#ifndef __WizDeletedGUIDCollection_FWD_DEFINED__
#define __WizDeletedGUIDCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDeletedGUIDCollection WizDeletedGUIDCollection;
#else
typedef struct WizDeletedGUIDCollection WizDeletedGUIDCollection;
#endif /* __cplusplus */

#endif 	/* __WizDeletedGUIDCollection_FWD_DEFINED__ */


#ifndef __WizKMTools_FWD_DEFINED__
#define __WizKMTools_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizKMTools WizKMTools;
#else
typedef struct WizKMTools WizKMTools;
#endif /* __cplusplus */

#endif 	/* __WizKMTools_FWD_DEFINED__ */


#ifndef __WizIndexZiwGDSPlugin_FWD_DEFINED__
#define __WizIndexZiwGDSPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizIndexZiwGDSPlugin WizIndexZiwGDSPlugin;
#else
typedef struct WizIndexZiwGDSPlugin WizIndexZiwGDSPlugin;
#endif /* __cplusplus */

#endif 	/* __WizIndexZiwGDSPlugin_FWD_DEFINED__ */


#ifndef __WizZiwIFilter_FWD_DEFINED__
#define __WizZiwIFilter_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizZiwIFilter WizZiwIFilter;
#else
typedef struct WizZiwIFilter WizZiwIFilter;
#endif /* __cplusplus */

#endif 	/* __WizZiwIFilter_FWD_DEFINED__ */


#ifndef __WizTodoItem_FWD_DEFINED__
#define __WizTodoItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizTodoItem WizTodoItem;
#else
typedef struct WizTodoItem WizTodoItem;
#endif /* __cplusplus */

#endif 	/* __WizTodoItem_FWD_DEFINED__ */


#ifndef __WizTodoItemCollection_FWD_DEFINED__
#define __WizTodoItemCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizTodoItemCollection WizTodoItemCollection;
#else
typedef struct WizTodoItemCollection WizTodoItemCollection;
#endif /* __cplusplus */

#endif 	/* __WizTodoItemCollection_FWD_DEFINED__ */


#ifndef __WizEvent_FWD_DEFINED__
#define __WizEvent_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizEvent WizEvent;
#else
typedef struct WizEvent WizEvent;
#endif /* __cplusplus */

#endif 	/* __WizEvent_FWD_DEFINED__ */


#ifndef __WizEventCollection_FWD_DEFINED__
#define __WizEventCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizEventCollection WizEventCollection;
#else
typedef struct WizEventCollection WizEventCollection;
#endif /* __cplusplus */

#endif 	/* __WizEventCollection_FWD_DEFINED__ */


#ifndef __WizRowset_FWD_DEFINED__
#define __WizRowset_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizRowset WizRowset;
#else
typedef struct WizRowset WizRowset;
#endif /* __cplusplus */

#endif 	/* __WizRowset_FWD_DEFINED__ */


#ifndef __WizSQLiteDatabase_FWD_DEFINED__
#define __WizSQLiteDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizSQLiteDatabase WizSQLiteDatabase;
#else
typedef struct WizSQLiteDatabase WizSQLiteDatabase;
#endif /* __cplusplus */

#endif 	/* __WizSQLiteDatabase_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWizDatabase_INTERFACE_DEFINED__
#define __IWizDatabase_INTERFACE_DEFINED__

/* interface IWizDatabase */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66EDABF2-D4D0-4B63-BFFA-EB7C53A9372A")
    IWizDatabase : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR bstrDatabasePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DatabasePath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Folders( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RootTags( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tags( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Styles( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attachments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Metas( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MetasByName( 
            /* [in] */ BSTR bstrMetaName,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Meta( 
            /* [in] */ BSTR bstrMetaName,
            /* [in] */ BSTR bstrMetaKey,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Meta( 
            /* [in] */ BSTR bstrMetaName,
            /* [in] */ BSTR bstrMetaKey,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeletedItemsFolder( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateRootFolder( 
            /* [in] */ BSTR bstrFolderName,
            /* [in] */ VARIANT_BOOL vbSync,
            /* [retval][out] */ IDispatch **ppNewFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateRootFolder2( 
            /* [in] */ BSTR bstrFolderName,
            /* [in] */ VARIANT_BOOL vbSync,
            /* [in] */ BSTR bstrIconFileName,
            /* [retval][out] */ IDispatch **ppNewFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateRootTag( 
            /* [in] */ BSTR bstrRootTagName,
            /* [in] */ BSTR bstrTagDescription,
            /* [retval][out] */ IDispatch **ppNewTagDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateStyle( 
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nTextColor,
            /* [in] */ LONG nBackColor,
            /* [in] */ VARIANT_BOOL vbTextBold,
            /* [in] */ LONG nFlagIndex,
            /* [retval][out] */ IDispatch **ppNewStyleDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TagGroupFromGUID( 
            /* [in] */ BSTR bstrTagGroupGUID,
            /* [retval][out] */ IDispatch **ppTagGroupDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TagFromGUID( 
            /* [in] */ BSTR bstrTagGUID,
            /* [retval][out] */ IDispatch **ppTagDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StyleFromGUID( 
            /* [in] */ BSTR bstrStyleGUID,
            /* [retval][out] */ IDispatch **ppStyleDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentFromGUID( 
            /* [in] */ BSTR bstrDocumentGUID,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentsFromSQL( 
            /* [in] */ BSTR bstrSQLWhere,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentsFromTags( 
            /* [in] */ IDispatch *pTagCollectionDisp,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachmentFromGUID( 
            /* [in] */ BSTR bstrAttachmentGUID,
            /* [retval][out] */ IDispatch **ppAttachmentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObjectsByTime( 
            /* [in] */ DATE dtTime,
            /* [in] */ BSTR bstrObjectType,
            /* [retval][out] */ IDispatch **ppCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetModifiedObjects( 
            /* [in] */ BSTR bstrObjectType,
            /* [retval][out] */ IDispatch **ppCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTagGroupEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTagEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrParentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateStyleEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nTextColor,
            /* [in] */ LONG nBackColor,
            /* [in] */ VARIANT_BOOL vbTextBold,
            /* [in] */ LONG nFlagIndex,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDocumentEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrSEO,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrAuthor,
            /* [in] */ BSTR bstrKeywords,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrOwner,
            /* [in] */ BSTR bstrFileType,
            /* [in] */ BSTR bstrStyleGUID,
            /* [in] */ DATE dtCreated,
            /* [in] */ DATE dtModified,
            /* [in] */ DATE dtAccessed,
            /* [in] */ LONG nIconIndex,
            /* [in] */ LONG nSync,
            /* [in] */ LONG nProtected,
            /* [in] */ LONG nReadCount,
            /* [in] */ LONG nAttachmentCount,
            /* [in] */ LONG nIndexed,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ DATE dtParamModified,
            /* [in] */ BSTR bstrParamMD5,
            /* [in] */ VARIANT vTagGUIDs,
            /* [in] */ VARIANT vParams,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDocumentAttachmentEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrDocumentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateTagGroupEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateTagEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrParentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateStyleEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nTextColor,
            /* [in] */ LONG nBackColor,
            /* [in] */ VARIANT_BOOL vbTextBold,
            /* [in] */ LONG nFlagIndex,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocumentEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrSEO,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrAuthor,
            /* [in] */ BSTR bstrKeywords,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrOwner,
            /* [in] */ BSTR bstrFileType,
            /* [in] */ BSTR bstrStyleGUID,
            /* [in] */ DATE dtCreated,
            /* [in] */ DATE dtModified,
            /* [in] */ DATE dtAccessed,
            /* [in] */ LONG nIconIndex,
            /* [in] */ LONG nSync,
            /* [in] */ LONG nProtected,
            /* [in] */ LONG nReadCount,
            /* [in] */ LONG nAttachmentCount,
            /* [in] */ LONG nIndexed,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ DATE dtParamModified,
            /* [in] */ BSTR bstrParamMD5,
            /* [in] */ VARIANT vTagGUIDs,
            /* [in] */ VARIANT vParams,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [in] */ long nParts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocumentAttachmentEx( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrDocumentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [in] */ long nParts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteObject( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrType,
            /* [in] */ DATE dtDeleted) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ObjectExists( 
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrType,
            /* [retval][out] */ VARIANT_BOOL *pvbExists) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SearchDocuments( 
            /* [in] */ BSTR bstrKeywords,
            /* [in] */ LONG nFlags,
            /* [in] */ IDispatch *pFolderDisp,
            /* [in] */ LONG nMaxResults,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EmptyDeletedItems( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginUpdate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndUpdate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecentDocuments( 
            /* [in] */ BSTR bstrDocumentType,
            /* [in] */ LONG nCount,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCalendarEvents( 
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFolderByLocation( 
            /* [in] */ BSTR bstrLocation,
            /* [in] */ VARIANT_BOOL vbCreate,
            /* [retval][out] */ IDispatch **ppFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTagByName( 
            /* [in] */ BSTR bstrTagName,
            /* [in] */ VARIANT_BOOL vbCreate,
            /* [in] */ BSTR bstrRootTagForCreate,
            /* [retval][out] */ IDispatch **ppTagDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRootTagByName( 
            /* [in] */ BSTR bstrTagName,
            /* [in] */ VARIANT_BOOL vbCreate,
            /* [retval][out] */ IDispatch **ppTagDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllDocuments( 
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsModified( 
            /* [retval][out] */ VARIANT_BOOL *pvbModified) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BackupIndex( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BackupAll( 
            /* [in] */ BSTR bstrDestPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileNameToDocument( 
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVirtualFolders( 
            /* [retval][out] */ VARIANT *pvVirtualFolderNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVirtualFolderDocuments( 
            /* [in] */ BSTR bstrVirtualFolderName,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVirtualFolderIcon( 
            /* [in] */ BSTR bstrVirtualFolderName,
            /* [retval][out] */ BSTR *pbstrIconFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllFoldersDocumentCount( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT *pvDocumentCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentsFromURL( 
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentCustomGetModified( 
            /* [in] */ BSTR bstrDocumentLocation,
            /* [in] */ BSTR bstrDocumentCustomID,
            /* [retval][out] */ DATE *pdtCustomModified) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentCustomUpdate( 
            /* [in] */ BSTR bstrDocumentLocation,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDocumentCustomID,
            /* [in] */ BSTR bstrDocumentURL,
            /* [in] */ DATE dtCustomModified,
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ VARIANT_BOOL vbAllowOverwrite,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableDocumentIndexing( 
            /* [in] */ VARIANT_BOOL vbEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpDatabase( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT_BOOL *pvbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RebuildDatabase( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT_BOOL *pvbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTodoDocument( 
            /* [in] */ DATE dtDate,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCalendarEvents2( 
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [retval][out] */ IDispatch **ppEventCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetKnownRootTagName( 
            /* [in] */ BSTR bstrRootTagName,
            /* [retval][out] */ BSTR *pbstrLocalRootTagName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SQLQuery( 
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ IDispatch **ppRowsetDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SQLExecute( 
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONG *pnRowsAffect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllTagsDocumentCount( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT *pvDocumentCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddZiwFile( 
            /* [in] */ LONG nFlags,
            /* [in] */ BSTR bstrZiwFileName,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open2( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrErrorMessage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangePassword( 
            /* [in] */ BSTR bstrOldPassword,
            /* [in] */ BSTR bstrPassword) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswordFlags( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswordFlags( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEncryptedPassword( 
            /* [retval][out] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserPassword( 
            /* [retval][out] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCert( 
            /* [in] */ BSTR bstrN,
            /* [in] */ BSTR bstre,
            /* [in] */ BSTR bstrEcnryptedd,
            /* [in] */ BSTR bstrHint,
            /* [in] */ LONG nFlags,
            /* [in] */ LONGLONG nWindowHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCertN( 
            /* [retval][out] */ BSTR *pbstrN) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCerte( 
            /* [retval][out] */ BSTR *pbstre) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEncryptedCertd( 
            /* [retval][out] */ BSTR *pbstrEncrypted_d) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCertHint( 
            /* [retval][out] */ BSTR *pbstrHint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitCertFromServer( 
            /* [in] */ LONGLONG nWindowHandle) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertPassword( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AllDocumentsTitle( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentsFromTitle( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DocumentsFromTagWithChildren( 
            /* [in] */ IDispatch *pRootTagDisp,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRecentDocuments2( 
            /* [in] */ LONG nFlags,
            /* [in] */ BSTR bstrDocumentType,
            /* [in] */ LONG nCount,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDatabase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDatabase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDatabase * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDatabase * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDatabase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDatabase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDatabase * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrDatabasePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IWizDatabase * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DatabasePath )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Folders )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RootTags )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tags )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Styles )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attachments )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Metas )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MetasByName )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrMetaName,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Meta )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrMetaName,
            /* [in] */ BSTR bstrMetaKey,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Meta )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrMetaName,
            /* [in] */ BSTR bstrMetaKey,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeletedItemsFolder )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateRootFolder )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrFolderName,
            /* [in] */ VARIANT_BOOL vbSync,
            /* [retval][out] */ IDispatch **ppNewFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateRootFolder2 )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrFolderName,
            /* [in] */ VARIANT_BOOL vbSync,
            /* [in] */ BSTR bstrIconFileName,
            /* [retval][out] */ IDispatch **ppNewFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateRootTag )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrRootTagName,
            /* [in] */ BSTR bstrTagDescription,
            /* [retval][out] */ IDispatch **ppNewTagDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateStyle )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nTextColor,
            /* [in] */ LONG nBackColor,
            /* [in] */ VARIANT_BOOL vbTextBold,
            /* [in] */ LONG nFlagIndex,
            /* [retval][out] */ IDispatch **ppNewStyleDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TagGroupFromGUID )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrTagGroupGUID,
            /* [retval][out] */ IDispatch **ppTagGroupDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TagFromGUID )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrTagGUID,
            /* [retval][out] */ IDispatch **ppTagDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StyleFromGUID )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrStyleGUID,
            /* [retval][out] */ IDispatch **ppStyleDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentFromGUID )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrDocumentGUID,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentsFromSQL )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrSQLWhere,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentsFromTags )( 
            IWizDatabase * This,
            /* [in] */ IDispatch *pTagCollectionDisp,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AttachmentFromGUID )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrAttachmentGUID,
            /* [retval][out] */ IDispatch **ppAttachmentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectsByTime )( 
            IWizDatabase * This,
            /* [in] */ DATE dtTime,
            /* [in] */ BSTR bstrObjectType,
            /* [retval][out] */ IDispatch **ppCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetModifiedObjects )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrObjectType,
            /* [retval][out] */ IDispatch **ppCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTagGroupEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTagEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrParentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateStyleEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nTextColor,
            /* [in] */ LONG nBackColor,
            /* [in] */ VARIANT_BOOL vbTextBold,
            /* [in] */ LONG nFlagIndex,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDocumentEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrSEO,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrAuthor,
            /* [in] */ BSTR bstrKeywords,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrOwner,
            /* [in] */ BSTR bstrFileType,
            /* [in] */ BSTR bstrStyleGUID,
            /* [in] */ DATE dtCreated,
            /* [in] */ DATE dtModified,
            /* [in] */ DATE dtAccessed,
            /* [in] */ LONG nIconIndex,
            /* [in] */ LONG nSync,
            /* [in] */ LONG nProtected,
            /* [in] */ LONG nReadCount,
            /* [in] */ LONG nAttachmentCount,
            /* [in] */ LONG nIndexed,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ DATE dtParamModified,
            /* [in] */ BSTR bstrParamMD5,
            /* [in] */ VARIANT vTagGUIDs,
            /* [in] */ VARIANT vParams,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDocumentAttachmentEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrDocumentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [retval][out] */ IDispatch **ppRetDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateTagGroupEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateTagEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrParentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateStyleEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nTextColor,
            /* [in] */ LONG nBackColor,
            /* [in] */ VARIANT_BOOL vbTextBold,
            /* [in] */ LONG nFlagIndex,
            /* [in] */ DATE dtModified,
            /* [in] */ LONGLONG nVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocumentEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrSEO,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrAuthor,
            /* [in] */ BSTR bstrKeywords,
            /* [in] */ BSTR bstrType,
            /* [in] */ BSTR bstrOwner,
            /* [in] */ BSTR bstrFileType,
            /* [in] */ BSTR bstrStyleGUID,
            /* [in] */ DATE dtCreated,
            /* [in] */ DATE dtModified,
            /* [in] */ DATE dtAccessed,
            /* [in] */ LONG nIconIndex,
            /* [in] */ LONG nSync,
            /* [in] */ LONG nProtected,
            /* [in] */ LONG nReadCount,
            /* [in] */ LONG nAttachmentCount,
            /* [in] */ LONG nIndexed,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ DATE dtParamModified,
            /* [in] */ BSTR bstrParamMD5,
            /* [in] */ VARIANT vTagGUIDs,
            /* [in] */ VARIANT vParams,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [in] */ long nParts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocumentAttachmentEx )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrDocumentGUID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ DATE dtInfoModified,
            /* [in] */ BSTR bstrInfoMD5,
            /* [in] */ DATE dtDataModified,
            /* [in] */ BSTR bstrDataMD5,
            /* [in] */ IUnknown *pDataStream,
            /* [in] */ LONGLONG nVersion,
            /* [in] */ long nParts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteObject )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrType,
            /* [in] */ DATE dtDeleted);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ObjectExists )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrGUID,
            /* [in] */ BSTR bstrType,
            /* [retval][out] */ VARIANT_BOOL *pvbExists);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SearchDocuments )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrKeywords,
            /* [in] */ LONG nFlags,
            /* [in] */ IDispatch *pFolderDisp,
            /* [in] */ LONG nMaxResults,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EmptyDeletedItems )( 
            IWizDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BeginUpdate )( 
            IWizDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EndUpdate )( 
            IWizDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecentDocuments )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrDocumentType,
            /* [in] */ LONG nCount,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCalendarEvents )( 
            IWizDatabase * This,
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFolderByLocation )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ VARIANT_BOOL vbCreate,
            /* [retval][out] */ IDispatch **ppFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTagByName )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ VARIANT_BOOL vbCreate,
            /* [in] */ BSTR bstrRootTagForCreate,
            /* [retval][out] */ IDispatch **ppTagDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRootTagByName )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ VARIANT_BOOL vbCreate,
            /* [retval][out] */ IDispatch **ppTagDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAllDocuments )( 
            IWizDatabase * This,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsModified )( 
            IWizDatabase * This,
            /* [retval][out] */ VARIANT_BOOL *pvbModified);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BackupIndex )( 
            IWizDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BackupAll )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrDestPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FileNameToDocument )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVirtualFolders )( 
            IWizDatabase * This,
            /* [retval][out] */ VARIANT *pvVirtualFolderNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVirtualFolderDocuments )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrVirtualFolderName,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVirtualFolderIcon )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrVirtualFolderName,
            /* [retval][out] */ BSTR *pbstrIconFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAllFoldersDocumentCount )( 
            IWizDatabase * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT *pvDocumentCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentsFromURL )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentCustomGetModified )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrDocumentLocation,
            /* [in] */ BSTR bstrDocumentCustomID,
            /* [retval][out] */ DATE *pdtCustomModified);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentCustomUpdate )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrDocumentLocation,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDocumentCustomID,
            /* [in] */ BSTR bstrDocumentURL,
            /* [in] */ DATE dtCustomModified,
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ VARIANT_BOOL vbAllowOverwrite,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableDocumentIndexing )( 
            IWizDatabase * This,
            /* [in] */ VARIANT_BOOL vbEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpDatabase )( 
            IWizDatabase * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT_BOOL *pvbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RebuildDatabase )( 
            IWizDatabase * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT_BOOL *pvbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTodoDocument )( 
            IWizDatabase * This,
            /* [in] */ DATE dtDate,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCalendarEvents2 )( 
            IWizDatabase * This,
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [retval][out] */ IDispatch **ppEventCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetKnownRootTagName )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrRootTagName,
            /* [retval][out] */ BSTR *pbstrLocalRootTagName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SQLQuery )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ IDispatch **ppRowsetDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SQLExecute )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONG *pnRowsAffect);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAllTagsDocumentCount )( 
            IWizDatabase * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ VARIANT *pvDocumentCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddZiwFile )( 
            IWizDatabase * This,
            /* [in] */ LONG nFlags,
            /* [in] */ BSTR bstrZiwFileName,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open2 )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrErrorMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangePassword )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrOldPassword,
            /* [in] */ BSTR bstrPassword);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PasswordFlags )( 
            IWizDatabase * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PasswordFlags )( 
            IWizDatabase * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserName )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UserName )( 
            IWizDatabase * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEncryptedPassword )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUserPassword )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCert )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrN,
            /* [in] */ BSTR bstre,
            /* [in] */ BSTR bstrEcnryptedd,
            /* [in] */ BSTR bstrHint,
            /* [in] */ LONG nFlags,
            /* [in] */ LONGLONG nWindowHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCertN )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pbstrN);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCerte )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pbstre);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEncryptedCertd )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pbstrEncrypted_d);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCertHint )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pbstrHint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitCertFromServer )( 
            IWizDatabase * This,
            /* [in] */ LONGLONG nWindowHandle);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CertPassword )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CertPassword )( 
            IWizDatabase * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllDocumentsTitle )( 
            IWizDatabase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentsFromTitle )( 
            IWizDatabase * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DocumentsFromTagWithChildren )( 
            IWizDatabase * This,
            /* [in] */ IDispatch *pRootTagDisp,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRecentDocuments2 )( 
            IWizDatabase * This,
            /* [in] */ LONG nFlags,
            /* [in] */ BSTR bstrDocumentType,
            /* [in] */ LONG nCount,
            /* [retval][out] */ IDispatch **ppDocumentCollectionDisp);
        
        END_INTERFACE
    } IWizDatabaseVtbl;

    interface IWizDatabase
    {
        CONST_VTBL struct IWizDatabaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDatabase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDatabase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDatabase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDatabase_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDatabase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDatabase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDatabase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDatabase_Open(This,bstrDatabasePath)	\
    ( (This)->lpVtbl -> Open(This,bstrDatabasePath) ) 

#define IWizDatabase_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IWizDatabase_get_DatabasePath(This,pVal)	\
    ( (This)->lpVtbl -> get_DatabasePath(This,pVal) ) 

#define IWizDatabase_get_Folders(This,pVal)	\
    ( (This)->lpVtbl -> get_Folders(This,pVal) ) 

#define IWizDatabase_get_RootTags(This,pVal)	\
    ( (This)->lpVtbl -> get_RootTags(This,pVal) ) 

#define IWizDatabase_get_Tags(This,pVal)	\
    ( (This)->lpVtbl -> get_Tags(This,pVal) ) 

#define IWizDatabase_get_Styles(This,pVal)	\
    ( (This)->lpVtbl -> get_Styles(This,pVal) ) 

#define IWizDatabase_get_Attachments(This,pVal)	\
    ( (This)->lpVtbl -> get_Attachments(This,pVal) ) 

#define IWizDatabase_get_Metas(This,pVal)	\
    ( (This)->lpVtbl -> get_Metas(This,pVal) ) 

#define IWizDatabase_get_MetasByName(This,bstrMetaName,pVal)	\
    ( (This)->lpVtbl -> get_MetasByName(This,bstrMetaName,pVal) ) 

#define IWizDatabase_get_Meta(This,bstrMetaName,bstrMetaKey,pVal)	\
    ( (This)->lpVtbl -> get_Meta(This,bstrMetaName,bstrMetaKey,pVal) ) 

#define IWizDatabase_put_Meta(This,bstrMetaName,bstrMetaKey,newVal)	\
    ( (This)->lpVtbl -> put_Meta(This,bstrMetaName,bstrMetaKey,newVal) ) 

#define IWizDatabase_get_DeletedItemsFolder(This,pVal)	\
    ( (This)->lpVtbl -> get_DeletedItemsFolder(This,pVal) ) 

#define IWizDatabase_CreateRootFolder(This,bstrFolderName,vbSync,ppNewFolderDisp)	\
    ( (This)->lpVtbl -> CreateRootFolder(This,bstrFolderName,vbSync,ppNewFolderDisp) ) 

#define IWizDatabase_CreateRootFolder2(This,bstrFolderName,vbSync,bstrIconFileName,ppNewFolderDisp)	\
    ( (This)->lpVtbl -> CreateRootFolder2(This,bstrFolderName,vbSync,bstrIconFileName,ppNewFolderDisp) ) 

#define IWizDatabase_CreateRootTag(This,bstrRootTagName,bstrTagDescription,ppNewTagDisp)	\
    ( (This)->lpVtbl -> CreateRootTag(This,bstrRootTagName,bstrTagDescription,ppNewTagDisp) ) 

#define IWizDatabase_CreateStyle(This,bstrName,bstrDescription,nTextColor,nBackColor,vbTextBold,nFlagIndex,ppNewStyleDisp)	\
    ( (This)->lpVtbl -> CreateStyle(This,bstrName,bstrDescription,nTextColor,nBackColor,vbTextBold,nFlagIndex,ppNewStyleDisp) ) 

#define IWizDatabase_TagGroupFromGUID(This,bstrTagGroupGUID,ppTagGroupDisp)	\
    ( (This)->lpVtbl -> TagGroupFromGUID(This,bstrTagGroupGUID,ppTagGroupDisp) ) 

#define IWizDatabase_TagFromGUID(This,bstrTagGUID,ppTagDisp)	\
    ( (This)->lpVtbl -> TagFromGUID(This,bstrTagGUID,ppTagDisp) ) 

#define IWizDatabase_StyleFromGUID(This,bstrStyleGUID,ppStyleDisp)	\
    ( (This)->lpVtbl -> StyleFromGUID(This,bstrStyleGUID,ppStyleDisp) ) 

#define IWizDatabase_DocumentFromGUID(This,bstrDocumentGUID,ppDocumentDisp)	\
    ( (This)->lpVtbl -> DocumentFromGUID(This,bstrDocumentGUID,ppDocumentDisp) ) 

#define IWizDatabase_DocumentsFromSQL(This,bstrSQLWhere,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> DocumentsFromSQL(This,bstrSQLWhere,ppDocumentCollectionDisp) ) 

#define IWizDatabase_DocumentsFromTags(This,pTagCollectionDisp,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> DocumentsFromTags(This,pTagCollectionDisp,ppDocumentCollectionDisp) ) 

#define IWizDatabase_AttachmentFromGUID(This,bstrAttachmentGUID,ppAttachmentDisp)	\
    ( (This)->lpVtbl -> AttachmentFromGUID(This,bstrAttachmentGUID,ppAttachmentDisp) ) 

#define IWizDatabase_GetObjectsByTime(This,dtTime,bstrObjectType,ppCollectionDisp)	\
    ( (This)->lpVtbl -> GetObjectsByTime(This,dtTime,bstrObjectType,ppCollectionDisp) ) 

#define IWizDatabase_GetModifiedObjects(This,bstrObjectType,ppCollectionDisp)	\
    ( (This)->lpVtbl -> GetModifiedObjects(This,bstrObjectType,ppCollectionDisp) ) 

#define IWizDatabase_CreateTagGroupEx(This,bstrGUID,bstrName,bstrDescription,dtModified,nVersion,ppRetDisp)	\
    ( (This)->lpVtbl -> CreateTagGroupEx(This,bstrGUID,bstrName,bstrDescription,dtModified,nVersion,ppRetDisp) ) 

#define IWizDatabase_CreateTagEx(This,bstrGUID,bstrParentGUID,bstrName,bstrDescription,dtModified,nVersion,ppRetDisp)	\
    ( (This)->lpVtbl -> CreateTagEx(This,bstrGUID,bstrParentGUID,bstrName,bstrDescription,dtModified,nVersion,ppRetDisp) ) 

#define IWizDatabase_CreateStyleEx(This,bstrGUID,bstrName,bstrDescription,nTextColor,nBackColor,vbTextBold,nFlagIndex,dtModified,nVersion,ppRetDisp)	\
    ( (This)->lpVtbl -> CreateStyleEx(This,bstrGUID,bstrName,bstrDescription,nTextColor,nBackColor,vbTextBold,nFlagIndex,dtModified,nVersion,ppRetDisp) ) 

#define IWizDatabase_CreateDocumentEx(This,bstrGUID,bstrTitle,bstrLocation,bstrName,bstrSEO,bstrURL,bstrAuthor,bstrKeywords,bstrType,bstrOwner,bstrFileType,bstrStyleGUID,dtCreated,dtModified,dtAccessed,nIconIndex,nSync,nProtected,nReadCount,nAttachmentCount,nIndexed,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,dtParamModified,bstrParamMD5,vTagGUIDs,vParams,pDataStream,nVersion,ppRetDisp)	\
    ( (This)->lpVtbl -> CreateDocumentEx(This,bstrGUID,bstrTitle,bstrLocation,bstrName,bstrSEO,bstrURL,bstrAuthor,bstrKeywords,bstrType,bstrOwner,bstrFileType,bstrStyleGUID,dtCreated,dtModified,dtAccessed,nIconIndex,nSync,nProtected,nReadCount,nAttachmentCount,nIndexed,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,dtParamModified,bstrParamMD5,vTagGUIDs,vParams,pDataStream,nVersion,ppRetDisp) ) 

#define IWizDatabase_CreateDocumentAttachmentEx(This,bstrGUID,bstrDocumentGUID,bstrName,bstrURL,bstrDescription,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,pDataStream,nVersion,ppRetDisp)	\
    ( (This)->lpVtbl -> CreateDocumentAttachmentEx(This,bstrGUID,bstrDocumentGUID,bstrName,bstrURL,bstrDescription,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,pDataStream,nVersion,ppRetDisp) ) 

#define IWizDatabase_UpdateTagGroupEx(This,bstrGUID,bstrName,bstrDescription,dtModified,nVersion)	\
    ( (This)->lpVtbl -> UpdateTagGroupEx(This,bstrGUID,bstrName,bstrDescription,dtModified,nVersion) ) 

#define IWizDatabase_UpdateTagEx(This,bstrGUID,bstrParentGUID,bstrName,bstrDescription,dtModified,nVersion)	\
    ( (This)->lpVtbl -> UpdateTagEx(This,bstrGUID,bstrParentGUID,bstrName,bstrDescription,dtModified,nVersion) ) 

#define IWizDatabase_UpdateStyleEx(This,bstrGUID,bstrName,bstrDescription,nTextColor,nBackColor,vbTextBold,nFlagIndex,dtModified,nVersion)	\
    ( (This)->lpVtbl -> UpdateStyleEx(This,bstrGUID,bstrName,bstrDescription,nTextColor,nBackColor,vbTextBold,nFlagIndex,dtModified,nVersion) ) 

#define IWizDatabase_UpdateDocumentEx(This,bstrGUID,bstrTitle,bstrLocation,bstrName,bstrSEO,bstrURL,bstrAuthor,bstrKeywords,bstrType,bstrOwner,bstrFileType,bstrStyleGUID,dtCreated,dtModified,dtAccessed,nIconIndex,nSync,nProtected,nReadCount,nAttachmentCount,nIndexed,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,dtParamModified,bstrParamMD5,vTagGUIDs,vParams,pDataStream,nVersion,nParts)	\
    ( (This)->lpVtbl -> UpdateDocumentEx(This,bstrGUID,bstrTitle,bstrLocation,bstrName,bstrSEO,bstrURL,bstrAuthor,bstrKeywords,bstrType,bstrOwner,bstrFileType,bstrStyleGUID,dtCreated,dtModified,dtAccessed,nIconIndex,nSync,nProtected,nReadCount,nAttachmentCount,nIndexed,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,dtParamModified,bstrParamMD5,vTagGUIDs,vParams,pDataStream,nVersion,nParts) ) 

#define IWizDatabase_UpdateDocumentAttachmentEx(This,bstrGUID,bstrDocumentGUID,bstrName,bstrURL,bstrDescription,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,pDataStream,nVersion,nParts)	\
    ( (This)->lpVtbl -> UpdateDocumentAttachmentEx(This,bstrGUID,bstrDocumentGUID,bstrName,bstrURL,bstrDescription,dtInfoModified,bstrInfoMD5,dtDataModified,bstrDataMD5,pDataStream,nVersion,nParts) ) 

#define IWizDatabase_DeleteObject(This,bstrGUID,bstrType,dtDeleted)	\
    ( (This)->lpVtbl -> DeleteObject(This,bstrGUID,bstrType,dtDeleted) ) 

#define IWizDatabase_ObjectExists(This,bstrGUID,bstrType,pvbExists)	\
    ( (This)->lpVtbl -> ObjectExists(This,bstrGUID,bstrType,pvbExists) ) 

#define IWizDatabase_SearchDocuments(This,bstrKeywords,nFlags,pFolderDisp,nMaxResults,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> SearchDocuments(This,bstrKeywords,nFlags,pFolderDisp,nMaxResults,ppDocumentCollectionDisp) ) 

#define IWizDatabase_EmptyDeletedItems(This)	\
    ( (This)->lpVtbl -> EmptyDeletedItems(This) ) 

#define IWizDatabase_BeginUpdate(This)	\
    ( (This)->lpVtbl -> BeginUpdate(This) ) 

#define IWizDatabase_EndUpdate(This)	\
    ( (This)->lpVtbl -> EndUpdate(This) ) 

#define IWizDatabase_GetRecentDocuments(This,bstrDocumentType,nCount,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> GetRecentDocuments(This,bstrDocumentType,nCount,ppDocumentCollectionDisp) ) 

#define IWizDatabase_GetCalendarEvents(This,dtStart,dtEnd,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> GetCalendarEvents(This,dtStart,dtEnd,ppDocumentCollectionDisp) ) 

#define IWizDatabase_GetFolderByLocation(This,bstrLocation,vbCreate,ppFolderDisp)	\
    ( (This)->lpVtbl -> GetFolderByLocation(This,bstrLocation,vbCreate,ppFolderDisp) ) 

#define IWizDatabase_GetTagByName(This,bstrTagName,vbCreate,bstrRootTagForCreate,ppTagDisp)	\
    ( (This)->lpVtbl -> GetTagByName(This,bstrTagName,vbCreate,bstrRootTagForCreate,ppTagDisp) ) 

#define IWizDatabase_GetRootTagByName(This,bstrTagName,vbCreate,ppTagDisp)	\
    ( (This)->lpVtbl -> GetRootTagByName(This,bstrTagName,vbCreate,ppTagDisp) ) 

#define IWizDatabase_GetAllDocuments(This,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> GetAllDocuments(This,ppDocumentCollectionDisp) ) 

#define IWizDatabase_IsModified(This,pvbModified)	\
    ( (This)->lpVtbl -> IsModified(This,pvbModified) ) 

#define IWizDatabase_BackupIndex(This)	\
    ( (This)->lpVtbl -> BackupIndex(This) ) 

#define IWizDatabase_BackupAll(This,bstrDestPath)	\
    ( (This)->lpVtbl -> BackupAll(This,bstrDestPath) ) 

#define IWizDatabase_FileNameToDocument(This,bstrFileName,ppDocumentDisp)	\
    ( (This)->lpVtbl -> FileNameToDocument(This,bstrFileName,ppDocumentDisp) ) 

#define IWizDatabase_GetVirtualFolders(This,pvVirtualFolderNames)	\
    ( (This)->lpVtbl -> GetVirtualFolders(This,pvVirtualFolderNames) ) 

#define IWizDatabase_GetVirtualFolderDocuments(This,bstrVirtualFolderName,ppDocumentDisp)	\
    ( (This)->lpVtbl -> GetVirtualFolderDocuments(This,bstrVirtualFolderName,ppDocumentDisp) ) 

#define IWizDatabase_GetVirtualFolderIcon(This,bstrVirtualFolderName,pbstrIconFileName)	\
    ( (This)->lpVtbl -> GetVirtualFolderIcon(This,bstrVirtualFolderName,pbstrIconFileName) ) 

#define IWizDatabase_GetAllFoldersDocumentCount(This,nFlags,pvDocumentCount)	\
    ( (This)->lpVtbl -> GetAllFoldersDocumentCount(This,nFlags,pvDocumentCount) ) 

#define IWizDatabase_DocumentsFromURL(This,bstrURL,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> DocumentsFromURL(This,bstrURL,ppDocumentCollectionDisp) ) 

#define IWizDatabase_DocumentCustomGetModified(This,bstrDocumentLocation,bstrDocumentCustomID,pdtCustomModified)	\
    ( (This)->lpVtbl -> DocumentCustomGetModified(This,bstrDocumentLocation,bstrDocumentCustomID,pdtCustomModified) ) 

#define IWizDatabase_DocumentCustomUpdate(This,bstrDocumentLocation,bstrTitle,bstrDocumentCustomID,bstrDocumentURL,dtCustomModified,bstrHtmlFileName,vbAllowOverwrite,nUpdateDocumentFlags,ppDocumentDisp)	\
    ( (This)->lpVtbl -> DocumentCustomUpdate(This,bstrDocumentLocation,bstrTitle,bstrDocumentCustomID,bstrDocumentURL,dtCustomModified,bstrHtmlFileName,vbAllowOverwrite,nUpdateDocumentFlags,ppDocumentDisp) ) 

#define IWizDatabase_EnableDocumentIndexing(This,vbEnable)	\
    ( (This)->lpVtbl -> EnableDocumentIndexing(This,vbEnable) ) 

#define IWizDatabase_DumpDatabase(This,nFlags,pvbRet)	\
    ( (This)->lpVtbl -> DumpDatabase(This,nFlags,pvbRet) ) 

#define IWizDatabase_RebuildDatabase(This,nFlags,pvbRet)	\
    ( (This)->lpVtbl -> RebuildDatabase(This,nFlags,pvbRet) ) 

#define IWizDatabase_GetTodoDocument(This,dtDate,ppDocumentDisp)	\
    ( (This)->lpVtbl -> GetTodoDocument(This,dtDate,ppDocumentDisp) ) 

#define IWizDatabase_GetCalendarEvents2(This,dtStart,dtEnd,ppEventCollectionDisp)	\
    ( (This)->lpVtbl -> GetCalendarEvents2(This,dtStart,dtEnd,ppEventCollectionDisp) ) 

#define IWizDatabase_GetKnownRootTagName(This,bstrRootTagName,pbstrLocalRootTagName)	\
    ( (This)->lpVtbl -> GetKnownRootTagName(This,bstrRootTagName,pbstrLocalRootTagName) ) 

#define IWizDatabase_SQLQuery(This,bstrSQL,bstrOptions,ppRowsetDisp)	\
    ( (This)->lpVtbl -> SQLQuery(This,bstrSQL,bstrOptions,ppRowsetDisp) ) 

#define IWizDatabase_SQLExecute(This,bstrSQL,bstrOptions,pnRowsAffect)	\
    ( (This)->lpVtbl -> SQLExecute(This,bstrSQL,bstrOptions,pnRowsAffect) ) 

#define IWizDatabase_GetAllTagsDocumentCount(This,nFlags,pvDocumentCount)	\
    ( (This)->lpVtbl -> GetAllTagsDocumentCount(This,nFlags,pvDocumentCount) ) 

#define IWizDatabase_AddZiwFile(This,nFlags,bstrZiwFileName,ppDocumentDisp)	\
    ( (This)->lpVtbl -> AddZiwFile(This,nFlags,bstrZiwFileName,ppDocumentDisp) ) 

#define IWizDatabase_Open2(This,bstrDatabasePath,bstrPassword,nFlags,pbstrErrorMessage)	\
    ( (This)->lpVtbl -> Open2(This,bstrDatabasePath,bstrPassword,nFlags,pbstrErrorMessage) ) 

#define IWizDatabase_ChangePassword(This,bstrOldPassword,bstrPassword)	\
    ( (This)->lpVtbl -> ChangePassword(This,bstrOldPassword,bstrPassword) ) 

#define IWizDatabase_get_PasswordFlags(This,pVal)	\
    ( (This)->lpVtbl -> get_PasswordFlags(This,pVal) ) 

#define IWizDatabase_put_PasswordFlags(This,newVal)	\
    ( (This)->lpVtbl -> put_PasswordFlags(This,newVal) ) 

#define IWizDatabase_get_UserName(This,pVal)	\
    ( (This)->lpVtbl -> get_UserName(This,pVal) ) 

#define IWizDatabase_put_UserName(This,newVal)	\
    ( (This)->lpVtbl -> put_UserName(This,newVal) ) 

#define IWizDatabase_GetEncryptedPassword(This,pbstrPassword)	\
    ( (This)->lpVtbl -> GetEncryptedPassword(This,pbstrPassword) ) 

#define IWizDatabase_GetUserPassword(This,pbstrPassword)	\
    ( (This)->lpVtbl -> GetUserPassword(This,pbstrPassword) ) 

#define IWizDatabase_SetCert(This,bstrN,bstre,bstrEcnryptedd,bstrHint,nFlags,nWindowHandle)	\
    ( (This)->lpVtbl -> SetCert(This,bstrN,bstre,bstrEcnryptedd,bstrHint,nFlags,nWindowHandle) ) 

#define IWizDatabase_GetCertN(This,pbstrN)	\
    ( (This)->lpVtbl -> GetCertN(This,pbstrN) ) 

#define IWizDatabase_GetCerte(This,pbstre)	\
    ( (This)->lpVtbl -> GetCerte(This,pbstre) ) 

#define IWizDatabase_GetEncryptedCertd(This,pbstrEncrypted_d)	\
    ( (This)->lpVtbl -> GetEncryptedCertd(This,pbstrEncrypted_d) ) 

#define IWizDatabase_GetCertHint(This,pbstrHint)	\
    ( (This)->lpVtbl -> GetCertHint(This,pbstrHint) ) 

#define IWizDatabase_InitCertFromServer(This,nWindowHandle)	\
    ( (This)->lpVtbl -> InitCertFromServer(This,nWindowHandle) ) 

#define IWizDatabase_get_CertPassword(This,pVal)	\
    ( (This)->lpVtbl -> get_CertPassword(This,pVal) ) 

#define IWizDatabase_put_CertPassword(This,newVal)	\
    ( (This)->lpVtbl -> put_CertPassword(This,newVal) ) 

#define IWizDatabase_get_AllDocumentsTitle(This,pVal)	\
    ( (This)->lpVtbl -> get_AllDocumentsTitle(This,pVal) ) 

#define IWizDatabase_DocumentsFromTitle(This,bstrTitle,nFlags,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> DocumentsFromTitle(This,bstrTitle,nFlags,ppDocumentCollectionDisp) ) 

#define IWizDatabase_DocumentsFromTagWithChildren(This,pRootTagDisp,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> DocumentsFromTagWithChildren(This,pRootTagDisp,ppDocumentCollectionDisp) ) 

#define IWizDatabase_GetRecentDocuments2(This,nFlags,bstrDocumentType,nCount,ppDocumentCollectionDisp)	\
    ( (This)->lpVtbl -> GetRecentDocuments2(This,nFlags,bstrDocumentType,nCount,ppDocumentCollectionDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDatabase_INTERFACE_DEFINED__ */


#ifndef __IWizTagCollection_INTERFACE_DEFINED__
#define __IWizTagCollection_INTERFACE_DEFINED__

/* interface IWizTagCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizTagCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B636DAC-CCF9-481E-8519-5662F35C6B0D")
    IWizTagCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDispatch *pTagDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizTagCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizTagCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizTagCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizTagCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizTagCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizTagCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizTagCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizTagCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizTagCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizTagCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizTagCollection * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWizTagCollection * This,
            /* [in] */ IDispatch *pTagDisp);
        
        END_INTERFACE
    } IWizTagCollectionVtbl;

    interface IWizTagCollection
    {
        CONST_VTBL struct IWizTagCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizTagCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizTagCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizTagCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizTagCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizTagCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizTagCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizTagCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizTagCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizTagCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizTagCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IWizTagCollection_Add(This,pTagDisp)	\
    ( (This)->lpVtbl -> Add(This,pTagDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizTagCollection_INTERFACE_DEFINED__ */


#ifndef __IWizTag_INTERFACE_DEFINED__
#define __IWizTag_INTERFACE_DEFINED__

/* interface IWizTag */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizTag;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C710180C-D3F6-4F25-B981-B6820B01C67C")
    IWizTag : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParentTag( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ParentTag( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Documents( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParentTagGUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ LONGLONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ LONGLONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reload( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Children( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateChildTag( 
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrTagDescription,
            /* [retval][out] */ IDispatch **ppNewTagDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveToRoot( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsIn( 
            /* [in] */ IDispatch *pFolderDisp,
            /* [retval][out] */ VARIANT_BOOL *pvbRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizTagVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizTag * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizTag * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizTag * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizTag * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizTag * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizTag * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizTag * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GUID )( 
            IWizTag * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParentTag )( 
            IWizTag * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ParentTag )( 
            IWizTag * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWizTag * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWizTag * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IWizTag * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IWizTag * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateModified )( 
            IWizTag * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Documents )( 
            IWizTag * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParentTagGUID )( 
            IWizTag * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IWizTag * This,
            /* [retval][out] */ LONGLONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Version )( 
            IWizTag * This,
            /* [in] */ LONGLONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizTag * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizTag * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reload )( 
            IWizTag * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Children )( 
            IWizTag * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateChildTag )( 
            IWizTag * This,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrTagDescription,
            /* [retval][out] */ IDispatch **ppNewTagDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveToRoot )( 
            IWizTag * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsIn )( 
            IWizTag * This,
            /* [in] */ IDispatch *pFolderDisp,
            /* [retval][out] */ VARIANT_BOOL *pvbRet);
        
        END_INTERFACE
    } IWizTagVtbl;

    interface IWizTag
    {
        CONST_VTBL struct IWizTagVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizTag_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizTag_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizTag_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizTag_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizTag_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizTag_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizTag_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizTag_get_GUID(This,pVal)	\
    ( (This)->lpVtbl -> get_GUID(This,pVal) ) 

#define IWizTag_get_ParentTag(This,pVal)	\
    ( (This)->lpVtbl -> get_ParentTag(This,pVal) ) 

#define IWizTag_put_ParentTag(This,newVal)	\
    ( (This)->lpVtbl -> put_ParentTag(This,newVal) ) 

#define IWizTag_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWizTag_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IWizTag_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define IWizTag_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define IWizTag_get_DateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_DateModified(This,pVal) ) 

#define IWizTag_get_Documents(This,pVal)	\
    ( (This)->lpVtbl -> get_Documents(This,pVal) ) 

#define IWizTag_get_ParentTagGUID(This,pVal)	\
    ( (This)->lpVtbl -> get_ParentTagGUID(This,pVal) ) 

#define IWizTag_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IWizTag_put_Version(This,newVal)	\
    ( (This)->lpVtbl -> put_Version(This,newVal) ) 

#define IWizTag_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizTag_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IWizTag_Reload(This)	\
    ( (This)->lpVtbl -> Reload(This) ) 

#define IWizTag_get_Children(This,pVal)	\
    ( (This)->lpVtbl -> get_Children(This,pVal) ) 

#define IWizTag_CreateChildTag(This,bstrTagName,bstrTagDescription,ppNewTagDisp)	\
    ( (This)->lpVtbl -> CreateChildTag(This,bstrTagName,bstrTagDescription,ppNewTagDisp) ) 

#define IWizTag_MoveToRoot(This)	\
    ( (This)->lpVtbl -> MoveToRoot(This) ) 

#define IWizTag_IsIn(This,pFolderDisp,pvbRet)	\
    ( (This)->lpVtbl -> IsIn(This,pFolderDisp,pvbRet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizTag_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentCollection_INTERFACE_DEFINED__
#define __IWizDocumentCollection_INTERFACE_DEFINED__

/* interface IWizDocumentCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F8AE7F18-3C30-47D1-8902-947E5676895C")
    IWizDocumentCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDispatch *pDocumentDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizDocumentCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizDocumentCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizDocumentCollection * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWizDocumentCollection * This,
            /* [in] */ IDispatch *pDocumentDisp);
        
        END_INTERFACE
    } IWizDocumentCollectionVtbl;

    interface IWizDocumentCollection
    {
        CONST_VTBL struct IWizDocumentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizDocumentCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizDocumentCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IWizDocumentCollection_Add(This,pDocumentDisp)	\
    ( (This)->lpVtbl -> Add(This,pDocumentDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentCollection_INTERFACE_DEFINED__ */


#ifndef __IWizDocument_INTERFACE_DEFINED__
#define __IWizDocument_INTERFACE_DEFINED__

/* interface IWizDocument */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5B78A65E-6EE8-41C7-B1DA-8ECBF9D917B0")
    IWizDocument : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Author( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Author( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Keywords( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Keywords( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tags( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Tags( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SEO( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SEO( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_URL( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Owner( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileType( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IconIndex( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IconIndex( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Sync( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Sync( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Protect( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Protect( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReadCount( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttachmentCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Indexed( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Indexed( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateCreated( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DateCreated( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DateModified( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateAccessed( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DateAccessed( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoDateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoMD5( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataDateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataMD5( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParamDateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParamMD5( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Attachments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParamValue( 
            /* [in] */ BSTR bstrParamName,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ParamValue( 
            /* [in] */ BSTR bstrParamName,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Params( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StyleGUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StyleGUID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ LONGLONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ LONGLONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TagsText( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TagsText( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilePath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttachmentsFilePath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddTag( 
            /* [in] */ IDispatch *pTagDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveTag( 
            /* [in] */ IDispatch *pTagDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAllTags( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reload( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAttachment( 
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ IDispatch **ppNewAttachmentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToHtml( 
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ IDispatch *pDestFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ IDispatch *pDestFolderDisp,
            /* [retval][out] */ IDispatch **ppNewDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsIn( 
            /* [in] */ IDispatch *pFolderDisp,
            /* [retval][out] */ VARIANT_BOOL *pvbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocument( 
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocument2( 
            /* [in] */ IDispatch *pIHTMLDocument2Disp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocument3( 
            /* [in] */ BSTR bstrHtml,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocument4( 
            /* [in] */ BSTR bstrHtml,
            /* [in] */ BSTR bstrURL,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocument5( 
            /* [in] */ BSTR bstrHtmlFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDocument6( 
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ BSTR bstrURL,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CompareTo( 
            /* [in] */ IDispatch *pDocumentDisp,
            /* [in] */ LONG nCompareBy,
            /* [retval][out] */ LONG *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ UINT nFlags,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHtml( 
            /* [retval][out] */ BSTR *pbstrHtml) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BeginUpdateParams( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndUpdateParams( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddToCalendar( 
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [in] */ BSTR bstrExtInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveFromCalendar( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeTitleAndFileName( 
            /* [in] */ BSTR bstrTitle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIconFileName( 
            /* [retval][out] */ BSTR *pbstrIconFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TodoItems( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TodoItems( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Event( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Event( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddToCalendar2( 
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [in] */ BSTR bstrRecurrence,
            /* [in] */ BSTR bstrEndRecurrence,
            /* [in] */ BSTR bstrExtInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTagsText2( 
            /* [in] */ BSTR bstrTagsText,
            BSTR bstrParentTagName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PermanentlyDelete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProtectedByData( 
            /* [retval][out] */ LONG *pnProtected) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoEncrypt( 
            /* [in] */ VARIANT_BOOL vbDecrypt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocument * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocument * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocument * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocument * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocument * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocument * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocument * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GUID )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Author )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Author )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Keywords )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Keywords )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tags )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Tags )( 
            IWizDocument * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileName )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SEO )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SEO )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_URL )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_URL )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Owner )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Owner )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileType )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileType )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Style )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Style )( 
            IWizDocument * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IconIndex )( 
            IWizDocument * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IconIndex )( 
            IWizDocument * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sync )( 
            IWizDocument * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sync )( 
            IWizDocument * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Protect )( 
            IWizDocument * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Protect )( 
            IWizDocument * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReadCount )( 
            IWizDocument * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReadCount )( 
            IWizDocument * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttachmentCount )( 
            IWizDocument * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Indexed )( 
            IWizDocument * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Indexed )( 
            IWizDocument * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateCreated )( 
            IWizDocument * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DateCreated )( 
            IWizDocument * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateModified )( 
            IWizDocument * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DateModified )( 
            IWizDocument * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateAccessed )( 
            IWizDocument * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DateAccessed )( 
            IWizDocument * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InfoDateModified )( 
            IWizDocument * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InfoMD5 )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataDateModified )( 
            IWizDocument * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataMD5 )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParamDateModified )( 
            IWizDocument * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParamMD5 )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Attachments )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParamValue )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrParamName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ParamValue )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrParamName,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Params )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StyleGUID )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StyleGUID )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IWizDocument * This,
            /* [retval][out] */ LONGLONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Version )( 
            IWizDocument * This,
            /* [in] */ LONGLONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TagsText )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TagsText )( 
            IWizDocument * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FilePath )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttachmentsFilePath )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddTag )( 
            IWizDocument * This,
            /* [in] */ IDispatch *pTagDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveTag )( 
            IWizDocument * This,
            /* [in] */ IDispatch *pTagDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllTags )( 
            IWizDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reload )( 
            IWizDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAttachment )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ IDispatch **ppNewAttachmentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveToHtml )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            IWizDocument * This,
            /* [in] */ IDispatch *pDestFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CopyTo )( 
            IWizDocument * This,
            /* [in] */ IDispatch *pDestFolderDisp,
            /* [retval][out] */ IDispatch **ppNewDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsIn )( 
            IWizDocument * This,
            /* [in] */ IDispatch *pFolderDisp,
            /* [retval][out] */ VARIANT_BOOL *pvbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocument )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocument2 )( 
            IWizDocument * This,
            /* [in] */ IDispatch *pIHTMLDocument2Disp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocument3 )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrHtml,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocument4 )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrHtml,
            /* [in] */ BSTR bstrURL,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocument5 )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrHtmlFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDocument6 )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrHtmlFileName,
            /* [in] */ BSTR bstrURL,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CompareTo )( 
            IWizDocument * This,
            /* [in] */ IDispatch *pDocumentDisp,
            /* [in] */ LONG nCompareBy,
            /* [retval][out] */ LONG *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IWizDocument * This,
            /* [in] */ UINT nFlags,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHtml )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pbstrHtml);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BeginUpdateParams )( 
            IWizDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EndUpdateParams )( 
            IWizDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddToCalendar )( 
            IWizDocument * This,
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [in] */ BSTR bstrExtInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveFromCalendar )( 
            IWizDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangeTitleAndFileName )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrTitle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIconFileName )( 
            IWizDocument * This,
            /* [retval][out] */ BSTR *pbstrIconFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TodoItems )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TodoItems )( 
            IWizDocument * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Event )( 
            IWizDocument * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Event )( 
            IWizDocument * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddToCalendar2 )( 
            IWizDocument * This,
            /* [in] */ DATE dtStart,
            /* [in] */ DATE dtEnd,
            /* [in] */ BSTR bstrRecurrence,
            /* [in] */ BSTR bstrEndRecurrence,
            /* [in] */ BSTR bstrExtInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTagsText2 )( 
            IWizDocument * This,
            /* [in] */ BSTR bstrTagsText,
            BSTR bstrParentTagName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PermanentlyDelete )( 
            IWizDocument * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetProtectedByData )( 
            IWizDocument * This,
            /* [retval][out] */ LONG *pnProtected);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoEncrypt )( 
            IWizDocument * This,
            /* [in] */ VARIANT_BOOL vbDecrypt);
        
        END_INTERFACE
    } IWizDocumentVtbl;

    interface IWizDocument
    {
        CONST_VTBL struct IWizDocumentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocument_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocument_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocument_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocument_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocument_get_GUID(This,pVal)	\
    ( (This)->lpVtbl -> get_GUID(This,pVal) ) 

#define IWizDocument_get_Title(This,pVal)	\
    ( (This)->lpVtbl -> get_Title(This,pVal) ) 

#define IWizDocument_put_Title(This,newVal)	\
    ( (This)->lpVtbl -> put_Title(This,newVal) ) 

#define IWizDocument_get_Author(This,pVal)	\
    ( (This)->lpVtbl -> get_Author(This,pVal) ) 

#define IWizDocument_put_Author(This,newVal)	\
    ( (This)->lpVtbl -> put_Author(This,newVal) ) 

#define IWizDocument_get_Keywords(This,pVal)	\
    ( (This)->lpVtbl -> get_Keywords(This,pVal) ) 

#define IWizDocument_put_Keywords(This,newVal)	\
    ( (This)->lpVtbl -> put_Keywords(This,newVal) ) 

#define IWizDocument_get_Tags(This,pVal)	\
    ( (This)->lpVtbl -> get_Tags(This,pVal) ) 

#define IWizDocument_put_Tags(This,newVal)	\
    ( (This)->lpVtbl -> put_Tags(This,newVal) ) 

#define IWizDocument_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWizDocument_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IWizDocument_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define IWizDocument_get_FileName(This,pVal)	\
    ( (This)->lpVtbl -> get_FileName(This,pVal) ) 

#define IWizDocument_get_SEO(This,pVal)	\
    ( (This)->lpVtbl -> get_SEO(This,pVal) ) 

#define IWizDocument_put_SEO(This,newVal)	\
    ( (This)->lpVtbl -> put_SEO(This,newVal) ) 

#define IWizDocument_get_URL(This,pVal)	\
    ( (This)->lpVtbl -> get_URL(This,pVal) ) 

#define IWizDocument_put_URL(This,newVal)	\
    ( (This)->lpVtbl -> put_URL(This,newVal) ) 

#define IWizDocument_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define IWizDocument_put_Type(This,newVal)	\
    ( (This)->lpVtbl -> put_Type(This,newVal) ) 

#define IWizDocument_get_Owner(This,pVal)	\
    ( (This)->lpVtbl -> get_Owner(This,pVal) ) 

#define IWizDocument_put_Owner(This,newVal)	\
    ( (This)->lpVtbl -> put_Owner(This,newVal) ) 

#define IWizDocument_get_FileType(This,pVal)	\
    ( (This)->lpVtbl -> get_FileType(This,pVal) ) 

#define IWizDocument_put_FileType(This,newVal)	\
    ( (This)->lpVtbl -> put_FileType(This,newVal) ) 

#define IWizDocument_get_Style(This,pVal)	\
    ( (This)->lpVtbl -> get_Style(This,pVal) ) 

#define IWizDocument_put_Style(This,newVal)	\
    ( (This)->lpVtbl -> put_Style(This,newVal) ) 

#define IWizDocument_get_IconIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_IconIndex(This,pVal) ) 

#define IWizDocument_put_IconIndex(This,newVal)	\
    ( (This)->lpVtbl -> put_IconIndex(This,newVal) ) 

#define IWizDocument_get_Sync(This,pVal)	\
    ( (This)->lpVtbl -> get_Sync(This,pVal) ) 

#define IWizDocument_put_Sync(This,newVal)	\
    ( (This)->lpVtbl -> put_Sync(This,newVal) ) 

#define IWizDocument_get_Protect(This,pVal)	\
    ( (This)->lpVtbl -> get_Protect(This,pVal) ) 

#define IWizDocument_put_Protect(This,newVal)	\
    ( (This)->lpVtbl -> put_Protect(This,newVal) ) 

#define IWizDocument_get_ReadCount(This,pVal)	\
    ( (This)->lpVtbl -> get_ReadCount(This,pVal) ) 

#define IWizDocument_put_ReadCount(This,newVal)	\
    ( (This)->lpVtbl -> put_ReadCount(This,newVal) ) 

#define IWizDocument_get_AttachmentCount(This,pVal)	\
    ( (This)->lpVtbl -> get_AttachmentCount(This,pVal) ) 

#define IWizDocument_get_Indexed(This,pVal)	\
    ( (This)->lpVtbl -> get_Indexed(This,pVal) ) 

#define IWizDocument_put_Indexed(This,newVal)	\
    ( (This)->lpVtbl -> put_Indexed(This,newVal) ) 

#define IWizDocument_get_DateCreated(This,pVal)	\
    ( (This)->lpVtbl -> get_DateCreated(This,pVal) ) 

#define IWizDocument_put_DateCreated(This,newVal)	\
    ( (This)->lpVtbl -> put_DateCreated(This,newVal) ) 

#define IWizDocument_get_DateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_DateModified(This,pVal) ) 

#define IWizDocument_put_DateModified(This,newVal)	\
    ( (This)->lpVtbl -> put_DateModified(This,newVal) ) 

#define IWizDocument_get_DateAccessed(This,pVal)	\
    ( (This)->lpVtbl -> get_DateAccessed(This,pVal) ) 

#define IWizDocument_put_DateAccessed(This,newVal)	\
    ( (This)->lpVtbl -> put_DateAccessed(This,newVal) ) 

#define IWizDocument_get_InfoDateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_InfoDateModified(This,pVal) ) 

#define IWizDocument_get_InfoMD5(This,pVal)	\
    ( (This)->lpVtbl -> get_InfoMD5(This,pVal) ) 

#define IWizDocument_get_DataDateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_DataDateModified(This,pVal) ) 

#define IWizDocument_get_DataMD5(This,pVal)	\
    ( (This)->lpVtbl -> get_DataMD5(This,pVal) ) 

#define IWizDocument_get_ParamDateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_ParamDateModified(This,pVal) ) 

#define IWizDocument_get_ParamMD5(This,pVal)	\
    ( (This)->lpVtbl -> get_ParamMD5(This,pVal) ) 

#define IWizDocument_get_Attachments(This,pVal)	\
    ( (This)->lpVtbl -> get_Attachments(This,pVal) ) 

#define IWizDocument_get_ParamValue(This,bstrParamName,pVal)	\
    ( (This)->lpVtbl -> get_ParamValue(This,bstrParamName,pVal) ) 

#define IWizDocument_put_ParamValue(This,bstrParamName,newVal)	\
    ( (This)->lpVtbl -> put_ParamValue(This,bstrParamName,newVal) ) 

#define IWizDocument_get_Params(This,pVal)	\
    ( (This)->lpVtbl -> get_Params(This,pVal) ) 

#define IWizDocument_get_Parent(This,pVal)	\
    ( (This)->lpVtbl -> get_Parent(This,pVal) ) 

#define IWizDocument_get_StyleGUID(This,pVal)	\
    ( (This)->lpVtbl -> get_StyleGUID(This,pVal) ) 

#define IWizDocument_put_StyleGUID(This,newVal)	\
    ( (This)->lpVtbl -> put_StyleGUID(This,newVal) ) 

#define IWizDocument_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IWizDocument_put_Version(This,newVal)	\
    ( (This)->lpVtbl -> put_Version(This,newVal) ) 

#define IWizDocument_get_TagsText(This,pVal)	\
    ( (This)->lpVtbl -> get_TagsText(This,pVal) ) 

#define IWizDocument_put_TagsText(This,newVal)	\
    ( (This)->lpVtbl -> put_TagsText(This,newVal) ) 

#define IWizDocument_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizDocument_get_FilePath(This,pVal)	\
    ( (This)->lpVtbl -> get_FilePath(This,pVal) ) 

#define IWizDocument_get_AttachmentsFilePath(This,pVal)	\
    ( (This)->lpVtbl -> get_AttachmentsFilePath(This,pVal) ) 

#define IWizDocument_AddTag(This,pTagDisp)	\
    ( (This)->lpVtbl -> AddTag(This,pTagDisp) ) 

#define IWizDocument_RemoveTag(This,pTagDisp)	\
    ( (This)->lpVtbl -> RemoveTag(This,pTagDisp) ) 

#define IWizDocument_RemoveAllTags(This)	\
    ( (This)->lpVtbl -> RemoveAllTags(This) ) 

#define IWizDocument_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IWizDocument_Reload(This)	\
    ( (This)->lpVtbl -> Reload(This) ) 

#define IWizDocument_AddAttachment(This,bstrFileName,ppNewAttachmentDisp)	\
    ( (This)->lpVtbl -> AddAttachment(This,bstrFileName,ppNewAttachmentDisp) ) 

#define IWizDocument_SaveToHtml(This,bstrHtmlFileName,nFlags)	\
    ( (This)->lpVtbl -> SaveToHtml(This,bstrHtmlFileName,nFlags) ) 

#define IWizDocument_MoveTo(This,pDestFolderDisp)	\
    ( (This)->lpVtbl -> MoveTo(This,pDestFolderDisp) ) 

#define IWizDocument_CopyTo(This,pDestFolderDisp,ppNewDocumentDisp)	\
    ( (This)->lpVtbl -> CopyTo(This,pDestFolderDisp,ppNewDocumentDisp) ) 

#define IWizDocument_IsIn(This,pFolderDisp,pvbRet)	\
    ( (This)->lpVtbl -> IsIn(This,pFolderDisp,pvbRet) ) 

#define IWizDocument_UpdateDocument(This,bstrHtmlFileName,nFlags)	\
    ( (This)->lpVtbl -> UpdateDocument(This,bstrHtmlFileName,nFlags) ) 

#define IWizDocument_UpdateDocument2(This,pIHTMLDocument2Disp,nFlags)	\
    ( (This)->lpVtbl -> UpdateDocument2(This,pIHTMLDocument2Disp,nFlags) ) 

#define IWizDocument_UpdateDocument3(This,bstrHtml,nFlags)	\
    ( (This)->lpVtbl -> UpdateDocument3(This,bstrHtml,nFlags) ) 

#define IWizDocument_UpdateDocument4(This,bstrHtml,bstrURL,nFlags)	\
    ( (This)->lpVtbl -> UpdateDocument4(This,bstrHtml,bstrURL,nFlags) ) 

#define IWizDocument_UpdateDocument5(This,bstrHtmlFileName)	\
    ( (This)->lpVtbl -> UpdateDocument5(This,bstrHtmlFileName) ) 

#define IWizDocument_UpdateDocument6(This,bstrHtmlFileName,bstrURL,nFlags)	\
    ( (This)->lpVtbl -> UpdateDocument6(This,bstrHtmlFileName,bstrURL,nFlags) ) 

#define IWizDocument_CompareTo(This,pDocumentDisp,nCompareBy,pnRet)	\
    ( (This)->lpVtbl -> CompareTo(This,pDocumentDisp,nCompareBy,pnRet) ) 

#define IWizDocument_GetText(This,nFlags,pbstrText)	\
    ( (This)->lpVtbl -> GetText(This,nFlags,pbstrText) ) 

#define IWizDocument_GetHtml(This,pbstrHtml)	\
    ( (This)->lpVtbl -> GetHtml(This,pbstrHtml) ) 

#define IWizDocument_BeginUpdateParams(This)	\
    ( (This)->lpVtbl -> BeginUpdateParams(This) ) 

#define IWizDocument_EndUpdateParams(This)	\
    ( (This)->lpVtbl -> EndUpdateParams(This) ) 

#define IWizDocument_AddToCalendar(This,dtStart,dtEnd,bstrExtInfo)	\
    ( (This)->lpVtbl -> AddToCalendar(This,dtStart,dtEnd,bstrExtInfo) ) 

#define IWizDocument_RemoveFromCalendar(This)	\
    ( (This)->lpVtbl -> RemoveFromCalendar(This) ) 

#define IWizDocument_ChangeTitleAndFileName(This,bstrTitle)	\
    ( (This)->lpVtbl -> ChangeTitleAndFileName(This,bstrTitle) ) 

#define IWizDocument_GetIconFileName(This,pbstrIconFileName)	\
    ( (This)->lpVtbl -> GetIconFileName(This,pbstrIconFileName) ) 

#define IWizDocument_get_TodoItems(This,pVal)	\
    ( (This)->lpVtbl -> get_TodoItems(This,pVal) ) 

#define IWizDocument_put_TodoItems(This,newVal)	\
    ( (This)->lpVtbl -> put_TodoItems(This,newVal) ) 

#define IWizDocument_get_Event(This,pVal)	\
    ( (This)->lpVtbl -> get_Event(This,pVal) ) 

#define IWizDocument_put_Event(This,newVal)	\
    ( (This)->lpVtbl -> put_Event(This,newVal) ) 

#define IWizDocument_AddToCalendar2(This,dtStart,dtEnd,bstrRecurrence,bstrEndRecurrence,bstrExtInfo)	\
    ( (This)->lpVtbl -> AddToCalendar2(This,dtStart,dtEnd,bstrRecurrence,bstrEndRecurrence,bstrExtInfo) ) 

#define IWizDocument_SetTagsText2(This,bstrTagsText,bstrParentTagName)	\
    ( (This)->lpVtbl -> SetTagsText2(This,bstrTagsText,bstrParentTagName) ) 

#define IWizDocument_PermanentlyDelete(This)	\
    ( (This)->lpVtbl -> PermanentlyDelete(This) ) 

#define IWizDocument_GetProtectedByData(This,pnProtected)	\
    ( (This)->lpVtbl -> GetProtectedByData(This,pnProtected) ) 

#define IWizDocument_AutoEncrypt(This,vbDecrypt)	\
    ( (This)->lpVtbl -> AutoEncrypt(This,vbDecrypt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocument_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentAttachmentCollection_INTERFACE_DEFINED__
#define __IWizDocumentAttachmentCollection_INTERFACE_DEFINED__

/* interface IWizDocumentAttachmentCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentAttachmentCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B1E33B1-C799-4F7F-8926-54A512D45635")
    IWizDocumentAttachmentCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDispatch *pDocumentAttachmentDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentAttachmentCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentAttachmentCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentAttachmentCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentAttachmentCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentAttachmentCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentAttachmentCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentAttachmentCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentAttachmentCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizDocumentAttachmentCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizDocumentAttachmentCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizDocumentAttachmentCollection * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWizDocumentAttachmentCollection * This,
            /* [in] */ IDispatch *pDocumentAttachmentDisp);
        
        END_INTERFACE
    } IWizDocumentAttachmentCollectionVtbl;

    interface IWizDocumentAttachmentCollection
    {
        CONST_VTBL struct IWizDocumentAttachmentCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentAttachmentCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentAttachmentCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentAttachmentCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentAttachmentCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentAttachmentCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentAttachmentCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentAttachmentCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentAttachmentCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizDocumentAttachmentCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizDocumentAttachmentCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IWizDocumentAttachmentCollection_Add(This,pDocumentAttachmentDisp)	\
    ( (This)->lpVtbl -> Add(This,pDocumentAttachmentDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentAttachmentCollection_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentAttachment_INTERFACE_DEFINED__
#define __IWizDocumentAttachment_INTERFACE_DEFINED__

/* interface IWizDocumentAttachment */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentAttachment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9368D723-8B76-45C3-9B65-BD88B0A1BE64")
    IWizDocumentAttachment : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_URL( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoDateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoMD5( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataDateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataMD5( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DocumentGUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ LONGLONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ LONGLONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reload( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateDataMD5( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentAttachmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentAttachment * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentAttachment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentAttachment * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentAttachment * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentAttachment * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentAttachment * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentAttachment * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GUID )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWizDocumentAttachment * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IWizDocumentAttachment * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_URL )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_URL )( 
            IWizDocumentAttachment * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Size )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InfoDateModified )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InfoMD5 )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataDateModified )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataMD5 )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DocumentGUID )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileName )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IWizDocumentAttachment * This,
            /* [retval][out] */ LONGLONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Version )( 
            IWizDocumentAttachment * This,
            /* [in] */ LONGLONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizDocumentAttachment * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reload )( 
            IWizDocumentAttachment * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UpdateDataMD5 )( 
            IWizDocumentAttachment * This);
        
        END_INTERFACE
    } IWizDocumentAttachmentVtbl;

    interface IWizDocumentAttachment
    {
        CONST_VTBL struct IWizDocumentAttachmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentAttachment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentAttachment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentAttachment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentAttachment_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentAttachment_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentAttachment_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentAttachment_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentAttachment_get_GUID(This,pVal)	\
    ( (This)->lpVtbl -> get_GUID(This,pVal) ) 

#define IWizDocumentAttachment_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWizDocumentAttachment_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IWizDocumentAttachment_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define IWizDocumentAttachment_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define IWizDocumentAttachment_get_URL(This,pVal)	\
    ( (This)->lpVtbl -> get_URL(This,pVal) ) 

#define IWizDocumentAttachment_put_URL(This,newVal)	\
    ( (This)->lpVtbl -> put_URL(This,newVal) ) 

#define IWizDocumentAttachment_get_Size(This,pVal)	\
    ( (This)->lpVtbl -> get_Size(This,pVal) ) 

#define IWizDocumentAttachment_get_InfoDateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_InfoDateModified(This,pVal) ) 

#define IWizDocumentAttachment_get_InfoMD5(This,pVal)	\
    ( (This)->lpVtbl -> get_InfoMD5(This,pVal) ) 

#define IWizDocumentAttachment_get_DataDateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_DataDateModified(This,pVal) ) 

#define IWizDocumentAttachment_get_DataMD5(This,pVal)	\
    ( (This)->lpVtbl -> get_DataMD5(This,pVal) ) 

#define IWizDocumentAttachment_get_Document(This,pVal)	\
    ( (This)->lpVtbl -> get_Document(This,pVal) ) 

#define IWizDocumentAttachment_get_DocumentGUID(This,pVal)	\
    ( (This)->lpVtbl -> get_DocumentGUID(This,pVal) ) 

#define IWizDocumentAttachment_get_FileName(This,pVal)	\
    ( (This)->lpVtbl -> get_FileName(This,pVal) ) 

#define IWizDocumentAttachment_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IWizDocumentAttachment_put_Version(This,newVal)	\
    ( (This)->lpVtbl -> put_Version(This,newVal) ) 

#define IWizDocumentAttachment_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IWizDocumentAttachment_Reload(This)	\
    ( (This)->lpVtbl -> Reload(This) ) 

#define IWizDocumentAttachment_UpdateDataMD5(This)	\
    ( (This)->lpVtbl -> UpdateDataMD5(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentAttachment_INTERFACE_DEFINED__ */


#ifndef __IWizFolderCollection_INTERFACE_DEFINED__
#define __IWizFolderCollection_INTERFACE_DEFINED__

/* interface IWizFolderCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizFolderCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A7B925B-14C7-434B-80E9-2165CD059A79")
    IWizFolderCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizFolderCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizFolderCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizFolderCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizFolderCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizFolderCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizFolderCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizFolderCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizFolderCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizFolderCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizFolderCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizFolderCollection * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWizFolderCollectionVtbl;

    interface IWizFolderCollection
    {
        CONST_VTBL struct IWizFolderCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizFolderCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizFolderCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizFolderCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizFolderCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizFolderCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizFolderCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizFolderCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizFolderCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizFolderCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizFolderCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizFolderCollection_INTERFACE_DEFINED__ */


#ifndef __IWizFolder_INTERFACE_DEFINED__
#define __IWizFolder_INTERFACE_DEFINED__

/* interface IWizFolder */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizFolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B0E49F7C-CF4B-4DD4-A3F3-432F628C3A31")
    IWizFolder : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Sync( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Sync( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FullPath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Documents( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Folders( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsRoot( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDeletedItems( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateSubFolder( 
            /* [in] */ BSTR bstrFolderName,
            /* [retval][out] */ IDispatch **ppNewFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDocument( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ IDispatch **ppNewDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDocument2( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ IDispatch **ppNewDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ IDispatch *pDestFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveToRoot( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsIn( 
            /* [in] */ IDispatch *pFolderDisp,
            /* [retval][out] */ VARIANT_BOOL *pvbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetIcon( 
            /* [in] */ OLE_HANDLE hIcon) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetIcon2( 
            /* [in] */ BSTR bstrIconFileName,
            /* [in] */ LONG nIconIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIconFileName( 
            /* [retval][out] */ BSTR *pbstrIconFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDocumentCount( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ LONG *pnCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrDisplayName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDisplayTemplate( 
            /* [retval][out] */ BSTR *pbstrReaingTemplateFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDisplayTemplate( 
            /* [in] */ BSTR bstrReaingTemplateFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RootFolder( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Settings( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKeyName,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Settings( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKeyName,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Encrypt( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Encrypt( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizFolder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizFolder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizFolder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizFolder * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizFolder * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizFolder * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizFolder * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWizFolder * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWizFolder * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sync )( 
            IWizFolder * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sync )( 
            IWizFolder * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FullPath )( 
            IWizFolder * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IWizFolder * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Documents )( 
            IWizFolder * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Folders )( 
            IWizFolder * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsRoot )( 
            IWizFolder * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsDeletedItems )( 
            IWizFolder * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            IWizFolder * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizFolder * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateSubFolder )( 
            IWizFolder * This,
            /* [in] */ BSTR bstrFolderName,
            /* [retval][out] */ IDispatch **ppNewFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDocument )( 
            IWizFolder * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ IDispatch **ppNewDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateDocument2 )( 
            IWizFolder * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ IDispatch **ppNewDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizFolder * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            IWizFolder * This,
            /* [in] */ IDispatch *pDestFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveToRoot )( 
            IWizFolder * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsIn )( 
            IWizFolder * This,
            /* [in] */ IDispatch *pFolderDisp,
            /* [retval][out] */ VARIANT_BOOL *pvbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetIcon )( 
            IWizFolder * This,
            /* [in] */ OLE_HANDLE hIcon);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetIcon2 )( 
            IWizFolder * This,
            /* [in] */ BSTR bstrIconFileName,
            /* [in] */ LONG nIconIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIconFileName )( 
            IWizFolder * This,
            /* [retval][out] */ BSTR *pbstrIconFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDocumentCount )( 
            IWizFolder * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ LONG *pnCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisplayName )( 
            IWizFolder * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrDisplayName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDisplayTemplate )( 
            IWizFolder * This,
            /* [retval][out] */ BSTR *pbstrReaingTemplateFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDisplayTemplate )( 
            IWizFolder * This,
            /* [in] */ BSTR bstrReaingTemplateFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RootFolder )( 
            IWizFolder * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Settings )( 
            IWizFolder * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKeyName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Settings )( 
            IWizFolder * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKeyName,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Encrypt )( 
            IWizFolder * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Encrypt )( 
            IWizFolder * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IWizFolderVtbl;

    interface IWizFolder
    {
        CONST_VTBL struct IWizFolderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizFolder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizFolder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizFolder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizFolder_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizFolder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizFolder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizFolder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizFolder_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWizFolder_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IWizFolder_get_Sync(This,pVal)	\
    ( (This)->lpVtbl -> get_Sync(This,pVal) ) 

#define IWizFolder_put_Sync(This,newVal)	\
    ( (This)->lpVtbl -> put_Sync(This,newVal) ) 

#define IWizFolder_get_FullPath(This,pVal)	\
    ( (This)->lpVtbl -> get_FullPath(This,pVal) ) 

#define IWizFolder_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define IWizFolder_get_Documents(This,pVal)	\
    ( (This)->lpVtbl -> get_Documents(This,pVal) ) 

#define IWizFolder_get_Folders(This,pVal)	\
    ( (This)->lpVtbl -> get_Folders(This,pVal) ) 

#define IWizFolder_get_IsRoot(This,pVal)	\
    ( (This)->lpVtbl -> get_IsRoot(This,pVal) ) 

#define IWizFolder_get_IsDeletedItems(This,pVal)	\
    ( (This)->lpVtbl -> get_IsDeletedItems(This,pVal) ) 

#define IWizFolder_get_Parent(This,pVal)	\
    ( (This)->lpVtbl -> get_Parent(This,pVal) ) 

#define IWizFolder_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizFolder_CreateSubFolder(This,bstrFolderName,ppNewFolderDisp)	\
    ( (This)->lpVtbl -> CreateSubFolder(This,bstrFolderName,ppNewFolderDisp) ) 

#define IWizFolder_CreateDocument(This,bstrTitle,strName,bstrURL,ppNewDocumentDisp)	\
    ( (This)->lpVtbl -> CreateDocument(This,bstrTitle,strName,bstrURL,ppNewDocumentDisp) ) 

#define IWizFolder_CreateDocument2(This,bstrTitle,bstrURL,ppNewDocumentDisp)	\
    ( (This)->lpVtbl -> CreateDocument2(This,bstrTitle,bstrURL,ppNewDocumentDisp) ) 

#define IWizFolder_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IWizFolder_MoveTo(This,pDestFolderDisp)	\
    ( (This)->lpVtbl -> MoveTo(This,pDestFolderDisp) ) 

#define IWizFolder_MoveToRoot(This)	\
    ( (This)->lpVtbl -> MoveToRoot(This) ) 

#define IWizFolder_IsIn(This,pFolderDisp,pvbRet)	\
    ( (This)->lpVtbl -> IsIn(This,pFolderDisp,pvbRet) ) 

#define IWizFolder_SetIcon(This,hIcon)	\
    ( (This)->lpVtbl -> SetIcon(This,hIcon) ) 

#define IWizFolder_SetIcon2(This,bstrIconFileName,nIconIndex)	\
    ( (This)->lpVtbl -> SetIcon2(This,bstrIconFileName,nIconIndex) ) 

#define IWizFolder_GetIconFileName(This,pbstrIconFileName)	\
    ( (This)->lpVtbl -> GetIconFileName(This,pbstrIconFileName) ) 

#define IWizFolder_GetDocumentCount(This,nFlags,pnCount)	\
    ( (This)->lpVtbl -> GetDocumentCount(This,nFlags,pnCount) ) 

#define IWizFolder_GetDisplayName(This,nFlags,pbstrDisplayName)	\
    ( (This)->lpVtbl -> GetDisplayName(This,nFlags,pbstrDisplayName) ) 

#define IWizFolder_GetDisplayTemplate(This,pbstrReaingTemplateFileName)	\
    ( (This)->lpVtbl -> GetDisplayTemplate(This,pbstrReaingTemplateFileName) ) 

#define IWizFolder_SetDisplayTemplate(This,bstrReaingTemplateFileName)	\
    ( (This)->lpVtbl -> SetDisplayTemplate(This,bstrReaingTemplateFileName) ) 

#define IWizFolder_get_RootFolder(This,pVal)	\
    ( (This)->lpVtbl -> get_RootFolder(This,pVal) ) 

#define IWizFolder_get_Settings(This,bstrSection,bstrKeyName,pVal)	\
    ( (This)->lpVtbl -> get_Settings(This,bstrSection,bstrKeyName,pVal) ) 

#define IWizFolder_put_Settings(This,bstrSection,bstrKeyName,newVal)	\
    ( (This)->lpVtbl -> put_Settings(This,bstrSection,bstrKeyName,newVal) ) 

#define IWizFolder_get_Encrypt(This,pVal)	\
    ( (This)->lpVtbl -> get_Encrypt(This,pVal) ) 

#define IWizFolder_put_Encrypt(This,newVal)	\
    ( (This)->lpVtbl -> put_Encrypt(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizFolder_INTERFACE_DEFINED__ */


#ifndef __IWizStyle_INTERFACE_DEFINED__
#define __IWizStyle_INTERFACE_DEFINED__

/* interface IWizStyle */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizStyle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77C6F00C-6A41-4A14-B3E6-986401D5A5D5")
    IWizStyle : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TextColor( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TextColor( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TextBold( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TextBold( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FlagIndex( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FlagIndex( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Documents( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ LONGLONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ LONGLONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reload( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizStyleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizStyle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizStyle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizStyle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizStyle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizStyle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizStyle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizStyle * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GUID )( 
            IWizStyle * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWizStyle * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IWizStyle * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IWizStyle * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IWizStyle * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextColor )( 
            IWizStyle * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextColor )( 
            IWizStyle * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IWizStyle * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IWizStyle * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TextBold )( 
            IWizStyle * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TextBold )( 
            IWizStyle * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FlagIndex )( 
            IWizStyle * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FlagIndex )( 
            IWizStyle * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateModified )( 
            IWizStyle * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Documents )( 
            IWizStyle * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IWizStyle * This,
            /* [retval][out] */ LONGLONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Version )( 
            IWizStyle * This,
            /* [in] */ LONGLONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizStyle * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizStyle * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reload )( 
            IWizStyle * This);
        
        END_INTERFACE
    } IWizStyleVtbl;

    interface IWizStyle
    {
        CONST_VTBL struct IWizStyleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizStyle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizStyle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizStyle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizStyle_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizStyle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizStyle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizStyle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizStyle_get_GUID(This,pVal)	\
    ( (This)->lpVtbl -> get_GUID(This,pVal) ) 

#define IWizStyle_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWizStyle_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IWizStyle_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define IWizStyle_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define IWizStyle_get_TextColor(This,pVal)	\
    ( (This)->lpVtbl -> get_TextColor(This,pVal) ) 

#define IWizStyle_put_TextColor(This,newVal)	\
    ( (This)->lpVtbl -> put_TextColor(This,newVal) ) 

#define IWizStyle_get_BackColor(This,pVal)	\
    ( (This)->lpVtbl -> get_BackColor(This,pVal) ) 

#define IWizStyle_put_BackColor(This,newVal)	\
    ( (This)->lpVtbl -> put_BackColor(This,newVal) ) 

#define IWizStyle_get_TextBold(This,pVal)	\
    ( (This)->lpVtbl -> get_TextBold(This,pVal) ) 

#define IWizStyle_put_TextBold(This,newVal)	\
    ( (This)->lpVtbl -> put_TextBold(This,newVal) ) 

#define IWizStyle_get_FlagIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_FlagIndex(This,pVal) ) 

#define IWizStyle_put_FlagIndex(This,newVal)	\
    ( (This)->lpVtbl -> put_FlagIndex(This,newVal) ) 

#define IWizStyle_get_DateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_DateModified(This,pVal) ) 

#define IWizStyle_get_Documents(This,pVal)	\
    ( (This)->lpVtbl -> get_Documents(This,pVal) ) 

#define IWizStyle_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IWizStyle_put_Version(This,newVal)	\
    ( (This)->lpVtbl -> put_Version(This,newVal) ) 

#define IWizStyle_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizStyle_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IWizStyle_Reload(This)	\
    ( (This)->lpVtbl -> Reload(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizStyle_INTERFACE_DEFINED__ */


#ifndef __IWizStyleCollection_INTERFACE_DEFINED__
#define __IWizStyleCollection_INTERFACE_DEFINED__

/* interface IWizStyleCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizStyleCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6A5A90D-5766-428F-BE25-AFC9D641CB88")
    IWizStyleCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizStyleCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizStyleCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizStyleCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizStyleCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizStyleCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizStyleCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizStyleCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizStyleCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizStyleCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizStyleCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizStyleCollection * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWizStyleCollectionVtbl;

    interface IWizStyleCollection
    {
        CONST_VTBL struct IWizStyleCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizStyleCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizStyleCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizStyleCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizStyleCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizStyleCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizStyleCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizStyleCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizStyleCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizStyleCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizStyleCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizStyleCollection_INTERFACE_DEFINED__ */


#ifndef __IWizKMProtocol_INTERFACE_DEFINED__
#define __IWizKMProtocol_INTERFACE_DEFINED__

/* interface IWizKMProtocol */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizKMProtocol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("19F99E93-2C32-411E-A407-2349716D0221")
    IWizKMProtocol : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IWizKMProtocolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizKMProtocol * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizKMProtocol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizKMProtocol * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizKMProtocol * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizKMProtocol * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizKMProtocol * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizKMProtocol * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IWizKMProtocolVtbl;

    interface IWizKMProtocol
    {
        CONST_VTBL struct IWizKMProtocolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizKMProtocol_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizKMProtocol_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizKMProtocol_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizKMProtocol_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizKMProtocol_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizKMProtocol_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizKMProtocol_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizKMProtocol_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentParam_INTERFACE_DEFINED__
#define __IWizDocumentParam_INTERFACE_DEFINED__

/* interface IWizDocumentParam */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentParam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("46C5786E-A72E-4089-B4DB-70B3DD174FEB")
    IWizDocumentParam : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentParamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentParam * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentParam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentParam * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentParam * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentParam * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentParam * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentParam * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWizDocumentParam * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IWizDocumentParam * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            IWizDocumentParam * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizDocumentParam * This);
        
        END_INTERFACE
    } IWizDocumentParamVtbl;

    interface IWizDocumentParam
    {
        CONST_VTBL struct IWizDocumentParamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentParam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentParam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentParam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentParam_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentParam_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentParam_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentParam_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentParam_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWizDocumentParam_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IWizDocumentParam_get_Document(This,pVal)	\
    ( (This)->lpVtbl -> get_Document(This,pVal) ) 

#define IWizDocumentParam_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentParam_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentParamCollection_INTERFACE_DEFINED__
#define __IWizDocumentParamCollection_INTERFACE_DEFINED__

/* interface IWizDocumentParamCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentParamCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8DB6192A-1C66-4DD0-ABD4-E80C12969A13")
    IWizDocumentParamCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentParamCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentParamCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentParamCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentParamCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentParamCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentParamCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentParamCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentParamCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizDocumentParamCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizDocumentParamCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizDocumentParamCollection * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWizDocumentParamCollectionVtbl;

    interface IWizDocumentParamCollection
    {
        CONST_VTBL struct IWizDocumentParamCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentParamCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentParamCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentParamCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentParamCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentParamCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentParamCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentParamCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentParamCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizDocumentParamCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizDocumentParamCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentParamCollection_INTERFACE_DEFINED__ */


#ifndef __IWizMeta_INTERFACE_DEFINED__
#define __IWizMeta_INTERFACE_DEFINED__

/* interface IWizMeta */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizMeta;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8FEE8441-A050-4CF7-99B6-4821DB945D80")
    IWizMeta : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Key( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizMetaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizMeta * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizMeta * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizMeta * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizMeta * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizMeta * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizMeta * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizMeta * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IWizMeta * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Key )( 
            IWizMeta * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IWizMeta * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IWizMeta * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateModified )( 
            IWizMeta * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizMeta * This);
        
        END_INTERFACE
    } IWizMetaVtbl;

    interface IWizMeta
    {
        CONST_VTBL struct IWizMetaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizMeta_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizMeta_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizMeta_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizMeta_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizMeta_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizMeta_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizMeta_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizMeta_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IWizMeta_get_Key(This,pVal)	\
    ( (This)->lpVtbl -> get_Key(This,pVal) ) 

#define IWizMeta_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IWizMeta_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#define IWizMeta_get_DateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_DateModified(This,pVal) ) 

#define IWizMeta_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizMeta_INTERFACE_DEFINED__ */


#ifndef __IWizMetaCollection_INTERFACE_DEFINED__
#define __IWizMetaCollection_INTERFACE_DEFINED__

/* interface IWizMetaCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizMetaCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7492D632-5461-42BC-BF59-6D93393892F8")
    IWizMetaCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizMetaCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizMetaCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizMetaCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizMetaCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizMetaCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizMetaCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizMetaCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizMetaCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizMetaCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizMetaCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizMetaCollection * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWizMetaCollectionVtbl;

    interface IWizMetaCollection
    {
        CONST_VTBL struct IWizMetaCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizMetaCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizMetaCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizMetaCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizMetaCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizMetaCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizMetaCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizMetaCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizMetaCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizMetaCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizMetaCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizMetaCollection_INTERFACE_DEFINED__ */


#ifndef __IWizSettings_INTERFACE_DEFINED__
#define __IWizSettings_INTERFACE_DEFINED__

/* interface IWizSettings */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E3C896AD-3E1F-453E-800C-07A1837E2F23")
    IWizSettings : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDirty( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StringValue( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StringValue( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IntValue( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IntValue( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BoolValue( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BoolValue( 
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [in] */ BSTR bstrSection,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearSection( 
            /* [in] */ BSTR bstrSection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizSettings * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizSettings * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizSettings * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizSettings * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizSettings * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizSettings * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizSettings * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IWizSettings * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsDirty )( 
            IWizSettings * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StringValue )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StringValue )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IntValue )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IntValue )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoolValue )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BoolValue )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearSection )( 
            IWizSettings * This,
            /* [in] */ BSTR bstrSection);
        
        END_INTERFACE
    } IWizSettingsVtbl;

    interface IWizSettings
    {
        CONST_VTBL struct IWizSettingsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizSettings_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizSettings_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizSettings_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizSettings_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizSettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizSettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizSettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizSettings_Open(This,bstrFileName)	\
    ( (This)->lpVtbl -> Open(This,bstrFileName) ) 

#define IWizSettings_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IWizSettings_get_IsDirty(This,pVal)	\
    ( (This)->lpVtbl -> get_IsDirty(This,pVal) ) 

#define IWizSettings_get_StringValue(This,bstrSection,bstrKey,pVal)	\
    ( (This)->lpVtbl -> get_StringValue(This,bstrSection,bstrKey,pVal) ) 

#define IWizSettings_put_StringValue(This,bstrSection,bstrKey,newVal)	\
    ( (This)->lpVtbl -> put_StringValue(This,bstrSection,bstrKey,newVal) ) 

#define IWizSettings_get_IntValue(This,bstrSection,bstrKey,pVal)	\
    ( (This)->lpVtbl -> get_IntValue(This,bstrSection,bstrKey,pVal) ) 

#define IWizSettings_put_IntValue(This,bstrSection,bstrKey,newVal)	\
    ( (This)->lpVtbl -> put_IntValue(This,bstrSection,bstrKey,newVal) ) 

#define IWizSettings_get_BoolValue(This,bstrSection,bstrKey,pVal)	\
    ( (This)->lpVtbl -> get_BoolValue(This,bstrSection,bstrKey,pVal) ) 

#define IWizSettings_put_BoolValue(This,bstrSection,bstrKey,newVal)	\
    ( (This)->lpVtbl -> put_BoolValue(This,bstrSection,bstrKey,newVal) ) 

#define IWizSettings_get_Section(This,bstrSection,pVal)	\
    ( (This)->lpVtbl -> get_Section(This,bstrSection,pVal) ) 

#define IWizSettings_ClearSection(This,bstrSection)	\
    ( (This)->lpVtbl -> ClearSection(This,bstrSection) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizSettings_INTERFACE_DEFINED__ */


#ifndef __IWizSettingsSection_INTERFACE_DEFINED__
#define __IWizSettingsSection_INTERFACE_DEFINED__

/* interface IWizSettingsSection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizSettingsSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E70062FF-7718-4508-8545-3D38A13F3E9C")
    IWizSettingsSection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StringValue( 
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IntValue( 
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BoolValue( 
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizSettingsSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizSettingsSection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizSettingsSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizSettingsSection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizSettingsSection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizSettingsSection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizSettingsSection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizSettingsSection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StringValue )( 
            IWizSettingsSection * This,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IntValue )( 
            IWizSettingsSection * This,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoolValue )( 
            IWizSettingsSection * This,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IWizSettingsSectionVtbl;

    interface IWizSettingsSection
    {
        CONST_VTBL struct IWizSettingsSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizSettingsSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizSettingsSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizSettingsSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizSettingsSection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizSettingsSection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizSettingsSection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizSettingsSection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizSettingsSection_get_StringValue(This,bstrKey,pVal)	\
    ( (This)->lpVtbl -> get_StringValue(This,bstrKey,pVal) ) 

#define IWizSettingsSection_get_IntValue(This,bstrKey,pVal)	\
    ( (This)->lpVtbl -> get_IntValue(This,bstrKey,pVal) ) 

#define IWizSettingsSection_get_BoolValue(This,bstrKey,pVal)	\
    ( (This)->lpVtbl -> get_BoolValue(This,bstrKey,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizSettingsSection_INTERFACE_DEFINED__ */


#ifndef __IWizDeletedGUID_INTERFACE_DEFINED__
#define __IWizDeletedGUID_INTERFACE_DEFINED__

/* interface IWizDeletedGUID */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDeletedGUID;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A45E820-DD9D-4FF2-B66B-6CDDEDC8ABA4")
    IWizDeletedGUID : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeletedTime( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TypeValue( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ LONGLONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ LONGLONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDeletedGUIDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDeletedGUID * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDeletedGUID * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDeletedGUID * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDeletedGUID * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDeletedGUID * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDeletedGUID * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDeletedGUID * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GUID )( 
            IWizDeletedGUID * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IWizDeletedGUID * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeletedTime )( 
            IWizDeletedGUID * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TypeValue )( 
            IWizDeletedGUID * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IWizDeletedGUID * This,
            /* [retval][out] */ LONGLONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Version )( 
            IWizDeletedGUID * This,
            /* [in] */ LONGLONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IWizDeletedGUID * This);
        
        END_INTERFACE
    } IWizDeletedGUIDVtbl;

    interface IWizDeletedGUID
    {
        CONST_VTBL struct IWizDeletedGUIDVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDeletedGUID_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDeletedGUID_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDeletedGUID_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDeletedGUID_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDeletedGUID_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDeletedGUID_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDeletedGUID_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDeletedGUID_get_GUID(This,pVal)	\
    ( (This)->lpVtbl -> get_GUID(This,pVal) ) 

#define IWizDeletedGUID_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define IWizDeletedGUID_get_DeletedTime(This,pVal)	\
    ( (This)->lpVtbl -> get_DeletedTime(This,pVal) ) 

#define IWizDeletedGUID_get_TypeValue(This,pVal)	\
    ( (This)->lpVtbl -> get_TypeValue(This,pVal) ) 

#define IWizDeletedGUID_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IWizDeletedGUID_put_Version(This,newVal)	\
    ( (This)->lpVtbl -> put_Version(This,newVal) ) 

#define IWizDeletedGUID_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDeletedGUID_INTERFACE_DEFINED__ */


#ifndef __IWizDeletedGUIDCollection_INTERFACE_DEFINED__
#define __IWizDeletedGUIDCollection_INTERFACE_DEFINED__

/* interface IWizDeletedGUIDCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDeletedGUIDCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B856EEB0-1F2E-4288-B66B-4A1B8EC17708")
    IWizDeletedGUIDCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDeletedGUIDCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDeletedGUIDCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDeletedGUIDCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDeletedGUIDCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDeletedGUIDCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDeletedGUIDCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDeletedGUIDCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDeletedGUIDCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizDeletedGUIDCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizDeletedGUIDCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizDeletedGUIDCollection * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWizDeletedGUIDCollectionVtbl;

    interface IWizDeletedGUIDCollection
    {
        CONST_VTBL struct IWizDeletedGUIDCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDeletedGUIDCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDeletedGUIDCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDeletedGUIDCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDeletedGUIDCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDeletedGUIDCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDeletedGUIDCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDeletedGUIDCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDeletedGUIDCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizDeletedGUIDCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizDeletedGUIDCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDeletedGUIDCollection_INTERFACE_DEFINED__ */


#ifndef __IWizKMTools_INTERFACE_DEFINED__
#define __IWizKMTools_INTERFACE_DEFINED__

/* interface IWizKMTools */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizKMTools;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2F5EFFF9-B2C0-44E3-9AC1-071404A30D00")
    IWizKMTools : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZipToHtml( 
            /* [in] */ BSTR bstrZipFileName,
            /* [in] */ BSTR bstrHtmlFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZipToHtml2( 
            /* [in] */ BSTR bstrZipFileName,
            /* [in] */ BSTR bstrFileTitleInZip,
            /* [in] */ BSTR bstrHtmlFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WindowsSearchInstalled( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GoogleDesktopInstalled( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizKMToolsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizKMTools * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizKMTools * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizKMTools * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizKMTools * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizKMTools * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizKMTools * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizKMTools * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ZipToHtml )( 
            IWizKMTools * This,
            /* [in] */ BSTR bstrZipFileName,
            /* [in] */ BSTR bstrHtmlFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ZipToHtml2 )( 
            IWizKMTools * This,
            /* [in] */ BSTR bstrZipFileName,
            /* [in] */ BSTR bstrFileTitleInZip,
            /* [in] */ BSTR bstrHtmlFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WindowsSearchInstalled )( 
            IWizKMTools * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GoogleDesktopInstalled )( 
            IWizKMTools * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IWizKMToolsVtbl;

    interface IWizKMTools
    {
        CONST_VTBL struct IWizKMToolsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizKMTools_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizKMTools_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizKMTools_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizKMTools_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizKMTools_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizKMTools_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizKMTools_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizKMTools_ZipToHtml(This,bstrZipFileName,bstrHtmlFileName)	\
    ( (This)->lpVtbl -> ZipToHtml(This,bstrZipFileName,bstrHtmlFileName) ) 

#define IWizKMTools_ZipToHtml2(This,bstrZipFileName,bstrFileTitleInZip,bstrHtmlFileName)	\
    ( (This)->lpVtbl -> ZipToHtml2(This,bstrZipFileName,bstrFileTitleInZip,bstrHtmlFileName) ) 

#define IWizKMTools_get_WindowsSearchInstalled(This,pVal)	\
    ( (This)->lpVtbl -> get_WindowsSearchInstalled(This,pVal) ) 

#define IWizKMTools_get_GoogleDesktopInstalled(This,pVal)	\
    ( (This)->lpVtbl -> get_GoogleDesktopInstalled(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizKMTools_INTERFACE_DEFINED__ */


#ifndef __IWizIndexZiwGDSPlugin_INTERFACE_DEFINED__
#define __IWizIndexZiwGDSPlugin_INTERFACE_DEFINED__

/* interface IWizIndexZiwGDSPlugin */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizIndexZiwGDSPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("432C723E-9614-47F6-B380-2CB82F052A9D")
    IWizIndexZiwGDSPlugin : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HandleFile( 
            BSTR full_path_to_file,
            IDispatch *event_factory) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizIndexZiwGDSPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizIndexZiwGDSPlugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizIndexZiwGDSPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizIndexZiwGDSPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizIndexZiwGDSPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizIndexZiwGDSPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizIndexZiwGDSPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizIndexZiwGDSPlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HandleFile )( 
            IWizIndexZiwGDSPlugin * This,
            BSTR full_path_to_file,
            IDispatch *event_factory);
        
        END_INTERFACE
    } IWizIndexZiwGDSPluginVtbl;

    interface IWizIndexZiwGDSPlugin
    {
        CONST_VTBL struct IWizIndexZiwGDSPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizIndexZiwGDSPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizIndexZiwGDSPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizIndexZiwGDSPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizIndexZiwGDSPlugin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizIndexZiwGDSPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizIndexZiwGDSPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizIndexZiwGDSPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizIndexZiwGDSPlugin_HandleFile(This,full_path_to_file,event_factory)	\
    ( (This)->lpVtbl -> HandleFile(This,full_path_to_file,event_factory) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizIndexZiwGDSPlugin_INTERFACE_DEFINED__ */


#ifndef __IWizZiwIFilter_INTERFACE_DEFINED__
#define __IWizZiwIFilter_INTERFACE_DEFINED__

/* interface IWizZiwIFilter */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizZiwIFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4ACEBC8-FB2F-4DD0-963A-67BFC0981F06")
    IWizZiwIFilter : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IWizZiwIFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizZiwIFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizZiwIFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizZiwIFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizZiwIFilter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizZiwIFilter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizZiwIFilter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizZiwIFilter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IWizZiwIFilterVtbl;

    interface IWizZiwIFilter
    {
        CONST_VTBL struct IWizZiwIFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizZiwIFilter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizZiwIFilter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizZiwIFilter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizZiwIFilter_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizZiwIFilter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizZiwIFilter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizZiwIFilter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizZiwIFilter_INTERFACE_DEFINED__ */


#ifndef __IWizTodoItem_INTERFACE_DEFINED__
#define __IWizTodoItem_INTERFACE_DEFINED__

/* interface IWizTodoItem */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizTodoItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8741532-7AC3-4EDB-87C4-E2B1C577C7AC")
    IWizTodoItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Prior( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Prior( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Complete( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Complete( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LinkedDocumentGUIDs( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LinkedDocumentGUIDs( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Blank( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Blank( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateCreated( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DateCreated( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateModified( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DateModified( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateComplete( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DateComplete( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Order( 
            /* [retval][out] */ LONGLONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Order( 
            /* [in] */ LONGLONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Children( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizTodoItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizTodoItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizTodoItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizTodoItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizTodoItem * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizTodoItem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizTodoItem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizTodoItem * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            IWizTodoItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            IWizTodoItem * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Prior )( 
            IWizTodoItem * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Prior )( 
            IWizTodoItem * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Complete )( 
            IWizTodoItem * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Complete )( 
            IWizTodoItem * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LinkedDocumentGUIDs )( 
            IWizTodoItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LinkedDocumentGUIDs )( 
            IWizTodoItem * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Blank )( 
            IWizTodoItem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Blank )( 
            IWizTodoItem * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateCreated )( 
            IWizTodoItem * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DateCreated )( 
            IWizTodoItem * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateModified )( 
            IWizTodoItem * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DateModified )( 
            IWizTodoItem * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DateComplete )( 
            IWizTodoItem * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DateComplete )( 
            IWizTodoItem * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Order )( 
            IWizTodoItem * This,
            /* [retval][out] */ LONGLONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Order )( 
            IWizTodoItem * This,
            /* [in] */ LONGLONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Children )( 
            IWizTodoItem * This,
            /* [retval][out] */ IDispatch **pVal);
        
        END_INTERFACE
    } IWizTodoItemVtbl;

    interface IWizTodoItem
    {
        CONST_VTBL struct IWizTodoItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizTodoItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizTodoItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizTodoItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizTodoItem_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizTodoItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizTodoItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizTodoItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizTodoItem_get_Text(This,pVal)	\
    ( (This)->lpVtbl -> get_Text(This,pVal) ) 

#define IWizTodoItem_put_Text(This,newVal)	\
    ( (This)->lpVtbl -> put_Text(This,newVal) ) 

#define IWizTodoItem_get_Prior(This,pVal)	\
    ( (This)->lpVtbl -> get_Prior(This,pVal) ) 

#define IWizTodoItem_put_Prior(This,newVal)	\
    ( (This)->lpVtbl -> put_Prior(This,newVal) ) 

#define IWizTodoItem_get_Complete(This,pVal)	\
    ( (This)->lpVtbl -> get_Complete(This,pVal) ) 

#define IWizTodoItem_put_Complete(This,newVal)	\
    ( (This)->lpVtbl -> put_Complete(This,newVal) ) 

#define IWizTodoItem_get_LinkedDocumentGUIDs(This,pVal)	\
    ( (This)->lpVtbl -> get_LinkedDocumentGUIDs(This,pVal) ) 

#define IWizTodoItem_put_LinkedDocumentGUIDs(This,newVal)	\
    ( (This)->lpVtbl -> put_LinkedDocumentGUIDs(This,newVal) ) 

#define IWizTodoItem_get_Blank(This,pVal)	\
    ( (This)->lpVtbl -> get_Blank(This,pVal) ) 

#define IWizTodoItem_put_Blank(This,newVal)	\
    ( (This)->lpVtbl -> put_Blank(This,newVal) ) 

#define IWizTodoItem_get_DateCreated(This,pVal)	\
    ( (This)->lpVtbl -> get_DateCreated(This,pVal) ) 

#define IWizTodoItem_put_DateCreated(This,newVal)	\
    ( (This)->lpVtbl -> put_DateCreated(This,newVal) ) 

#define IWizTodoItem_get_DateModified(This,pVal)	\
    ( (This)->lpVtbl -> get_DateModified(This,pVal) ) 

#define IWizTodoItem_put_DateModified(This,newVal)	\
    ( (This)->lpVtbl -> put_DateModified(This,newVal) ) 

#define IWizTodoItem_get_DateComplete(This,pVal)	\
    ( (This)->lpVtbl -> get_DateComplete(This,pVal) ) 

#define IWizTodoItem_put_DateComplete(This,newVal)	\
    ( (This)->lpVtbl -> put_DateComplete(This,newVal) ) 

#define IWizTodoItem_get_Order(This,pVal)	\
    ( (This)->lpVtbl -> get_Order(This,pVal) ) 

#define IWizTodoItem_put_Order(This,newVal)	\
    ( (This)->lpVtbl -> put_Order(This,newVal) ) 

#define IWizTodoItem_get_Children(This,pVal)	\
    ( (This)->lpVtbl -> get_Children(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizTodoItem_INTERFACE_DEFINED__ */


#ifndef __IWizTodoItemCollection_INTERFACE_DEFINED__
#define __IWizTodoItemCollection_INTERFACE_DEFINED__

/* interface IWizTodoItemCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizTodoItemCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("621F668F-00AF-426B-BE84-5B92C221F571")
    IWizTodoItemCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IDispatch *pTodoItemDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizTodoItemCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizTodoItemCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizTodoItemCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizTodoItemCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizTodoItemCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizTodoItemCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizTodoItemCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizTodoItemCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizTodoItemCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizTodoItemCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizTodoItemCollection * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IWizTodoItemCollection * This,
            /* [in] */ IDispatch *pTodoItemDisp);
        
        END_INTERFACE
    } IWizTodoItemCollectionVtbl;

    interface IWizTodoItemCollection
    {
        CONST_VTBL struct IWizTodoItemCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizTodoItemCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizTodoItemCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizTodoItemCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizTodoItemCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizTodoItemCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizTodoItemCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizTodoItemCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizTodoItemCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizTodoItemCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizTodoItemCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IWizTodoItemCollection_Add(This,pTodoItemDisp)	\
    ( (This)->lpVtbl -> Add(This,pTodoItemDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizTodoItemCollection_INTERFACE_DEFINED__ */


#ifndef __IWizEvent_INTERFACE_DEFINED__
#define __IWizEvent_INTERFACE_DEFINED__

/* interface IWizEvent */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D5A30441-0007-4F1B-9674-286FAF90E74C")
    IWizEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Start( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Start( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_End( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_End( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Reminder( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reminder( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Completed( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Completed( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Recurrence( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Recurrence( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EndRecurrence( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EndRecurrence( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecurrenceIndex( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecurrenceIndex( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reload( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizEvent * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizEvent * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            IWizEvent * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GUID )( 
            IWizEvent * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IWizEvent * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IWizEvent * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Start )( 
            IWizEvent * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Start )( 
            IWizEvent * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_End )( 
            IWizEvent * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_End )( 
            IWizEvent * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IWizEvent * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IWizEvent * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Reminder )( 
            IWizEvent * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Reminder )( 
            IWizEvent * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Completed )( 
            IWizEvent * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Completed )( 
            IWizEvent * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Recurrence )( 
            IWizEvent * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Recurrence )( 
            IWizEvent * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndRecurrence )( 
            IWizEvent * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndRecurrence )( 
            IWizEvent * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecurrenceIndex )( 
            IWizEvent * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecurrenceIndex )( 
            IWizEvent * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IWizEvent * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reload )( 
            IWizEvent * This);
        
        END_INTERFACE
    } IWizEventVtbl;

    interface IWizEvent
    {
        CONST_VTBL struct IWizEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizEvent_get_Document(This,pVal)	\
    ( (This)->lpVtbl -> get_Document(This,pVal) ) 

#define IWizEvent_get_GUID(This,pVal)	\
    ( (This)->lpVtbl -> get_GUID(This,pVal) ) 

#define IWizEvent_get_Title(This,pVal)	\
    ( (This)->lpVtbl -> get_Title(This,pVal) ) 

#define IWizEvent_put_Title(This,newVal)	\
    ( (This)->lpVtbl -> put_Title(This,newVal) ) 

#define IWizEvent_get_Start(This,pVal)	\
    ( (This)->lpVtbl -> get_Start(This,pVal) ) 

#define IWizEvent_put_Start(This,newVal)	\
    ( (This)->lpVtbl -> put_Start(This,newVal) ) 

#define IWizEvent_get_End(This,pVal)	\
    ( (This)->lpVtbl -> get_End(This,pVal) ) 

#define IWizEvent_put_End(This,newVal)	\
    ( (This)->lpVtbl -> put_End(This,newVal) ) 

#define IWizEvent_get_Color(This,pVal)	\
    ( (This)->lpVtbl -> get_Color(This,pVal) ) 

#define IWizEvent_put_Color(This,newVal)	\
    ( (This)->lpVtbl -> put_Color(This,newVal) ) 

#define IWizEvent_get_Reminder(This,pVal)	\
    ( (This)->lpVtbl -> get_Reminder(This,pVal) ) 

#define IWizEvent_put_Reminder(This,newVal)	\
    ( (This)->lpVtbl -> put_Reminder(This,newVal) ) 

#define IWizEvent_get_Completed(This,pVal)	\
    ( (This)->lpVtbl -> get_Completed(This,pVal) ) 

#define IWizEvent_put_Completed(This,newVal)	\
    ( (This)->lpVtbl -> put_Completed(This,newVal) ) 

#define IWizEvent_get_Recurrence(This,pVal)	\
    ( (This)->lpVtbl -> get_Recurrence(This,pVal) ) 

#define IWizEvent_put_Recurrence(This,newVal)	\
    ( (This)->lpVtbl -> put_Recurrence(This,newVal) ) 

#define IWizEvent_get_EndRecurrence(This,pVal)	\
    ( (This)->lpVtbl -> get_EndRecurrence(This,pVal) ) 

#define IWizEvent_put_EndRecurrence(This,newVal)	\
    ( (This)->lpVtbl -> put_EndRecurrence(This,newVal) ) 

#define IWizEvent_get_RecurrenceIndex(This,pVal)	\
    ( (This)->lpVtbl -> get_RecurrenceIndex(This,pVal) ) 

#define IWizEvent_put_RecurrenceIndex(This,newVal)	\
    ( (This)->lpVtbl -> put_RecurrenceIndex(This,newVal) ) 

#define IWizEvent_Save(This)	\
    ( (This)->lpVtbl -> Save(This) ) 

#define IWizEvent_Reload(This)	\
    ( (This)->lpVtbl -> Reload(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizEvent_INTERFACE_DEFINED__ */


#ifndef __IWizEventCollection_INTERFACE_DEFINED__
#define __IWizEventCollection_INTERFACE_DEFINED__

/* interface IWizEventCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizEventCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AB1D86D6-6FE7-4CCD-BD6C-1CCF88E90CCD")
    IWizEventCollection : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizEventCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizEventCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizEventCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizEventCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizEventCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizEventCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizEventCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizEventCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IWizEventCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IWizEventCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IWizEventCollection * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWizEventCollectionVtbl;

    interface IWizEventCollection
    {
        CONST_VTBL struct IWizEventCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizEventCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizEventCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizEventCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizEventCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizEventCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizEventCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizEventCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizEventCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IWizEventCollection_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define IWizEventCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizEventCollection_INTERFACE_DEFINED__ */


#ifndef __IWizRowset_INTERFACE_DEFINED__
#define __IWizRowset_INTERFACE_DEFINED__

/* interface IWizRowset */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizRowset;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74D15AA2-9E93-437C-990B-81A3D9155C06")
    IWizRowset : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EOF( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFieldValue( 
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ BSTR *pbstrFieldValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFieldValue2( 
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ VARIANT *pvRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFieldName( 
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ BSTR *pbstrFieldName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFieldType( 
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ BSTR *pbstrFieldType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveNext( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFieldValueAsStream( 
            /* [in] */ LONG nFieldIndex,
            /* [in] */ VARIANT vStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizRowsetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizRowset * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizRowset * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizRowset * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizRowset * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizRowset * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizRowset * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizRowset * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ColumnCount )( 
            IWizRowset * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EOF )( 
            IWizRowset * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFieldValue )( 
            IWizRowset * This,
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ BSTR *pbstrFieldValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFieldValue2 )( 
            IWizRowset * This,
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ VARIANT *pvRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFieldName )( 
            IWizRowset * This,
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ BSTR *pbstrFieldName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFieldType )( 
            IWizRowset * This,
            /* [in] */ LONG nFieldIndex,
            /* [retval][out] */ BSTR *pbstrFieldType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            IWizRowset * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFieldValueAsStream )( 
            IWizRowset * This,
            /* [in] */ LONG nFieldIndex,
            /* [in] */ VARIANT vStream);
        
        END_INTERFACE
    } IWizRowsetVtbl;

    interface IWizRowset
    {
        CONST_VTBL struct IWizRowsetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizRowset_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizRowset_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizRowset_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizRowset_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizRowset_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizRowset_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizRowset_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizRowset_get_ColumnCount(This,pVal)	\
    ( (This)->lpVtbl -> get_ColumnCount(This,pVal) ) 

#define IWizRowset_get_EOF(This,pVal)	\
    ( (This)->lpVtbl -> get_EOF(This,pVal) ) 

#define IWizRowset_GetFieldValue(This,nFieldIndex,pbstrFieldValue)	\
    ( (This)->lpVtbl -> GetFieldValue(This,nFieldIndex,pbstrFieldValue) ) 

#define IWizRowset_GetFieldValue2(This,nFieldIndex,pvRet)	\
    ( (This)->lpVtbl -> GetFieldValue2(This,nFieldIndex,pvRet) ) 

#define IWizRowset_GetFieldName(This,nFieldIndex,pbstrFieldName)	\
    ( (This)->lpVtbl -> GetFieldName(This,nFieldIndex,pbstrFieldName) ) 

#define IWizRowset_GetFieldType(This,nFieldIndex,pbstrFieldType)	\
    ( (This)->lpVtbl -> GetFieldType(This,nFieldIndex,pbstrFieldType) ) 

#define IWizRowset_MoveNext(This)	\
    ( (This)->lpVtbl -> MoveNext(This) ) 

#define IWizRowset_GetFieldValueAsStream(This,nFieldIndex,vStream)	\
    ( (This)->lpVtbl -> GetFieldValueAsStream(This,nFieldIndex,vStream) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizRowset_INTERFACE_DEFINED__ */


#ifndef __IWizSQLiteDatabase_INTERFACE_DEFINED__
#define __IWizSQLiteDatabase_INTERFACE_DEFINED__

/* interface IWizSQLiteDatabase */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizSQLiteDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AAD77AF9-FDD1-454A-A52F-7E2037EB5F8D")
    IWizSQLiteDatabase : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR bstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SQLQuery( 
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ IDispatch **ppRowsetDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SQLExecute( 
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONG *pnRowsAffect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizSQLiteDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizSQLiteDatabase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizSQLiteDatabase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizSQLiteDatabase * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizSQLiteDatabase * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizSQLiteDatabase * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizSQLiteDatabase * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizSQLiteDatabase * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            IWizSQLiteDatabase * This,
            /* [in] */ BSTR bstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IWizSQLiteDatabase * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SQLQuery )( 
            IWizSQLiteDatabase * This,
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ IDispatch **ppRowsetDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SQLExecute )( 
            IWizSQLiteDatabase * This,
            /* [in] */ BSTR bstrSQL,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ LONG *pnRowsAffect);
        
        END_INTERFACE
    } IWizSQLiteDatabaseVtbl;

    interface IWizSQLiteDatabase
    {
        CONST_VTBL struct IWizSQLiteDatabaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizSQLiteDatabase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizSQLiteDatabase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizSQLiteDatabase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizSQLiteDatabase_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizSQLiteDatabase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizSQLiteDatabase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizSQLiteDatabase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizSQLiteDatabase_Open(This,bstrFileName)	\
    ( (This)->lpVtbl -> Open(This,bstrFileName) ) 

#define IWizSQLiteDatabase_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IWizSQLiteDatabase_SQLQuery(This,bstrSQL,bstrOptions,ppRowsetDisp)	\
    ( (This)->lpVtbl -> SQLQuery(This,bstrSQL,bstrOptions,ppRowsetDisp) ) 

#define IWizSQLiteDatabase_SQLExecute(This,bstrSQL,bstrOptions,pnRowsAffect)	\
    ( (This)->lpVtbl -> SQLExecute(This,bstrSQL,bstrOptions,pnRowsAffect) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizSQLiteDatabase_INTERFACE_DEFINED__ */



#ifndef __WizKMCoreLib_LIBRARY_DEFINED__
#define __WizKMCoreLib_LIBRARY_DEFINED__

/* library WizKMCoreLib */
/* [helpstring][version][uuid] */ 


enum WizInitDocumentFlags
    {	wizUpdateDocumentSaveSel	= 0x1,
	wizUpdateDocumentIncludeScript	= 0x2,
	wizUpdateDocumentShowProgress	= 0x4,
	wizUpdateDocumentSaveContentOnly	= 0x8,
	wizUpdateDocumentSaveTextOnly	= 0x10,
	wizUpdateDocumentDonotDownloadFile	= 0x20,
	wizUpdateDocumentAllowAutoGetContent	= 0x40,
	wizUpdateDocumentDonotIncludeImages	= 0x80,
	wizUpdateDocumentDonotConvertLinks	= 0x100,
	wizUpdateDocumentIncludeCSSAlways	= 0x200
    } ;

enum WizDocumentGetTextFlags
    {	wizDocumentGetTextIncludeTitle	= 0x1,
	wizDocumentGetTextIncludeAllFrames	= 0x2,
	wizDocumentGetTextNoPromptPassword	= 0x4
    } ;

enum WizSearchDocumentsFlags
    {	wizSearchDocumentsIncludeSubFolders	= 0x1,
	wizSearchDocumentsFullTextSearchWindows	= 0x2,
	wizSearchDocumentsFullTextSearchGoogle	= 0x4,
	wizSearchDocumentsFullText	= 0x8
    } ;

enum WizFolderGetDisplayNameFlags
    {	wizDisplayNameIncludeDocumentCount	= 0x1,
	wizDisplayNameIDCContainsSubFolders	= 0x2
    } ;

enum WizGetAllFoldersDocumentCountFlags
    {	wizDocumentCountContainsSubFolders	= 0x2
    } ;

enum WizDocumentSaveToHtmlFlags
    {	wizDocumentToHtmlUsingDisplayTemplate	= 0x1,
	wizDocumentToHtmlUTF8	= 0x2,
	wizDocumentToHtmlUTF8BOM	= 0x4,
	wizDocumentToHtmlMhtFormat	= 0x8
    } ;

enum WizDatabasePasswordFlags
    {	wizDatabasePasswordProtect	= 0x1,
	wizDatabasePasswordProtectWizNote	= 0x2,
	wizDatabasePasswordProtectWizCalendar	= 0x4
    } ;

enum WizDatabaseOpenFlags
    {	wizDatabaseOpenNoUI	= 0x1,
	wizDatabaseOpenNoChangeAccount	= 0x2
    } ;

enum WizDatabaseSetCertFlags
    {	wizDatabaseSetCertBackupPubKeyToServer	= 0x1,
	wizDatabaseSetCertBackupPriKeyToServer	= 0x2
    } ;

enum WizDocumentPrtoect
    {	wizDocumentProtectNone	= 0,
	wizDocumentProtectRSA	= 1,
	wizDocumentProtectAES	= 2
    } ;

EXTERN_C const IID LIBID_WizKMCoreLib;

EXTERN_C const CLSID CLSID_WizDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("AB45C39E-7793-4DCE-8C3E-3DA52B07AD68")
WizDatabase;
#endif

EXTERN_C const CLSID CLSID_WizTagCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("95985FE1-9F9E-4F66-8A7D-4CBAEDCF5936")
WizTagCollection;
#endif

EXTERN_C const CLSID CLSID_WizTag;

#ifdef __cplusplus

class DECLSPEC_UUID("972019A8-D393-4EB3-B271-65E0BBBE2A2E")
WizTag;
#endif

EXTERN_C const CLSID CLSID_WizDocumentCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("6A94B47D-FD36-452D-952D-E4D550F10628")
WizDocumentCollection;
#endif

EXTERN_C const CLSID CLSID_WizDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("ED406C6B-C584-4029-B1A9-7FAE0A575C2B")
WizDocument;
#endif

EXTERN_C const CLSID CLSID_WizDocumentAttachmentCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("C06B06EA-6E58-4761-BCB0-725EA6A3804D")
WizDocumentAttachmentCollection;
#endif

EXTERN_C const CLSID CLSID_WizDocumentAttachment;

#ifdef __cplusplus

class DECLSPEC_UUID("8D95BA68-C8E1-42C2-9287-CC8231C95E7F")
WizDocumentAttachment;
#endif

EXTERN_C const CLSID CLSID_WizFolderCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("150F936F-26A4-474D-8DD3-811A88F0CB96")
WizFolderCollection;
#endif

EXTERN_C const CLSID CLSID_WizFolder;

#ifdef __cplusplus

class DECLSPEC_UUID("2DE89910-4C9B-4252-9D30-751915121E24")
WizFolder;
#endif

EXTERN_C const CLSID CLSID_WizStyle;

#ifdef __cplusplus

class DECLSPEC_UUID("872DD0F4-D6B6-4730-9087-757B5F66054C")
WizStyle;
#endif

EXTERN_C const CLSID CLSID_WizStyleCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("B8B402D3-DE9E-42E5-838B-9BA0B923C16E")
WizStyleCollection;
#endif

EXTERN_C const CLSID CLSID_WizKMProtocol;

#ifdef __cplusplus

class DECLSPEC_UUID("E4DB345D-4E98-49E5-A4E8-1C923284B978")
WizKMProtocol;
#endif

EXTERN_C const CLSID CLSID_WizDocumentParam;

#ifdef __cplusplus

class DECLSPEC_UUID("8F4F05F7-D3FC-4656-8D3B-B849DA3FB6A6")
WizDocumentParam;
#endif

EXTERN_C const CLSID CLSID_WizDocumentParamCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("1B211802-4E90-440D-905E-BF6DD322B135")
WizDocumentParamCollection;
#endif

EXTERN_C const CLSID CLSID_WizMeta;

#ifdef __cplusplus

class DECLSPEC_UUID("0DC1C265-7695-45F4-8B97-4A4B06C4DE2E")
WizMeta;
#endif

EXTERN_C const CLSID CLSID_WizMetaCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("212C4E5C-88B0-477B-B399-A4F7FD3BC034")
WizMetaCollection;
#endif

EXTERN_C const CLSID CLSID_WizSettings;

#ifdef __cplusplus

class DECLSPEC_UUID("8BC0154C-BE01-45A6-949D-A4D8E5A0D8AA")
WizSettings;
#endif

EXTERN_C const CLSID CLSID_WizSettingsSection;

#ifdef __cplusplus

class DECLSPEC_UUID("A6FFBEDF-C292-4CD7-83DC-CB2779D77483")
WizSettingsSection;
#endif

EXTERN_C const CLSID CLSID_WizDeletedGUID;

#ifdef __cplusplus

class DECLSPEC_UUID("CDC8B878-61C3-4ECA-AC3B-7B7D8091A89B")
WizDeletedGUID;
#endif

EXTERN_C const CLSID CLSID_WizDeletedGUIDCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("D69D50B6-9A9D-4BD9-AA38-2DDD05579C26")
WizDeletedGUIDCollection;
#endif

EXTERN_C const CLSID CLSID_WizKMTools;

#ifdef __cplusplus

class DECLSPEC_UUID("0862A44D-A591-4FAF-950C-EB81BE4AC372")
WizKMTools;
#endif

EXTERN_C const CLSID CLSID_WizIndexZiwGDSPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("53829D7C-8548-4C07-A2F1-A9766B9ABA01")
WizIndexZiwGDSPlugin;
#endif

EXTERN_C const CLSID CLSID_WizZiwIFilter;

#ifdef __cplusplus

class DECLSPEC_UUID("5ABFA0B0-FDE5-4337-B9F6-DE6CCAADC179")
WizZiwIFilter;
#endif

EXTERN_C const CLSID CLSID_WizTodoItem;

#ifdef __cplusplus

class DECLSPEC_UUID("AF6ADB0C-D5CB-4B83-88E8-2CA45BE7873F")
WizTodoItem;
#endif

EXTERN_C const CLSID CLSID_WizTodoItemCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("465102EA-EB28-4758-BA63-C8E177F4F3F2")
WizTodoItemCollection;
#endif

EXTERN_C const CLSID CLSID_WizEvent;

#ifdef __cplusplus

class DECLSPEC_UUID("45BC1CC7-4BDD-4D17-A8F3-DC4CE48FE584")
WizEvent;
#endif

EXTERN_C const CLSID CLSID_WizEventCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("83287FD4-35C9-4E6D-83BC-BE341E339B0D")
WizEventCollection;
#endif

EXTERN_C const CLSID CLSID_WizRowset;

#ifdef __cplusplus

class DECLSPEC_UUID("4D55D9D6-11EF-4816-9079-5C077D8EE864")
WizRowset;
#endif

EXTERN_C const CLSID CLSID_WizSQLiteDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("CD91B37A-6B51-46D1-BC7E-06C0F9F8539D")
WizSQLiteDatabase;
#endif
#endif /* __WizKMCoreLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


