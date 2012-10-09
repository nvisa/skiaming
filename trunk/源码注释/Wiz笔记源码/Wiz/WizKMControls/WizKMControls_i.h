

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sat May 28 10:15:26 2011
 */
/* Compiler settings for .\WizKMControls.idl:
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

#ifndef __WizKMControls_i_h__
#define __WizKMControls_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWizFolderTreeCtrl_FWD_DEFINED__
#define __IWizFolderTreeCtrl_FWD_DEFINED__
typedef interface IWizFolderTreeCtrl IWizFolderTreeCtrl;
#endif 	/* __IWizFolderTreeCtrl_FWD_DEFINED__ */


#ifndef __IWizStyleListBox_FWD_DEFINED__
#define __IWizStyleListBox_FWD_DEFINED__
typedef interface IWizStyleListBox IWizStyleListBox;
#endif 	/* __IWizStyleListBox_FWD_DEFINED__ */


#ifndef __IWizTagTreeCtrl_FWD_DEFINED__
#define __IWizTagTreeCtrl_FWD_DEFINED__
typedef interface IWizTagTreeCtrl IWizTagTreeCtrl;
#endif 	/* __IWizTagTreeCtrl_FWD_DEFINED__ */


#ifndef __IWizDocumentListCtrl_FWD_DEFINED__
#define __IWizDocumentListCtrl_FWD_DEFINED__
typedef interface IWizDocumentListCtrl IWizDocumentListCtrl;
#endif 	/* __IWizDocumentListCtrl_FWD_DEFINED__ */


#ifndef __IWizDocumentAttachmentListCtrl_FWD_DEFINED__
#define __IWizDocumentAttachmentListCtrl_FWD_DEFINED__
typedef interface IWizDocumentAttachmentListCtrl IWizDocumentAttachmentListCtrl;
#endif 	/* __IWizDocumentAttachmentListCtrl_FWD_DEFINED__ */


#ifndef __IWizCommonUI_FWD_DEFINED__
#define __IWizCommonUI_FWD_DEFINED__
typedef interface IWizCommonUI IWizCommonUI;
#endif 	/* __IWizCommonUI_FWD_DEFINED__ */


#ifndef __IWizBatchDownloader_FWD_DEFINED__
#define __IWizBatchDownloader_FWD_DEFINED__
typedef interface IWizBatchDownloader IWizBatchDownloader;
#endif 	/* __IWizBatchDownloader_FWD_DEFINED__ */


#ifndef __IWizProgressWindow_FWD_DEFINED__
#define __IWizProgressWindow_FWD_DEFINED__
typedef interface IWizProgressWindow IWizProgressWindow;
#endif 	/* __IWizProgressWindow_FWD_DEFINED__ */


#ifndef __IWizSyncProgressDlg_FWD_DEFINED__
#define __IWizSyncProgressDlg_FWD_DEFINED__
typedef interface IWizSyncProgressDlg IWizSyncProgressDlg;
#endif 	/* __IWizSyncProgressDlg_FWD_DEFINED__ */


#ifndef ___IWizFolderTreeCtrlEvents_FWD_DEFINED__
#define ___IWizFolderTreeCtrlEvents_FWD_DEFINED__
typedef interface _IWizFolderTreeCtrlEvents _IWizFolderTreeCtrlEvents;
#endif 	/* ___IWizFolderTreeCtrlEvents_FWD_DEFINED__ */


#ifndef __WizFolderTreeCtrl_FWD_DEFINED__
#define __WizFolderTreeCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizFolderTreeCtrl WizFolderTreeCtrl;
#else
typedef struct WizFolderTreeCtrl WizFolderTreeCtrl;
#endif /* __cplusplus */

#endif 	/* __WizFolderTreeCtrl_FWD_DEFINED__ */


#ifndef ___IWizStyleListBoxEvents_FWD_DEFINED__
#define ___IWizStyleListBoxEvents_FWD_DEFINED__
typedef interface _IWizStyleListBoxEvents _IWizStyleListBoxEvents;
#endif 	/* ___IWizStyleListBoxEvents_FWD_DEFINED__ */


#ifndef __WizStyleListBox_FWD_DEFINED__
#define __WizStyleListBox_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizStyleListBox WizStyleListBox;
#else
typedef struct WizStyleListBox WizStyleListBox;
#endif /* __cplusplus */

#endif 	/* __WizStyleListBox_FWD_DEFINED__ */


#ifndef ___IWizTagTreeCtrlEvents_FWD_DEFINED__
#define ___IWizTagTreeCtrlEvents_FWD_DEFINED__
typedef interface _IWizTagTreeCtrlEvents _IWizTagTreeCtrlEvents;
#endif 	/* ___IWizTagTreeCtrlEvents_FWD_DEFINED__ */


#ifndef __WizTagTreeCtrl_FWD_DEFINED__
#define __WizTagTreeCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizTagTreeCtrl WizTagTreeCtrl;
#else
typedef struct WizTagTreeCtrl WizTagTreeCtrl;
#endif /* __cplusplus */

#endif 	/* __WizTagTreeCtrl_FWD_DEFINED__ */


#ifndef ___IWizDocumentListCtrlEvents_FWD_DEFINED__
#define ___IWizDocumentListCtrlEvents_FWD_DEFINED__
typedef interface _IWizDocumentListCtrlEvents _IWizDocumentListCtrlEvents;
#endif 	/* ___IWizDocumentListCtrlEvents_FWD_DEFINED__ */


#ifndef __WizDocumentListCtrl_FWD_DEFINED__
#define __WizDocumentListCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentListCtrl WizDocumentListCtrl;
#else
typedef struct WizDocumentListCtrl WizDocumentListCtrl;
#endif /* __cplusplus */

#endif 	/* __WizDocumentListCtrl_FWD_DEFINED__ */


#ifndef ___IWizDocumentAttachmentListCtrlEvents_FWD_DEFINED__
#define ___IWizDocumentAttachmentListCtrlEvents_FWD_DEFINED__
typedef interface _IWizDocumentAttachmentListCtrlEvents _IWizDocumentAttachmentListCtrlEvents;
#endif 	/* ___IWizDocumentAttachmentListCtrlEvents_FWD_DEFINED__ */


#ifndef __WizDocumentAttachmentListCtrl_FWD_DEFINED__
#define __WizDocumentAttachmentListCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizDocumentAttachmentListCtrl WizDocumentAttachmentListCtrl;
#else
typedef struct WizDocumentAttachmentListCtrl WizDocumentAttachmentListCtrl;
#endif /* __cplusplus */

#endif 	/* __WizDocumentAttachmentListCtrl_FWD_DEFINED__ */


#ifndef __WizCommonUI_FWD_DEFINED__
#define __WizCommonUI_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizCommonUI WizCommonUI;
#else
typedef struct WizCommonUI WizCommonUI;
#endif /* __cplusplus */

#endif 	/* __WizCommonUI_FWD_DEFINED__ */


#ifndef __WizBatchDownloader_FWD_DEFINED__
#define __WizBatchDownloader_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizBatchDownloader WizBatchDownloader;
#else
typedef struct WizBatchDownloader WizBatchDownloader;
#endif /* __cplusplus */

#endif 	/* __WizBatchDownloader_FWD_DEFINED__ */


#ifndef __WizProgressWindow_FWD_DEFINED__
#define __WizProgressWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizProgressWindow WizProgressWindow;
#else
typedef struct WizProgressWindow WizProgressWindow;
#endif /* __cplusplus */

#endif 	/* __WizProgressWindow_FWD_DEFINED__ */


#ifndef __WizSyncProgressDlg_FWD_DEFINED__
#define __WizSyncProgressDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizSyncProgressDlg WizSyncProgressDlg;
#else
typedef struct WizSyncProgressDlg WizSyncProgressDlg;
#endif /* __cplusplus */

#endif 	/* __WizSyncProgressDlg_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWizFolderTreeCtrl_INTERFACE_DEFINED__
#define __IWizFolderTreeCtrl_INTERFACE_DEFINED__

/* interface IWizFolderTreeCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizFolderTreeCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4CE9188-C153-49D1-BC69-345B1AD693E8")
    IWizFolderTreeCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedFolder( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedFolder( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StateSection( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StateSection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisableContextMenu( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisableContextMenu( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Shadow( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Shadow( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecSimpleCommand( 
            /* [in] */ BSTR bstrCommandName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelectedDocuments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetShowVirtualFolders( 
            /* [in] */ VARIANT_BOOL bVisible) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnSelChanged( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnSelChanged( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Flags( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSelectedDocuments2( 
            /* [out] */ BSTR *pbstrSortBy,
            /* [out] */ BSTR *pbstrSortOrder,
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetShowRecentPickFolders( 
            /* [in] */ VARIANT_BOOL bVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizFolderTreeCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizFolderTreeCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizFolderTreeCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizFolderTreeCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedFolder )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedFolder )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StateSection )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StateSection )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisableContextMenu )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisableContextMenu )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shadow )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shadow )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWizFolderTreeCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExecSimpleCommand )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ BSTR bstrCommandName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSelectedDocuments )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetShowVirtualFolders )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ VARIANT_BOOL bVisible);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnSelChanged )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnSelChanged )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Flags )( 
            IWizFolderTreeCtrl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Flags )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSelectedDocuments2 )( 
            IWizFolderTreeCtrl * This,
            /* [out] */ BSTR *pbstrSortBy,
            /* [out] */ BSTR *pbstrSortOrder,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetShowRecentPickFolders )( 
            IWizFolderTreeCtrl * This,
            /* [in] */ VARIANT_BOOL bVisible);
        
        END_INTERFACE
    } IWizFolderTreeCtrlVtbl;

    interface IWizFolderTreeCtrl
    {
        CONST_VTBL struct IWizFolderTreeCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizFolderTreeCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizFolderTreeCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizFolderTreeCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizFolderTreeCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizFolderTreeCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizFolderTreeCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizFolderTreeCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizFolderTreeCtrl_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizFolderTreeCtrl_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizFolderTreeCtrl_get_SelectedFolder(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedFolder(This,pVal) ) 

#define IWizFolderTreeCtrl_put_SelectedFolder(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedFolder(This,newVal) ) 

#define IWizFolderTreeCtrl_get_StateSection(This,pVal)	\
    ( (This)->lpVtbl -> get_StateSection(This,pVal) ) 

#define IWizFolderTreeCtrl_put_StateSection(This,newVal)	\
    ( (This)->lpVtbl -> put_StateSection(This,newVal) ) 

#define IWizFolderTreeCtrl_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizFolderTreeCtrl_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizFolderTreeCtrl_get_DisableContextMenu(This,pVal)	\
    ( (This)->lpVtbl -> get_DisableContextMenu(This,pVal) ) 

#define IWizFolderTreeCtrl_put_DisableContextMenu(This,newVal)	\
    ( (This)->lpVtbl -> put_DisableContextMenu(This,newVal) ) 

#define IWizFolderTreeCtrl_get_Shadow(This,pVal)	\
    ( (This)->lpVtbl -> get_Shadow(This,pVal) ) 

#define IWizFolderTreeCtrl_put_Shadow(This,newVal)	\
    ( (This)->lpVtbl -> put_Shadow(This,newVal) ) 

#define IWizFolderTreeCtrl_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IWizFolderTreeCtrl_ExecSimpleCommand(This,bstrCommandName)	\
    ( (This)->lpVtbl -> ExecSimpleCommand(This,bstrCommandName) ) 

#define IWizFolderTreeCtrl_GetSelectedDocuments(This,pVal)	\
    ( (This)->lpVtbl -> GetSelectedDocuments(This,pVal) ) 

#define IWizFolderTreeCtrl_SetShowVirtualFolders(This,bVisible)	\
    ( (This)->lpVtbl -> SetShowVirtualFolders(This,bVisible) ) 

#define IWizFolderTreeCtrl_get_OnSelChanged(This,pVal)	\
    ( (This)->lpVtbl -> get_OnSelChanged(This,pVal) ) 

#define IWizFolderTreeCtrl_put_OnSelChanged(This,newVal)	\
    ( (This)->lpVtbl -> put_OnSelChanged(This,newVal) ) 

#define IWizFolderTreeCtrl_get_Flags(This,pVal)	\
    ( (This)->lpVtbl -> get_Flags(This,pVal) ) 

#define IWizFolderTreeCtrl_put_Flags(This,newVal)	\
    ( (This)->lpVtbl -> put_Flags(This,newVal) ) 

#define IWizFolderTreeCtrl_GetSelectedDocuments2(This,pbstrSortBy,pbstrSortOrder,pVal)	\
    ( (This)->lpVtbl -> GetSelectedDocuments2(This,pbstrSortBy,pbstrSortOrder,pVal) ) 

#define IWizFolderTreeCtrl_SetShowRecentPickFolders(This,bVisible)	\
    ( (This)->lpVtbl -> SetShowRecentPickFolders(This,bVisible) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizFolderTreeCtrl_INTERFACE_DEFINED__ */


#ifndef __IWizStyleListBox_INTERFACE_DEFINED__
#define __IWizStyleListBox_INTERFACE_DEFINED__

/* interface IWizStyleListBox */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizStyleListBox;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5AE7BE3-B10A-464A-8A4C-AA8D33E9B272")
    IWizStyleListBox : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedStyle( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedStyle( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StateSection( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StateSection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Shadow( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Shadow( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnSelChanged( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnSelChanged( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizStyleListBoxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizStyleListBox * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizStyleListBox * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizStyleListBox * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizStyleListBox * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizStyleListBox * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizStyleListBox * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizStyleListBox * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizStyleListBox * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizStyleListBox * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedStyle )( 
            IWizStyleListBox * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedStyle )( 
            IWizStyleListBox * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StateSection )( 
            IWizStyleListBox * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StateSection )( 
            IWizStyleListBox * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizStyleListBox * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizStyleListBox * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shadow )( 
            IWizStyleListBox * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shadow )( 
            IWizStyleListBox * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWizStyleListBox * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnSelChanged )( 
            IWizStyleListBox * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnSelChanged )( 
            IWizStyleListBox * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IWizStyleListBoxVtbl;

    interface IWizStyleListBox
    {
        CONST_VTBL struct IWizStyleListBoxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizStyleListBox_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizStyleListBox_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizStyleListBox_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizStyleListBox_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizStyleListBox_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizStyleListBox_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizStyleListBox_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizStyleListBox_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizStyleListBox_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizStyleListBox_get_SelectedStyle(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedStyle(This,pVal) ) 

#define IWizStyleListBox_put_SelectedStyle(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedStyle(This,newVal) ) 

#define IWizStyleListBox_get_StateSection(This,pVal)	\
    ( (This)->lpVtbl -> get_StateSection(This,pVal) ) 

#define IWizStyleListBox_put_StateSection(This,newVal)	\
    ( (This)->lpVtbl -> put_StateSection(This,newVal) ) 

#define IWizStyleListBox_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizStyleListBox_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizStyleListBox_get_Shadow(This,pVal)	\
    ( (This)->lpVtbl -> get_Shadow(This,pVal) ) 

#define IWizStyleListBox_put_Shadow(This,newVal)	\
    ( (This)->lpVtbl -> put_Shadow(This,newVal) ) 

#define IWizStyleListBox_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IWizStyleListBox_get_OnSelChanged(This,pVal)	\
    ( (This)->lpVtbl -> get_OnSelChanged(This,pVal) ) 

#define IWizStyleListBox_put_OnSelChanged(This,newVal)	\
    ( (This)->lpVtbl -> put_OnSelChanged(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizStyleListBox_INTERFACE_DEFINED__ */


#ifndef __IWizTagTreeCtrl_INTERFACE_DEFINED__
#define __IWizTagTreeCtrl_INTERFACE_DEFINED__

/* interface IWizTagTreeCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizTagTreeCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30799F2F-3377-4326-818E-1A4BF3CB715A")
    IWizTagTreeCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedTags( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedTags( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StateSection( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StateSection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Shadow( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Shadow( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnSelChanged( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnSelChanged( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Flags( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Flags( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizTagTreeCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizTagTreeCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizTagTreeCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizTagTreeCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizTagTreeCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizTagTreeCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizTagTreeCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizTagTreeCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizTagTreeCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizTagTreeCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedTags )( 
            IWizTagTreeCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedTags )( 
            IWizTagTreeCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StateSection )( 
            IWizTagTreeCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StateSection )( 
            IWizTagTreeCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizTagTreeCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizTagTreeCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shadow )( 
            IWizTagTreeCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shadow )( 
            IWizTagTreeCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWizTagTreeCtrl * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnSelChanged )( 
            IWizTagTreeCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnSelChanged )( 
            IWizTagTreeCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Flags )( 
            IWizTagTreeCtrl * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Flags )( 
            IWizTagTreeCtrl * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IWizTagTreeCtrlVtbl;

    interface IWizTagTreeCtrl
    {
        CONST_VTBL struct IWizTagTreeCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizTagTreeCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizTagTreeCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizTagTreeCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizTagTreeCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizTagTreeCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizTagTreeCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizTagTreeCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizTagTreeCtrl_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizTagTreeCtrl_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizTagTreeCtrl_get_SelectedTags(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedTags(This,pVal) ) 

#define IWizTagTreeCtrl_put_SelectedTags(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedTags(This,newVal) ) 

#define IWizTagTreeCtrl_get_StateSection(This,pVal)	\
    ( (This)->lpVtbl -> get_StateSection(This,pVal) ) 

#define IWizTagTreeCtrl_put_StateSection(This,newVal)	\
    ( (This)->lpVtbl -> put_StateSection(This,newVal) ) 

#define IWizTagTreeCtrl_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizTagTreeCtrl_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizTagTreeCtrl_get_Shadow(This,pVal)	\
    ( (This)->lpVtbl -> get_Shadow(This,pVal) ) 

#define IWizTagTreeCtrl_put_Shadow(This,newVal)	\
    ( (This)->lpVtbl -> put_Shadow(This,newVal) ) 

#define IWizTagTreeCtrl_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IWizTagTreeCtrl_get_OnSelChanged(This,pVal)	\
    ( (This)->lpVtbl -> get_OnSelChanged(This,pVal) ) 

#define IWizTagTreeCtrl_put_OnSelChanged(This,newVal)	\
    ( (This)->lpVtbl -> put_OnSelChanged(This,newVal) ) 

#define IWizTagTreeCtrl_get_Flags(This,pVal)	\
    ( (This)->lpVtbl -> get_Flags(This,pVal) ) 

#define IWizTagTreeCtrl_put_Flags(This,newVal)	\
    ( (This)->lpVtbl -> put_Flags(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizTagTreeCtrl_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentListCtrl_INTERFACE_DEFINED__
#define __IWizDocumentListCtrl_INTERFACE_DEFINED__

/* interface IWizDocumentListCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentListCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C128ECE0-A006-4E57-8054-4CBC49818231")
    IWizDocumentListCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedDocuments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedDocuments( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StateSection( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StateSection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisableContextMenu( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisableContextMenu( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SearchKeywords( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Shadow( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Shadow( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SortBy( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SortBy( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SortOrder( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SortOrder( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParentFolder( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDocuments( 
            /* [in] */ IDispatch *pDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDocuments2( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ BSTR bstrSortBy,
            /* [in] */ BSTR bstrSortOrder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDocuments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnSelChanged( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnSelChanged( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnDblClickItem( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnDblClickItem( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnExecCommand( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnExecCommand( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FocusToSearchBox( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentListCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentListCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentListCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentListCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentListCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentListCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedDocuments )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedDocuments )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StateSection )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StateSection )( 
            IWizDocumentListCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisableContextMenu )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisableContextMenu )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SearchKeywords )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shadow )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shadow )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SortBy )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SortBy )( 
            IWizDocumentListCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SortOrder )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SortOrder )( 
            IWizDocumentListCtrl * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ParentFolder )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDocuments )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *pDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDocuments2 )( 
            IWizDocumentListCtrl * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ BSTR bstrSortBy,
            /* [in] */ BSTR bstrSortOrder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IWizDocumentListCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDocuments )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnSelChanged )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnSelChanged )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnDblClickItem )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnDblClickItem )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnExecCommand )( 
            IWizDocumentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnExecCommand )( 
            IWizDocumentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FocusToSearchBox )( 
            IWizDocumentListCtrl * This);
        
        END_INTERFACE
    } IWizDocumentListCtrlVtbl;

    interface IWizDocumentListCtrl
    {
        CONST_VTBL struct IWizDocumentListCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentListCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentListCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentListCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentListCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentListCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentListCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentListCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentListCtrl_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizDocumentListCtrl_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizDocumentListCtrl_get_SelectedDocuments(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedDocuments(This,pVal) ) 

#define IWizDocumentListCtrl_put_SelectedDocuments(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedDocuments(This,newVal) ) 

#define IWizDocumentListCtrl_get_StateSection(This,pVal)	\
    ( (This)->lpVtbl -> get_StateSection(This,pVal) ) 

#define IWizDocumentListCtrl_put_StateSection(This,newVal)	\
    ( (This)->lpVtbl -> put_StateSection(This,newVal) ) 

#define IWizDocumentListCtrl_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizDocumentListCtrl_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizDocumentListCtrl_get_DisableContextMenu(This,pVal)	\
    ( (This)->lpVtbl -> get_DisableContextMenu(This,pVal) ) 

#define IWizDocumentListCtrl_put_DisableContextMenu(This,newVal)	\
    ( (This)->lpVtbl -> put_DisableContextMenu(This,newVal) ) 

#define IWizDocumentListCtrl_get_SearchKeywords(This,pVal)	\
    ( (This)->lpVtbl -> get_SearchKeywords(This,pVal) ) 

#define IWizDocumentListCtrl_get_Shadow(This,pVal)	\
    ( (This)->lpVtbl -> get_Shadow(This,pVal) ) 

#define IWizDocumentListCtrl_put_Shadow(This,newVal)	\
    ( (This)->lpVtbl -> put_Shadow(This,newVal) ) 

#define IWizDocumentListCtrl_get_SortBy(This,pVal)	\
    ( (This)->lpVtbl -> get_SortBy(This,pVal) ) 

#define IWizDocumentListCtrl_put_SortBy(This,newVal)	\
    ( (This)->lpVtbl -> put_SortBy(This,newVal) ) 

#define IWizDocumentListCtrl_get_SortOrder(This,pVal)	\
    ( (This)->lpVtbl -> get_SortOrder(This,pVal) ) 

#define IWizDocumentListCtrl_put_SortOrder(This,newVal)	\
    ( (This)->lpVtbl -> put_SortOrder(This,newVal) ) 

#define IWizDocumentListCtrl_get_ParentFolder(This,pVal)	\
    ( (This)->lpVtbl -> get_ParentFolder(This,pVal) ) 

#define IWizDocumentListCtrl_SetDocuments(This,pDisp)	\
    ( (This)->lpVtbl -> SetDocuments(This,pDisp) ) 

#define IWizDocumentListCtrl_SetDocuments2(This,pDisp,bstrSortBy,bstrSortOrder)	\
    ( (This)->lpVtbl -> SetDocuments2(This,pDisp,bstrSortBy,bstrSortOrder) ) 

#define IWizDocumentListCtrl_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IWizDocumentListCtrl_GetDocuments(This,pVal)	\
    ( (This)->lpVtbl -> GetDocuments(This,pVal) ) 

#define IWizDocumentListCtrl_get_OnSelChanged(This,pVal)	\
    ( (This)->lpVtbl -> get_OnSelChanged(This,pVal) ) 

#define IWizDocumentListCtrl_put_OnSelChanged(This,newVal)	\
    ( (This)->lpVtbl -> put_OnSelChanged(This,newVal) ) 

#define IWizDocumentListCtrl_get_OnDblClickItem(This,pVal)	\
    ( (This)->lpVtbl -> get_OnDblClickItem(This,pVal) ) 

#define IWizDocumentListCtrl_put_OnDblClickItem(This,newVal)	\
    ( (This)->lpVtbl -> put_OnDblClickItem(This,newVal) ) 

#define IWizDocumentListCtrl_get_OnExecCommand(This,pVal)	\
    ( (This)->lpVtbl -> get_OnExecCommand(This,pVal) ) 

#define IWizDocumentListCtrl_put_OnExecCommand(This,newVal)	\
    ( (This)->lpVtbl -> put_OnExecCommand(This,newVal) ) 

#define IWizDocumentListCtrl_FocusToSearchBox(This)	\
    ( (This)->lpVtbl -> FocusToSearchBox(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentListCtrl_INTERFACE_DEFINED__ */


#ifndef __IWizDocumentAttachmentListCtrl_INTERFACE_DEFINED__
#define __IWizDocumentAttachmentListCtrl_INTERFACE_DEFINED__

/* interface IWizDocumentAttachmentListCtrl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizDocumentAttachmentListCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("39B2717D-7FDA-4EDD-91A4-0173FD35B871")
    IWizDocumentAttachmentListCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Database( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Database( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Document( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedAttachments( 
            /* [retval][out] */ IDispatch **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelectedAttachments( 
            /* [in] */ IDispatch *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Border( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Border( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Shadow( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Shadow( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnSelChanged( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnSelChanged( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnDblClickItem( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnDblClickItem( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OnExecCommand( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OnExecCommand( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAttachments( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAttachments2( 
            /* [in] */ VARIANT *pvFiles) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizDocumentAttachmentListCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizDocumentAttachmentListCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizDocumentAttachmentListCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Database )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Database )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Document )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Document )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedAttachments )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ IDispatch **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SelectedAttachments )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Border )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Border )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shadow )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Shadow )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnSelChanged )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnSelChanged )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnDblClickItem )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnDblClickItem )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OnExecCommand )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OnExecCommand )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAttachments )( 
            IWizDocumentAttachmentListCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAttachments2 )( 
            IWizDocumentAttachmentListCtrl * This,
            /* [in] */ VARIANT *pvFiles);
        
        END_INTERFACE
    } IWizDocumentAttachmentListCtrlVtbl;

    interface IWizDocumentAttachmentListCtrl
    {
        CONST_VTBL struct IWizDocumentAttachmentListCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizDocumentAttachmentListCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizDocumentAttachmentListCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizDocumentAttachmentListCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizDocumentAttachmentListCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizDocumentAttachmentListCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizDocumentAttachmentListCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizDocumentAttachmentListCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizDocumentAttachmentListCtrl_get_Database(This,pVal)	\
    ( (This)->lpVtbl -> get_Database(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_Database(This,newVal)	\
    ( (This)->lpVtbl -> put_Database(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_Document(This,pVal)	\
    ( (This)->lpVtbl -> get_Document(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_Document(This,newVal)	\
    ( (This)->lpVtbl -> put_Document(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_SelectedAttachments(This,pVal)	\
    ( (This)->lpVtbl -> get_SelectedAttachments(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_SelectedAttachments(This,newVal)	\
    ( (This)->lpVtbl -> put_SelectedAttachments(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_Border(This,pVal)	\
    ( (This)->lpVtbl -> get_Border(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_Border(This,newVal)	\
    ( (This)->lpVtbl -> put_Border(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_Shadow(This,pVal)	\
    ( (This)->lpVtbl -> get_Shadow(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_Shadow(This,newVal)	\
    ( (This)->lpVtbl -> put_Shadow(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_OnSelChanged(This,pVal)	\
    ( (This)->lpVtbl -> get_OnSelChanged(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_OnSelChanged(This,newVal)	\
    ( (This)->lpVtbl -> put_OnSelChanged(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_OnDblClickItem(This,pVal)	\
    ( (This)->lpVtbl -> get_OnDblClickItem(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_OnDblClickItem(This,newVal)	\
    ( (This)->lpVtbl -> put_OnDblClickItem(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_get_OnExecCommand(This,pVal)	\
    ( (This)->lpVtbl -> get_OnExecCommand(This,pVal) ) 

#define IWizDocumentAttachmentListCtrl_put_OnExecCommand(This,newVal)	\
    ( (This)->lpVtbl -> put_OnExecCommand(This,newVal) ) 

#define IWizDocumentAttachmentListCtrl_AddAttachments(This)	\
    ( (This)->lpVtbl -> AddAttachments(This) ) 

#define IWizDocumentAttachmentListCtrl_AddAttachments2(This,pvFiles)	\
    ( (This)->lpVtbl -> AddAttachments2(This,pvFiles) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizDocumentAttachmentListCtrl_INTERFACE_DEFINED__ */


#ifndef __IWizCommonUI_INTERFACE_DEFINED__
#define __IWizCommonUI_INTERFACE_DEFINED__

/* interface IWizCommonUI */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizCommonUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B671315F-B6FE-4799-AE50-AEA0848FBA05")
    IWizCommonUI : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryUserAccount( 
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddDocumentToCalendar( 
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateCalendarEvent( 
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ DATE dtEvent,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EditCalendarEvent( 
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AboutBox( 
            /* [in] */ BSTR bstrModuleName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OptionsDlg( 
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BackupDlg( 
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AccountsManagerDlg( 
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChooseAccount( 
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrDatabasePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIntValue( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIntValue2( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [in] */ LONG nMin,
            /* [in] */ LONG nMax,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckNewVersion( 
            /* [in] */ VARIANT_BOOL vbPrompt,
            /* [in] */ VARIANT_BOOL vbSilent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InputBox( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InputMultiLineText( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWindowsFile( 
            /* [in] */ VARIANT_BOOL vbOpen,
            /* [in] */ BSTR bstrFilter,
            /* [retval][out] */ BSTR *pbstrResultFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWindowsFolder( 
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ BSTR *pbtrFolderPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWizFolder( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppFolderDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWizDocument( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadTextFromFile( 
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveTextToFile( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrText,
            /* [in] */ BSTR bstrCharset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetValueFromIni( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pbstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueToIni( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetATempFileName( 
            /* [in] */ BSTR bstrFileExt,
            /* [retval][out] */ BSTR *pbstrFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSpecialFolder( 
            /* [in] */ BSTR bstrFolderName,
            /* [retval][out] */ BSTR *pbstrPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunExe( 
            /* [in] */ BSTR bstrExeFileName,
            /* [in] */ BSTR bstrParams,
            /* [in] */ VARIANT_BOOL vbWait,
            /* [retval][out] */ long *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumFiles( 
            /* [in] */ BSTR bstrPath,
            /* [in] */ BSTR bstrFileExt,
            /* [in] */ VARIANT_BOOL vbIncludeSubFolders,
            /* [retval][out] */ VARIANT *pvFiles) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumFolders( 
            /* [in] */ BSTR bstrPath,
            /* [retval][out] */ VARIANT *pvFolders) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateActiveXObject( 
            /* [in] */ BSTR bstrProgID,
            /* [retval][out] */ IDispatch **ppObjDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetValueFromReg( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [retval][out] */ BSTR *pbstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetValueToReg( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [in] */ BSTR bstrData,
            /* [in] */ BSTR bstrDataType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumRegValues( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvValueNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumRegKeys( 
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvKeys) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectTemplate( 
            /* [in] */ BSTR bstrTemplateType,
            /* [retval][out] */ BSTR *pbstrResultTemplateFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlTagGetAttributeValue( 
            /* [in] */ BSTR bstrHtmlTag,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [retval][out] */ BSTR *pbstrAttributeValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlExtractTags( 
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [in] */ BSTR bstrTagAttributeValue,
            /* [retval][out] */ VARIANT *pvTags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlEnumLinks( 
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ VARIANT *pvLinks) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlGetContent( 
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrContent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlConvertFileToHtmlFile( 
            /* [in] */ BSTR bstrSrcFileName,
            /* [retval][out] */ BSTR *pbstrHtmlFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HtmlConvertZipFileToHtmlFile( 
            /* [in] */ BSTR bstrSrcZipFileName,
            /* [in] */ BSTR bstrDestHtmlFileName,
            /* [in] */ BSTR bstrHtmlTitle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OptionsDlg2( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectDay( 
            /* [in] */ DATE dtDefault,
            /* [retval][out] */ DATE *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReportSyncResult( 
            /* [in] */ LONGLONG hWnd,
            /* [in] */ VARIANT vDownloaded,
            /* [in] */ VARIANT vUploaded,
            /* [in] */ VARIANT vSkipped,
            /* [in] */ VARIANT vFailed) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyTextToClipboard( 
            /* [in] */ BSTR bstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PromptTrafficLimit( 
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [in] */ LONGLONG nLimit) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AccountSecurityDlg( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitEncryptionDlg( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ImportCertDlg( 
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnterPasswordDlg( 
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrInfo,
            /* [in] */ VARIANT_BOOL vbShowRememberPasswordButton,
            /* [out] */ VARIANT_BOOL *pvbRememberPassword,
            /* [retval][out] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryUserAccount2( 
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClipboardToImage( 
            /* [in] */ OLE_HANDLE hwnd,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CaptureScreen( 
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DumpCHM( 
            /* [in] */ BSTR bstrCHMFileName,
            /* [in] */ BSTR bstrTempPath,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ VARIANT *pvRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HyperlinkDlg( 
            /* [in] */ IDispatch *pdispDatabase,
            /* [in] */ IDispatch *pdispDocument,
            /* [in] */ IDispatch *pdispHtmlDocument,
            /* [in] */ BSTR bstrInitURL,
            /* [retval][out] */ BSTR *pbstrResultURL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectColor( 
            /* [in] */ BSTR bstrInitColor,
            /* [retval][out] */ BSTR *pbstrRetColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFontNames( 
            /* [retval][out] */ VARIANT *pvNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFont( 
            /* [in] */ BSTR bstrInit,
            /* [retval][out] */ BSTR *pbstrRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateWizObject( 
            /* [in] */ BSTR bstrObjectName,
            /* [retval][out] */ IDispatch **ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetScriptParamValue( 
            /* [in] */ BSTR bstrParamName,
            /* [retval][out] */ BSTR *pbstrVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadStringFromFile( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrStringName,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE URLDownloadToText( 
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectWizTags( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ IDispatch **ppTagCollectionDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CalendarDlg( 
            /* [in] */ LONG nFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizCommonUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizCommonUI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizCommonUI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizCommonUI * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizCommonUI * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizCommonUI * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizCommonUI * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizCommonUI * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryUserAccount )( 
            IWizCommonUI * This,
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddDocumentToCalendar )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateCalendarEvent )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ DATE dtEvent,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EditCalendarEvent )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDocumentDisp,
            /* [retval][out] */ VARIANT_BOOL *pbRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AboutBox )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrModuleName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OptionsDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BackupDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AccountsManagerDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChooseAccount )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ BSTR *pbstrDatabasePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIntValue )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIntValue2 )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ LONG nInitValue,
            /* [in] */ LONG nMin,
            /* [in] */ LONG nMax,
            /* [out] */ VARIANT_BOOL *pvbOK,
            /* [retval][out] */ LONG *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckNewVersion )( 
            IWizCommonUI * This,
            /* [in] */ VARIANT_BOOL vbPrompt,
            /* [in] */ VARIANT_BOOL vbSilent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InputBox )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InputMultiLineText )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrInitValue,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWindowsFile )( 
            IWizCommonUI * This,
            /* [in] */ VARIANT_BOOL vbOpen,
            /* [in] */ BSTR bstrFilter,
            /* [retval][out] */ BSTR *pbstrResultFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWindowsFolder )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ BSTR *pbtrFolderPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWizFolder )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppFolderDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWizDocument )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrDescription,
            /* [retval][out] */ IDispatch **ppDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadTextFromFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveTextToFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrText,
            /* [in] */ BSTR bstrCharset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetValueFromIni )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ BSTR *pbstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueToIni )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrSection,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetATempFileName )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileExt,
            /* [retval][out] */ BSTR *pbstrFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSpecialFolder )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFolderName,
            /* [retval][out] */ BSTR *pbstrPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RunExe )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrExeFileName,
            /* [in] */ BSTR bstrParams,
            /* [in] */ VARIANT_BOOL vbWait,
            /* [retval][out] */ long *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumFiles )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrPath,
            /* [in] */ BSTR bstrFileExt,
            /* [in] */ VARIANT_BOOL vbIncludeSubFolders,
            /* [retval][out] */ VARIANT *pvFiles);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumFolders )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrPath,
            /* [retval][out] */ VARIANT *pvFolders);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateActiveXObject )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrProgID,
            /* [retval][out] */ IDispatch **ppObjDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetValueFromReg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [retval][out] */ BSTR *pbstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetValueToReg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [in] */ BSTR bstrValueName,
            /* [in] */ BSTR bstrData,
            /* [in] */ BSTR bstrDataType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumRegValues )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvValueNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumRegKeys )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrRoot,
            /* [in] */ BSTR bstrKey,
            /* [retval][out] */ VARIANT *pvKeys);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectTemplate )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTemplateType,
            /* [retval][out] */ BSTR *pbstrResultTemplateFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlTagGetAttributeValue )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlTag,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [retval][out] */ BSTR *pbstrAttributeValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlExtractTags )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrTagName,
            /* [in] */ BSTR bstrTagAttributeName,
            /* [in] */ BSTR bstrTagAttributeValue,
            /* [retval][out] */ VARIANT *pvTags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlEnumLinks )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ VARIANT *pvLinks);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlGetContent )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrHtmlText,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrContent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlConvertFileToHtmlFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrSrcFileName,
            /* [retval][out] */ BSTR *pbstrHtmlFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HtmlConvertZipFileToHtmlFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrSrcZipFileName,
            /* [in] */ BSTR bstrDestHtmlFileName,
            /* [in] */ BSTR bstrHtmlTitle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OptionsDlg2 )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectDay )( 
            IWizCommonUI * This,
            /* [in] */ DATE dtDefault,
            /* [retval][out] */ DATE *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReportSyncResult )( 
            IWizCommonUI * This,
            /* [in] */ LONGLONG hWnd,
            /* [in] */ VARIANT vDownloaded,
            /* [in] */ VARIANT vUploaded,
            /* [in] */ VARIANT vSkipped,
            /* [in] */ VARIANT vFailed);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CopyTextToClipboard )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PromptTrafficLimit )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [in] */ LONGLONG nLimit);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AccountSecurityDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitEncryptionDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ImportCertDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDisp,
            /* [in] */ LONG nFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnterPasswordDlg )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrInfo,
            /* [in] */ VARIANT_BOOL vbShowRememberPasswordButton,
            /* [out] */ VARIANT_BOOL *pvbRememberPassword,
            /* [retval][out] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QueryUserAccount2 )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pDatabaseDisp,
            /* [in] */ LONGLONG hWnd,
            /* [out][in] */ BSTR *pbstrUserName,
            /* [out][in] */ BSTR *pbstrPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClipboardToImage )( 
            IWizCommonUI * This,
            /* [in] */ OLE_HANDLE hwnd,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CaptureScreen )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ BSTR *pbstrImageFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DumpCHM )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrCHMFileName,
            /* [in] */ BSTR bstrTempPath,
            /* [in] */ BSTR bstrOptions,
            /* [retval][out] */ VARIANT *pvRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HyperlinkDlg )( 
            IWizCommonUI * This,
            /* [in] */ IDispatch *pdispDatabase,
            /* [in] */ IDispatch *pdispDocument,
            /* [in] */ IDispatch *pdispHtmlDocument,
            /* [in] */ BSTR bstrInitURL,
            /* [retval][out] */ BSTR *pbstrResultURL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectColor )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrInitColor,
            /* [retval][out] */ BSTR *pbstrRetColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFontNames )( 
            IWizCommonUI * This,
            /* [retval][out] */ VARIANT *pvNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFont )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrInit,
            /* [retval][out] */ BSTR *pbstrRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateWizObject )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrObjectName,
            /* [retval][out] */ IDispatch **ppVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetScriptParamValue )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrParamName,
            /* [retval][out] */ BSTR *pbstrVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadStringFromFile )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrStringName,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *URLDownloadToText )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrURL,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectWizTags )( 
            IWizCommonUI * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nFlags,
            /* [retval][out] */ IDispatch **ppTagCollectionDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CalendarDlg )( 
            IWizCommonUI * This,
            /* [in] */ LONG nFlags);
        
        END_INTERFACE
    } IWizCommonUIVtbl;

    interface IWizCommonUI
    {
        CONST_VTBL struct IWizCommonUIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizCommonUI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizCommonUI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizCommonUI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizCommonUI_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizCommonUI_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizCommonUI_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizCommonUI_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizCommonUI_QueryUserAccount(This,hWnd,pbstrUserName,pbstrPassword)	\
    ( (This)->lpVtbl -> QueryUserAccount(This,hWnd,pbstrUserName,pbstrPassword) ) 

#define IWizCommonUI_AddDocumentToCalendar(This,pDocumentDisp,pbRet)	\
    ( (This)->lpVtbl -> AddDocumentToCalendar(This,pDocumentDisp,pbRet) ) 

#define IWizCommonUI_CreateCalendarEvent(This,pDatabaseDisp,dtEvent,ppDocumentDisp)	\
    ( (This)->lpVtbl -> CreateCalendarEvent(This,pDatabaseDisp,dtEvent,ppDocumentDisp) ) 

#define IWizCommonUI_EditCalendarEvent(This,pDocumentDisp,pbRet)	\
    ( (This)->lpVtbl -> EditCalendarEvent(This,pDocumentDisp,pbRet) ) 

#define IWizCommonUI_AboutBox(This,bstrModuleName)	\
    ( (This)->lpVtbl -> AboutBox(This,bstrModuleName) ) 

#define IWizCommonUI_OptionsDlg(This,nFlags)	\
    ( (This)->lpVtbl -> OptionsDlg(This,nFlags) ) 

#define IWizCommonUI_BackupDlg(This,nFlags)	\
    ( (This)->lpVtbl -> BackupDlg(This,nFlags) ) 

#define IWizCommonUI_AccountsManagerDlg(This,nFlags)	\
    ( (This)->lpVtbl -> AccountsManagerDlg(This,nFlags) ) 

#define IWizCommonUI_ChooseAccount(This,nFlags,pbstrDatabasePath)	\
    ( (This)->lpVtbl -> ChooseAccount(This,nFlags,pbstrDatabasePath) ) 

#define IWizCommonUI_GetIntValue(This,bstrTitle,bstrDescription,nInitValue,pvbOK,pnRet)	\
    ( (This)->lpVtbl -> GetIntValue(This,bstrTitle,bstrDescription,nInitValue,pvbOK,pnRet) ) 

#define IWizCommonUI_GetIntValue2(This,bstrTitle,bstrDescription,nInitValue,nMin,nMax,pvbOK,pnRet)	\
    ( (This)->lpVtbl -> GetIntValue2(This,bstrTitle,bstrDescription,nInitValue,nMin,nMax,pvbOK,pnRet) ) 

#define IWizCommonUI_CheckNewVersion(This,vbPrompt,vbSilent)	\
    ( (This)->lpVtbl -> CheckNewVersion(This,vbPrompt,vbSilent) ) 

#define IWizCommonUI_InputBox(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText)	\
    ( (This)->lpVtbl -> InputBox(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText) ) 

#define IWizCommonUI_InputMultiLineText(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText)	\
    ( (This)->lpVtbl -> InputMultiLineText(This,bstrTitle,bstrDescription,bstrInitValue,pbstrText) ) 

#define IWizCommonUI_SelectWindowsFile(This,vbOpen,bstrFilter,pbstrResultFileName)	\
    ( (This)->lpVtbl -> SelectWindowsFile(This,vbOpen,bstrFilter,pbstrResultFileName) ) 

#define IWizCommonUI_SelectWindowsFolder(This,bstrDescription,pbtrFolderPath)	\
    ( (This)->lpVtbl -> SelectWindowsFolder(This,bstrDescription,pbtrFolderPath) ) 

#define IWizCommonUI_SelectWizFolder(This,bstrDatabasePath,bstrDescription,ppFolderDisp)	\
    ( (This)->lpVtbl -> SelectWizFolder(This,bstrDatabasePath,bstrDescription,ppFolderDisp) ) 

#define IWizCommonUI_SelectWizDocument(This,bstrDatabasePath,bstrDescription,ppDocumentDisp)	\
    ( (This)->lpVtbl -> SelectWizDocument(This,bstrDatabasePath,bstrDescription,ppDocumentDisp) ) 

#define IWizCommonUI_LoadTextFromFile(This,bstrFileName,pbstrText)	\
    ( (This)->lpVtbl -> LoadTextFromFile(This,bstrFileName,pbstrText) ) 

#define IWizCommonUI_SaveTextToFile(This,bstrFileName,bstrText,bstrCharset)	\
    ( (This)->lpVtbl -> SaveTextToFile(This,bstrFileName,bstrText,bstrCharset) ) 

#define IWizCommonUI_GetValueFromIni(This,bstrFileName,bstrSection,bstrKey,pbstrValue)	\
    ( (This)->lpVtbl -> GetValueFromIni(This,bstrFileName,bstrSection,bstrKey,pbstrValue) ) 

#define IWizCommonUI_SetValueToIni(This,bstrFileName,bstrSection,bstrKey,bstrValue)	\
    ( (This)->lpVtbl -> SetValueToIni(This,bstrFileName,bstrSection,bstrKey,bstrValue) ) 

#define IWizCommonUI_GetATempFileName(This,bstrFileExt,pbstrFileName)	\
    ( (This)->lpVtbl -> GetATempFileName(This,bstrFileExt,pbstrFileName) ) 

#define IWizCommonUI_GetSpecialFolder(This,bstrFolderName,pbstrPath)	\
    ( (This)->lpVtbl -> GetSpecialFolder(This,bstrFolderName,pbstrPath) ) 

#define IWizCommonUI_RunExe(This,bstrExeFileName,bstrParams,vbWait,pnRet)	\
    ( (This)->lpVtbl -> RunExe(This,bstrExeFileName,bstrParams,vbWait,pnRet) ) 

#define IWizCommonUI_EnumFiles(This,bstrPath,bstrFileExt,vbIncludeSubFolders,pvFiles)	\
    ( (This)->lpVtbl -> EnumFiles(This,bstrPath,bstrFileExt,vbIncludeSubFolders,pvFiles) ) 

#define IWizCommonUI_EnumFolders(This,bstrPath,pvFolders)	\
    ( (This)->lpVtbl -> EnumFolders(This,bstrPath,pvFolders) ) 

#define IWizCommonUI_CreateActiveXObject(This,bstrProgID,ppObjDisp)	\
    ( (This)->lpVtbl -> CreateActiveXObject(This,bstrProgID,ppObjDisp) ) 

#define IWizCommonUI_GetValueFromReg(This,bstrRoot,bstrKey,bstrValueName,pbstrData)	\
    ( (This)->lpVtbl -> GetValueFromReg(This,bstrRoot,bstrKey,bstrValueName,pbstrData) ) 

#define IWizCommonUI_SetValueToReg(This,bstrRoot,bstrKey,bstrValueName,bstrData,bstrDataType)	\
    ( (This)->lpVtbl -> SetValueToReg(This,bstrRoot,bstrKey,bstrValueName,bstrData,bstrDataType) ) 

#define IWizCommonUI_EnumRegValues(This,bstrRoot,bstrKey,pvValueNames)	\
    ( (This)->lpVtbl -> EnumRegValues(This,bstrRoot,bstrKey,pvValueNames) ) 

#define IWizCommonUI_EnumRegKeys(This,bstrRoot,bstrKey,pvKeys)	\
    ( (This)->lpVtbl -> EnumRegKeys(This,bstrRoot,bstrKey,pvKeys) ) 

#define IWizCommonUI_SelectTemplate(This,bstrTemplateType,pbstrResultTemplateFileName)	\
    ( (This)->lpVtbl -> SelectTemplate(This,bstrTemplateType,pbstrResultTemplateFileName) ) 

#define IWizCommonUI_HtmlTagGetAttributeValue(This,bstrHtmlTag,bstrTagAttributeName,pbstrAttributeValue)	\
    ( (This)->lpVtbl -> HtmlTagGetAttributeValue(This,bstrHtmlTag,bstrTagAttributeName,pbstrAttributeValue) ) 

#define IWizCommonUI_HtmlExtractTags(This,bstrHtmlText,bstrTagName,bstrTagAttributeName,bstrTagAttributeValue,pvTags)	\
    ( (This)->lpVtbl -> HtmlExtractTags(This,bstrHtmlText,bstrTagName,bstrTagAttributeName,bstrTagAttributeValue,pvTags) ) 

#define IWizCommonUI_HtmlEnumLinks(This,bstrHtmlText,bstrURL,pvLinks)	\
    ( (This)->lpVtbl -> HtmlEnumLinks(This,bstrHtmlText,bstrURL,pvLinks) ) 

#define IWizCommonUI_HtmlGetContent(This,bstrHtmlText,bstrURL,pbstrContent)	\
    ( (This)->lpVtbl -> HtmlGetContent(This,bstrHtmlText,bstrURL,pbstrContent) ) 

#define IWizCommonUI_HtmlConvertFileToHtmlFile(This,bstrSrcFileName,pbstrHtmlFileName)	\
    ( (This)->lpVtbl -> HtmlConvertFileToHtmlFile(This,bstrSrcFileName,pbstrHtmlFileName) ) 

#define IWizCommonUI_HtmlConvertZipFileToHtmlFile(This,bstrSrcZipFileName,bstrDestHtmlFileName,bstrHtmlTitle)	\
    ( (This)->lpVtbl -> HtmlConvertZipFileToHtmlFile(This,bstrSrcZipFileName,bstrDestHtmlFileName,bstrHtmlTitle) ) 

#define IWizCommonUI_OptionsDlg2(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> OptionsDlg2(This,pDisp,nFlags) ) 

#define IWizCommonUI_SelectDay(This,dtDefault,pRet)	\
    ( (This)->lpVtbl -> SelectDay(This,dtDefault,pRet) ) 

#define IWizCommonUI_ReportSyncResult(This,hWnd,vDownloaded,vUploaded,vSkipped,vFailed)	\
    ( (This)->lpVtbl -> ReportSyncResult(This,hWnd,vDownloaded,vUploaded,vSkipped,vFailed) ) 

#define IWizCommonUI_CopyTextToClipboard(This,bstrText)	\
    ( (This)->lpVtbl -> CopyTextToClipboard(This,bstrText) ) 

#define IWizCommonUI_PromptTrafficLimit(This,pDatabaseDisp,hWnd,nLimit)	\
    ( (This)->lpVtbl -> PromptTrafficLimit(This,pDatabaseDisp,hWnd,nLimit) ) 

#define IWizCommonUI_AccountSecurityDlg(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> AccountSecurityDlg(This,pDisp,nFlags) ) 

#define IWizCommonUI_InitEncryptionDlg(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> InitEncryptionDlg(This,pDisp,nFlags) ) 

#define IWizCommonUI_ImportCertDlg(This,pDisp,nFlags)	\
    ( (This)->lpVtbl -> ImportCertDlg(This,pDisp,nFlags) ) 

#define IWizCommonUI_EnterPasswordDlg(This,bstrTitle,bstrInfo,vbShowRememberPasswordButton,pvbRememberPassword,pbstrPassword)	\
    ( (This)->lpVtbl -> EnterPasswordDlg(This,bstrTitle,bstrInfo,vbShowRememberPasswordButton,pvbRememberPassword,pbstrPassword) ) 

#define IWizCommonUI_QueryUserAccount2(This,pDatabaseDisp,hWnd,pbstrUserName,pbstrPassword)	\
    ( (This)->lpVtbl -> QueryUserAccount2(This,pDatabaseDisp,hWnd,pbstrUserName,pbstrPassword) ) 

#define IWizCommonUI_ClipboardToImage(This,hwnd,bstrOptions,pbstrImageFileName)	\
    ( (This)->lpVtbl -> ClipboardToImage(This,hwnd,bstrOptions,pbstrImageFileName) ) 

#define IWizCommonUI_CaptureScreen(This,bstrOptions,pbstrImageFileName)	\
    ( (This)->lpVtbl -> CaptureScreen(This,bstrOptions,pbstrImageFileName) ) 

#define IWizCommonUI_DumpCHM(This,bstrCHMFileName,bstrTempPath,bstrOptions,pvRet)	\
    ( (This)->lpVtbl -> DumpCHM(This,bstrCHMFileName,bstrTempPath,bstrOptions,pvRet) ) 

#define IWizCommonUI_HyperlinkDlg(This,pdispDatabase,pdispDocument,pdispHtmlDocument,bstrInitURL,pbstrResultURL)	\
    ( (This)->lpVtbl -> HyperlinkDlg(This,pdispDatabase,pdispDocument,pdispHtmlDocument,bstrInitURL,pbstrResultURL) ) 

#define IWizCommonUI_SelectColor(This,bstrInitColor,pbstrRetColor)	\
    ( (This)->lpVtbl -> SelectColor(This,bstrInitColor,pbstrRetColor) ) 

#define IWizCommonUI_GetFontNames(This,pvNames)	\
    ( (This)->lpVtbl -> GetFontNames(This,pvNames) ) 

#define IWizCommonUI_SelectFont(This,bstrInit,pbstrRet)	\
    ( (This)->lpVtbl -> SelectFont(This,bstrInit,pbstrRet) ) 

#define IWizCommonUI_CreateWizObject(This,bstrObjectName,ppVal)	\
    ( (This)->lpVtbl -> CreateWizObject(This,bstrObjectName,ppVal) ) 

#define IWizCommonUI_GetScriptParamValue(This,bstrParamName,pbstrVal)	\
    ( (This)->lpVtbl -> GetScriptParamValue(This,bstrParamName,pbstrVal) ) 

#define IWizCommonUI_LoadStringFromFile(This,bstrFileName,bstrStringName,pVal)	\
    ( (This)->lpVtbl -> LoadStringFromFile(This,bstrFileName,bstrStringName,pVal) ) 

#define IWizCommonUI_URLDownloadToText(This,bstrURL,pbstrText)	\
    ( (This)->lpVtbl -> URLDownloadToText(This,bstrURL,pbstrText) ) 

#define IWizCommonUI_SelectWizTags(This,bstrDatabasePath,bstrTitle,nFlags,ppTagCollectionDisp)	\
    ( (This)->lpVtbl -> SelectWizTags(This,bstrDatabasePath,bstrTitle,nFlags,ppTagCollectionDisp) ) 

#define IWizCommonUI_CalendarDlg(This,nFlags)	\
    ( (This)->lpVtbl -> CalendarDlg(This,nFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizCommonUI_INTERFACE_DEFINED__ */


#ifndef __IWizBatchDownloader_INTERFACE_DEFINED__
#define __IWizBatchDownloader_INTERFACE_DEFINED__

/* interface IWizBatchDownloader */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizBatchDownloader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49C2236A-6DA1-4AA9-BAD7-BF0DA94535A4")
    IWizBatchDownloader : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJob( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbLinkTextAsTitle,
            /* [in] */ VARIANT_BOOL vbExecuteScript) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJobsFromTextFile( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrTextFileName,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbExecuteScript) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowWindow( 
            VARIANT_BOOL vbStartDownload) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CombineDocuments( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CombineDocuments( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJob2( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddJob3( 
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrOverwriteDocumentGUID,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizBatchDownloaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizBatchDownloader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizBatchDownloader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizBatchDownloader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizBatchDownloader * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizBatchDownloader * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizBatchDownloader * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizBatchDownloader * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJob )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbLinkTextAsTitle,
            /* [in] */ VARIANT_BOOL vbExecuteScript);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJobsFromTextFile )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrTextFileName,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ VARIANT_BOOL vbExecuteScript);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowWindow )( 
            IWizBatchDownloader * This,
            VARIANT_BOOL vbStartDownload);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CombineDocuments )( 
            IWizBatchDownloader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CombineDocuments )( 
            IWizBatchDownloader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJob2 )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrLocation,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrLinkText,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddJob3 )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR bstrDatabasePath,
            /* [in] */ BSTR bstrOverwriteDocumentGUID,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ LONG nUpdateDocumentFlags,
            /* [in] */ LONG nJobFlags);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IWizBatchDownloader * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IWizBatchDownloader * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IWizBatchDownloaderVtbl;

    interface IWizBatchDownloader
    {
        CONST_VTBL struct IWizBatchDownloaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizBatchDownloader_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizBatchDownloader_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizBatchDownloader_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizBatchDownloader_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizBatchDownloader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizBatchDownloader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizBatchDownloader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizBatchDownloader_AddJob(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,vbLinkTextAsTitle,vbExecuteScript)	\
    ( (This)->lpVtbl -> AddJob(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,vbLinkTextAsTitle,vbExecuteScript) ) 

#define IWizBatchDownloader_AddJobsFromTextFile(This,bstrDatabasePath,bstrLocation,bstrTextFileName,nUpdateDocumentFlags,vbExecuteScript)	\
    ( (This)->lpVtbl -> AddJobsFromTextFile(This,bstrDatabasePath,bstrLocation,bstrTextFileName,nUpdateDocumentFlags,vbExecuteScript) ) 

#define IWizBatchDownloader_ShowWindow(This,vbStartDownload)	\
    ( (This)->lpVtbl -> ShowWindow(This,vbStartDownload) ) 

#define IWizBatchDownloader_get_CombineDocuments(This,pVal)	\
    ( (This)->lpVtbl -> get_CombineDocuments(This,pVal) ) 

#define IWizBatchDownloader_put_CombineDocuments(This,newVal)	\
    ( (This)->lpVtbl -> put_CombineDocuments(This,newVal) ) 

#define IWizBatchDownloader_AddJob2(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,nJobFlags)	\
    ( (This)->lpVtbl -> AddJob2(This,bstrDatabasePath,bstrLocation,bstrURL,bstrLinkText,nUpdateDocumentFlags,nJobFlags) ) 

#define IWizBatchDownloader_AddJob3(This,bstrDatabasePath,bstrOverwriteDocumentGUID,bstrURL,bstrTitle,nUpdateDocumentFlags,nJobFlags)	\
    ( (This)->lpVtbl -> AddJob3(This,bstrDatabasePath,bstrOverwriteDocumentGUID,bstrURL,bstrTitle,nUpdateDocumentFlags,nJobFlags) ) 

#define IWizBatchDownloader_get_Title(This,pVal)	\
    ( (This)->lpVtbl -> get_Title(This,pVal) ) 

#define IWizBatchDownloader_put_Title(This,newVal)	\
    ( (This)->lpVtbl -> put_Title(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizBatchDownloader_INTERFACE_DEFINED__ */


#ifndef __IWizProgressWindow_INTERFACE_DEFINED__
#define __IWizProgressWindow_INTERFACE_DEFINED__

/* interface IWizProgressWindow */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizProgressWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF5BCE34-5FC1-4337-80D3-87747643CB15")
    IWizProgressWindow : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Max( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Max( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Pos( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Pos( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Show( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Destroy( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetParent( 
            /* [in] */ OLE_HANDLE hwnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizProgressWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizProgressWindow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizProgressWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizProgressWindow * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizProgressWindow * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizProgressWindow * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizProgressWindow * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizProgressWindow * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Title )( 
            IWizProgressWindow * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Title )( 
            IWizProgressWindow * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Max )( 
            IWizProgressWindow * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Max )( 
            IWizProgressWindow * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Pos )( 
            IWizProgressWindow * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Pos )( 
            IWizProgressWindow * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            IWizProgressWindow * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            IWizProgressWindow * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IWizProgressWindow * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hide )( 
            IWizProgressWindow * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Destroy )( 
            IWizProgressWindow * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetParent )( 
            IWizProgressWindow * This,
            /* [in] */ OLE_HANDLE hwnd);
        
        END_INTERFACE
    } IWizProgressWindowVtbl;

    interface IWizProgressWindow
    {
        CONST_VTBL struct IWizProgressWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizProgressWindow_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizProgressWindow_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizProgressWindow_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizProgressWindow_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizProgressWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizProgressWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizProgressWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizProgressWindow_get_Title(This,pVal)	\
    ( (This)->lpVtbl -> get_Title(This,pVal) ) 

#define IWizProgressWindow_put_Title(This,newVal)	\
    ( (This)->lpVtbl -> put_Title(This,newVal) ) 

#define IWizProgressWindow_get_Max(This,pVal)	\
    ( (This)->lpVtbl -> get_Max(This,pVal) ) 

#define IWizProgressWindow_put_Max(This,newVal)	\
    ( (This)->lpVtbl -> put_Max(This,newVal) ) 

#define IWizProgressWindow_get_Pos(This,pVal)	\
    ( (This)->lpVtbl -> get_Pos(This,pVal) ) 

#define IWizProgressWindow_put_Pos(This,newVal)	\
    ( (This)->lpVtbl -> put_Pos(This,newVal) ) 

#define IWizProgressWindow_get_Text(This,pVal)	\
    ( (This)->lpVtbl -> get_Text(This,pVal) ) 

#define IWizProgressWindow_put_Text(This,newVal)	\
    ( (This)->lpVtbl -> put_Text(This,newVal) ) 

#define IWizProgressWindow_Show(This)	\
    ( (This)->lpVtbl -> Show(This) ) 

#define IWizProgressWindow_Hide(This)	\
    ( (This)->lpVtbl -> Hide(This) ) 

#define IWizProgressWindow_Destroy(This)	\
    ( (This)->lpVtbl -> Destroy(This) ) 

#define IWizProgressWindow_SetParent(This,hwnd)	\
    ( (This)->lpVtbl -> SetParent(This,hwnd) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizProgressWindow_INTERFACE_DEFINED__ */


#ifndef __IWizSyncProgressDlg_INTERFACE_DEFINED__
#define __IWizSyncProgressDlg_INTERFACE_DEFINED__

/* interface IWizSyncProgressDlg */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizSyncProgressDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("476F255C-8032-42A4-AA36-4EBB25C36BAB")
    IWizSyncProgressDlg : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Show( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hide( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDatabasePath( 
            /* [in] */ BSTR bstrDatabasePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AutoShow( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Background( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Background( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizSyncProgressDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizSyncProgressDlg * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizSyncProgressDlg * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizSyncProgressDlg * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizSyncProgressDlg * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizSyncProgressDlg * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizSyncProgressDlg * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizSyncProgressDlg * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hide )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDatabasePath )( 
            IWizSyncProgressDlg * This,
            /* [in] */ BSTR bstrDatabasePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AutoShow )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IWizSyncProgressDlg * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Background )( 
            IWizSyncProgressDlg * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Background )( 
            IWizSyncProgressDlg * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IWizSyncProgressDlgVtbl;

    interface IWizSyncProgressDlg
    {
        CONST_VTBL struct IWizSyncProgressDlgVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizSyncProgressDlg_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizSyncProgressDlg_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizSyncProgressDlg_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizSyncProgressDlg_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizSyncProgressDlg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizSyncProgressDlg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizSyncProgressDlg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizSyncProgressDlg_Show(This)	\
    ( (This)->lpVtbl -> Show(This) ) 

#define IWizSyncProgressDlg_Hide(This)	\
    ( (This)->lpVtbl -> Hide(This) ) 

#define IWizSyncProgressDlg_SetDatabasePath(This,bstrDatabasePath)	\
    ( (This)->lpVtbl -> SetDatabasePath(This,bstrDatabasePath) ) 

#define IWizSyncProgressDlg_AutoShow(This)	\
    ( (This)->lpVtbl -> AutoShow(This) ) 

#define IWizSyncProgressDlg_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IWizSyncProgressDlg_get_Background(This,pVal)	\
    ( (This)->lpVtbl -> get_Background(This,pVal) ) 

#define IWizSyncProgressDlg_put_Background(This,newVal)	\
    ( (This)->lpVtbl -> put_Background(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizSyncProgressDlg_INTERFACE_DEFINED__ */



#ifndef __WizKMControlsLib_LIBRARY_DEFINED__
#define __WizKMControlsLib_LIBRARY_DEFINED__

/* library WizKMControlsLib */
/* [helpstring][version][uuid] */ 


enum WizBatchDownloaderJobFlags
    {	wizWizBatchDownloaderJobLinkTextAsTitle	= 0x1,
	wizWizBatchDownloaderJobExecuteScript	= 0x2,
	wizWizBatchDownloaderJobURLAsCustomID	= 0x4
    } ;

enum WizFolderTreeCtrlFlags
    {	wizFolderTreeCtrlEnableNewDocument	= 0x1,
	wizFolderTreeCtrlIncludeSubFolders	= 0x2
    } ;

enum WizTagTreeCtrlFlags
    {	wizTagTreeCtrlIncludeSubFolders	= 0x2
    } ;

enum WizCommandID
    {	wizCommandSelectPrevDocument	= 0x1,
	wizCommandSelectNextDocument	= 0x2
    } ;

EXTERN_C const IID LIBID_WizKMControlsLib;

#ifndef ___IWizFolderTreeCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IWizFolderTreeCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWizFolderTreeCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWizFolderTreeCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C6A08167-A326-40C6-9BF3-529F07206E93")
    _IWizFolderTreeCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWizFolderTreeCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWizFolderTreeCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWizFolderTreeCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWizFolderTreeCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWizFolderTreeCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWizFolderTreeCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWizFolderTreeCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWizFolderTreeCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWizFolderTreeCtrlEventsVtbl;

    interface _IWizFolderTreeCtrlEvents
    {
        CONST_VTBL struct _IWizFolderTreeCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWizFolderTreeCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWizFolderTreeCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWizFolderTreeCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWizFolderTreeCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWizFolderTreeCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWizFolderTreeCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWizFolderTreeCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWizFolderTreeCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WizFolderTreeCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("26C7C9DF-8814-4FB5-925A-C720E75C924A")
WizFolderTreeCtrl;
#endif

#ifndef ___IWizStyleListBoxEvents_DISPINTERFACE_DEFINED__
#define ___IWizStyleListBoxEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWizStyleListBoxEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWizStyleListBoxEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("94B0B237-5327-454F-8DB7-EB767BCFD2CC")
    _IWizStyleListBoxEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWizStyleListBoxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWizStyleListBoxEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWizStyleListBoxEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWizStyleListBoxEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWizStyleListBoxEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWizStyleListBoxEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWizStyleListBoxEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWizStyleListBoxEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWizStyleListBoxEventsVtbl;

    interface _IWizStyleListBoxEvents
    {
        CONST_VTBL struct _IWizStyleListBoxEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWizStyleListBoxEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWizStyleListBoxEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWizStyleListBoxEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWizStyleListBoxEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWizStyleListBoxEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWizStyleListBoxEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWizStyleListBoxEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWizStyleListBoxEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WizStyleListBox;

#ifdef __cplusplus

class DECLSPEC_UUID("45654514-333B-4E1F-A82F-B5A770B51DF2")
WizStyleListBox;
#endif

#ifndef ___IWizTagTreeCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IWizTagTreeCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWizTagTreeCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWizTagTreeCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B9344735-5486-4FF9-BDFA-5CDCD30122AD")
    _IWizTagTreeCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWizTagTreeCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWizTagTreeCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWizTagTreeCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWizTagTreeCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWizTagTreeCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWizTagTreeCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWizTagTreeCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWizTagTreeCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWizTagTreeCtrlEventsVtbl;

    interface _IWizTagTreeCtrlEvents
    {
        CONST_VTBL struct _IWizTagTreeCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWizTagTreeCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWizTagTreeCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWizTagTreeCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWizTagTreeCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWizTagTreeCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWizTagTreeCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWizTagTreeCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWizTagTreeCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WizTagTreeCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("2ECF9CCC-A138-4940-A8FB-06509F8A1D09")
WizTagTreeCtrl;
#endif

#ifndef ___IWizDocumentListCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IWizDocumentListCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWizDocumentListCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWizDocumentListCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6F374E41-29D7-426A-8F9D-995E3DA812CA")
    _IWizDocumentListCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWizDocumentListCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWizDocumentListCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWizDocumentListCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWizDocumentListCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWizDocumentListCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWizDocumentListCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWizDocumentListCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWizDocumentListCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWizDocumentListCtrlEventsVtbl;

    interface _IWizDocumentListCtrlEvents
    {
        CONST_VTBL struct _IWizDocumentListCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWizDocumentListCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWizDocumentListCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWizDocumentListCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWizDocumentListCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWizDocumentListCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWizDocumentListCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWizDocumentListCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWizDocumentListCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WizDocumentListCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("D30F2928-D136-4F2D-98C4-080E3CB1C92C")
WizDocumentListCtrl;
#endif

#ifndef ___IWizDocumentAttachmentListCtrlEvents_DISPINTERFACE_DEFINED__
#define ___IWizDocumentAttachmentListCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWizDocumentAttachmentListCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWizDocumentAttachmentListCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B752B564-DA68-4F9F-894F-556F641C4FCE")
    _IWizDocumentAttachmentListCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWizDocumentAttachmentListCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWizDocumentAttachmentListCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWizDocumentAttachmentListCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWizDocumentAttachmentListCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWizDocumentAttachmentListCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWizDocumentAttachmentListCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWizDocumentAttachmentListCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWizDocumentAttachmentListCtrlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWizDocumentAttachmentListCtrlEventsVtbl;

    interface _IWizDocumentAttachmentListCtrlEvents
    {
        CONST_VTBL struct _IWizDocumentAttachmentListCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWizDocumentAttachmentListCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWizDocumentAttachmentListCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWizDocumentAttachmentListCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWizDocumentAttachmentListCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWizDocumentAttachmentListCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWizDocumentAttachmentListCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWizDocumentAttachmentListCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWizDocumentAttachmentListCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WizDocumentAttachmentListCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("A74098CA-0E98-40D6-92BF-06AAAE1B2EB8")
WizDocumentAttachmentListCtrl;
#endif

EXTERN_C const CLSID CLSID_WizCommonUI;

#ifdef __cplusplus

class DECLSPEC_UUID("5EABDAD8-A056-4445-AC98-E66885B0935F")
WizCommonUI;
#endif

EXTERN_C const CLSID CLSID_WizBatchDownloader;

#ifdef __cplusplus

class DECLSPEC_UUID("8C43A23A-11CD-4BFA-A3FA-CBC4A586F666")
WizBatchDownloader;
#endif

EXTERN_C const CLSID CLSID_WizProgressWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("E132C3B7-DA0C-4946-9332-D3D1822FC52C")
WizProgressWindow;
#endif

EXTERN_C const CLSID CLSID_WizSyncProgressDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("CDEF75C2-9494-4336-AF33-66980EB65E29")
WizSyncProgressDlg;
#endif
#endif /* __WizKMControlsLib_LIBRARY_DEFINED__ */

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


