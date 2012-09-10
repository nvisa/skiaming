

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sat May 28 10:12:46 2011
 */
/* Compiler settings for .\WizWebCapture.idl:
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

#ifndef __WizWebCapture_i_h__
#define __WizWebCapture_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWizIECapture_FWD_DEFINED__
#define __IWizIECapture_FWD_DEFINED__
typedef interface IWizIECapture IWizIECapture;
#endif 	/* __IWizIECapture_FWD_DEFINED__ */


#ifndef __WizIECapture_FWD_DEFINED__
#define __WizIECapture_FWD_DEFINED__

#ifdef __cplusplus
typedef class WizIECapture WizIECapture;
#else
typedef struct WizIECapture WizIECapture;
#endif /* __cplusplus */

#endif 	/* __WizIECapture_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWizIECapture_INTERFACE_DEFINED__
#define __IWizIECapture_INTERFACE_DEFINED__

/* interface IWizIECapture */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWizIECapture;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("502644EE-7301-457B-A77D-8BC3329AEA21")
    IWizIECapture : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IDispatch *pHtmlDocument2Disp,
            /* [in] */ VARIANT_BOOL vbSaveSel,
            /* [retval][out] */ IDispatch **ppWizDocumentDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BackgroundSave( 
            /* [in] */ IDispatch *pHtmlDocument2Disp,
            /* [in] */ VARIANT_BOOL vbSaveSel) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DatabasePath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DatabasePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SaveButtonOnly( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SaveButtonOnly( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizIECaptureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizIECapture * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizIECapture * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizIECapture * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWizIECapture * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWizIECapture * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWizIECapture * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWizIECapture * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IWizIECapture * This,
            /* [in] */ IDispatch *pHtmlDocument2Disp,
            /* [in] */ VARIANT_BOOL vbSaveSel,
            /* [retval][out] */ IDispatch **ppWizDocumentDisp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BackgroundSave )( 
            IWizIECapture * This,
            /* [in] */ IDispatch *pHtmlDocument2Disp,
            /* [in] */ VARIANT_BOOL vbSaveSel);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DatabasePath )( 
            IWizIECapture * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DatabasePath )( 
            IWizIECapture * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SaveButtonOnly )( 
            IWizIECapture * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SaveButtonOnly )( 
            IWizIECapture * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IWizIECaptureVtbl;

    interface IWizIECapture
    {
        CONST_VTBL struct IWizIECaptureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizIECapture_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizIECapture_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizIECapture_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizIECapture_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWizIECapture_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWizIECapture_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWizIECapture_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWizIECapture_Save(This,pHtmlDocument2Disp,vbSaveSel,ppWizDocumentDisp)	\
    ( (This)->lpVtbl -> Save(This,pHtmlDocument2Disp,vbSaveSel,ppWizDocumentDisp) ) 

#define IWizIECapture_BackgroundSave(This,pHtmlDocument2Disp,vbSaveSel)	\
    ( (This)->lpVtbl -> BackgroundSave(This,pHtmlDocument2Disp,vbSaveSel) ) 

#define IWizIECapture_get_DatabasePath(This,pVal)	\
    ( (This)->lpVtbl -> get_DatabasePath(This,pVal) ) 

#define IWizIECapture_put_DatabasePath(This,newVal)	\
    ( (This)->lpVtbl -> put_DatabasePath(This,newVal) ) 

#define IWizIECapture_get_SaveButtonOnly(This,pVal)	\
    ( (This)->lpVtbl -> get_SaveButtonOnly(This,pVal) ) 

#define IWizIECapture_put_SaveButtonOnly(This,newVal)	\
    ( (This)->lpVtbl -> put_SaveButtonOnly(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWizIECapture_INTERFACE_DEFINED__ */



#ifndef __WizWebCaptureLib_LIBRARY_DEFINED__
#define __WizWebCaptureLib_LIBRARY_DEFINED__

/* library WizWebCaptureLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WizWebCaptureLib;

EXTERN_C const CLSID CLSID_WizIECapture;

#ifdef __cplusplus

class DECLSPEC_UUID("ED20B72B-C691-4331-A8D0-FBBB231A5DD4")
WizIECapture;
#endif
#endif /* __WizWebCaptureLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


