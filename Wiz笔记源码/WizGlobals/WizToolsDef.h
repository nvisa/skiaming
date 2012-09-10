#pragma once


#pragma pack(1)

interface IWizToolsExtractTagsEvents
{
	virtual HRESULT __stdcall OnTag(LPCWSTR lpszTagHtml) = 0;
};

interface IWizToolsEnumLinksEvents
{
	virtual HRESULT __stdcall OnLink(LPCWSTR lpszURL, LPCWSTR lpszLinkText) = 0;
};


interface IWizToolsEnumTableCellsEvents
{
	virtual HRESULT __stdcall OnCell(long columnIndex, long rowIndex, LPCWSTR lpszCellHtml) = 0;
};

interface IWizToolsSearchDocumentsEvents
{
	virtual HRESULT __stdcall OnDocuments(LPCWSTR lpszDocumentID, LPCWSTR lpszURL) = 0;
};

interface IWizToolsParseHtmlEvents
{
	virtual HRESULT __stdcall ProcessTag(LPWSTR lpszTag, long nTagBufferSize) = 0;
	virtual HRESULT __stdcall ProcessText(LPWSTR lpszText, long nTextBufferSize) = 0;
	virtual HRESULT __stdcall ProcessProgress(long nProgress) = 0;
	virtual HRESULT __stdcall IsProcessTagsInComments() = 0;
};


#define WIZ_BUBBLE_RESULT_TIME_OUT			0
#define WIZ_BUBBLE_RESULT_CLOSE				1
#define WIZ_BUBBLE_RESULT_CUSTOM_BUTTON		2
#define WIZ_BUBBLE_RESULT_TEXT				3


#define WIZ_CONVERT_FILE_TO_HTML_USE_INNEL_ONVERTER		0x01


#pragma pack()





static const GUID IID_IWizMimeMailAddress = {0x0171DB92,0xCE68,0x4113,{0x9B,0xC4,0x79,0x6A,0xBB,0x1F,0x6B,0x4A}};


static const GUID IID_IWizMimeHeader = {0x0CCFBC62,0x21DC,0x4A1F,{0x87,0xB6,0x45,0xB6,0xFD,0x24,0x56,0x9F}};


static const GUID IID_IWizMimeBody = {0x68AA0515,0xCF97,0x4BD4,{0xBF,0xB8,0x74,0x22,0x8F,0xB9,0x4B,0x1F}};


static const GUID IID_IWizMimeMessage = {0xEDB12A69,0xCAB5,0x4B44,{0x93,0xA1,0x5B,0x7A,0x4D,0x02,0x15,0x12}};


static const GUID IID_IWizMimeMailAddressCollection = {0x59719593,0x5DEE,0x4CA4,{0x82,0xD2,0x4F,0x2D,0x4A,0x81,0x4E,0x66}};


static const GUID IID_IWizMimeBodyCollection = {0xFCDA62A0,0x621F,0x4025,{0x8B,0xD9,0x34,0x17,0x45,0xF8,0x8A,0x9D}};


static const GUID IID_IWizMimeMessageCreator = {0xD25BE8FA,0x3091,0x4925,{0x87,0x04,0x58,0x9D,0x32,0xE2,0xF5,0xA6}};



MIDL_INTERFACE("0171DB92-CE68-4113-9BC4-796ABB1F6B4A")
IWizMimeMailAddress : public IUnknown
{
public:
	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
		/* [in] */ BSTR newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Email( 
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Email( 
		/* [in] */ BSTR newVal) = 0;

};

MIDL_INTERFACE("0CCFBC62-21DC-4A1F-87B6-45B6FD24569F")
IWizMimeHeader : public IUnknown
{
public:
	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Subject( 
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Subject( 
		/* [in] */ BSTR newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_From( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_From( 
		/* [in] */ IUnknown *newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_To( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_To( 
		/* [in] */ IUnknown *newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CC( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CC( 
		/* [in] */ IUnknown *newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BCC( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BCC( 
		/* [in] */ IUnknown *newVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Sent( 
		/* [retval][out] */ DATE *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Received( 
		/* [retval][out] */ DATE *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FieldValue( 
		/* [in] */ BSTR bstrFieldName,
		/* [in] */ BSTR bstrValueName,
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Message( 
		/* [retval][out] */ IUnknown **pVal) = 0;

};

MIDL_INTERFACE("68AA0515-CF97-4BD4-BFB8-74228FB94B1F")
IWizMimeBody : public IUnknown
{
public:
	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BodyName( 
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FieldValue( 
		/* [in] */ BSTR bstrFieldName,
		/* [in] */ BSTR bstrValueName,
		/* [retval][out] */ BSTR *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Message( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetData( 
		/* [in] */ IStream *pStream) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetData( 
		/* [in] */ IStream *pStream) = 0;

};

MIDL_INTERFACE("EDB12A69-CAB5-4B44-93A1-5B7A4D021512")
IWizMimeMessage : public IUnknown
{
public:
	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Header( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PlainBodies( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HTMLBodies( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ResourceBodies( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttachmentBodies( 
		/* [retval][out] */ IUnknown **pVal) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromFile( 
		/* [in] */ BSTR bstrFileName) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromStream( 
		/* [in] */ IUnknown *pStreamUnk) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToHTMLFile( 
		/* [in] */ BSTR bstrFileName,
		/* [in] */ long nFlags) = 0;

};

MIDL_INTERFACE("59719593-5DEE-4CA4-82D2-4F2D4A814E66")
IWizMimeMailAddressCollection : public IUnknown
{
public:
	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
		/* [retval][out] */ LONG *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
		/* [in] */ LONG nIndex,
		/* [retval][out] */ IUnknown **pVal) = 0;

};

MIDL_INTERFACE("FCDA62A0-621F-4025-8BD9-341745F88A9D")
IWizMimeBodyCollection : public IUnknown
{
public:
	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
		/* [retval][out] */ LONG *pVal) = 0;

	virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
		/* [in] */ LONG nIndex,
		/* [retval][out] */ IUnknown **pVal) = 0;

};

MIDL_INTERFACE("D25BE8FA-3091-4925-8704-589D32E2F5A6")
IWizMimeMessageCreator : public IUnknown
{
public:
	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddBody( 
		/* [in] */ BSTR bstrFileName,
		/* [in] */ BSTR bstrURL,
		/* [in] */ IUnknown *pDataStream) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;

	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
		/* [in] */ BSTR bstrTitle,
		/* [in] */ IUnknown *pDataStream) = 0;

};



enum WizHtmlEditorViewType
{
	wizhtmleditorPreview = 0,
	wizhtmleditorEditor = 1,
};

enum WizHtmlEditorToolBarType
{
	wizhtmleditorCompact,
	wizhtmleditorFull
};

enum WizHtmlEditorSetViewTypeFlags
{
	wizhtmleditorNoFocus = 0x01
};

interface IWebBrowser2;
interface IHTMLDocument2;


interface IWizHtmlEditor
{
	virtual HRESULT __stdcall Create(HWND hwndParent, BSTR bstrOptions) = 0;
	virtual HRESULT __stdcall Destroy() = 0;
	virtual HRESULT __stdcall Delete() = 0;
	virtual HRESULT __stdcall get_Window(HWND* phwnd) = 0;
	virtual HRESULT __stdcall get_PreviewBrowser2(IWebBrowser2** ppBrowser) = 0;
	virtual HRESULT __stdcall get_EditorBrowser2(IWebBrowser2** ppBrowser) = 0;
	virtual HRESULT __stdcall put_ViewType(LONG val) = 0;
	virtual HRESULT __stdcall get_ViewType(LONG* pVal) = 0;
	virtual HRESULT __stdcall put_ToolBarType(LONG val) = 0;
	virtual HRESULT __stdcall get_ToolBarType(LONG* pVal) = 0;
	virtual HRESULT __stdcall put_Modified(VARIANT_BOOL val) = 0;
	virtual HRESULT __stdcall get_Modified(VARIANT_BOOL* pVal) = 0;
	virtual HRESULT __stdcall put_Zoom(LONG nViewType, LONG val) = 0;
	virtual HRESULT __stdcall get_Zoom(LONG nViewType, LONG* pVal) = 0;
	virtual HRESULT __stdcall UpdateLayout() = 0;
	virtual HRESULT __stdcall Focus() = 0;
	virtual HRESULT __stdcall ForwardMsg(UINT nMsg, WPARAM wParam, LPARAM lParam, LRESULT* pnRet) = 0;
	virtual HRESULT __stdcall Reset(LONG nInitViewType) = 0;
	virtual HRESULT __stdcall OnDocumentCompleteEx(IHTMLDocument2* pDoc) = 0;
	virtual HRESULT __stdcall SetOptions(BSTR bstrOptions) = 0;
	virtual HRESULT __stdcall ExecCommand(BSTR bstrCommandName, BSTR bstrParams) = 0;
	virtual HRESULT __stdcall Highlight(BSTR bstrText, BSTR bstrParams) = 0;
	virtual HRESULT __stdcall put_ViewType2(LONG val, long nFlags) = 0;
};

interface IWizHtmlEditorEvents
{
	virtual HRESULT __stdcall OnCreate(IWizHtmlEditor* pEditor) = 0;
	virtual HRESULT __stdcall OnCreateToolBar(LONG* pnToolBarType) = 0;
	virtual HRESULT __stdcall OnViewTypeChanging(IWizHtmlEditor* pEditor, LONG nOldViewType, LONG nNewViewType) = 0;
	virtual HRESULT __stdcall OnViewTypeChanged(IWizHtmlEditor* pEditor, LONG nOldViewType, LONG nNewViewType) = 0;
	virtual HRESULT __stdcall OnToolBarTypeChanged(IWizHtmlEditor* pEditor, LONG nOldViewType, LONG nNewViewType) = 0;
	virtual HRESULT __stdcall OnBrowserBeforeNavigate2(IWizHtmlEditor* pEditor, LONG nViewType, IDispatch* pDisp, BSTR ndytUTL) = 0;
	virtual HRESULT __stdcall OnBrowserNewWindow2(IWizHtmlEditor* pEditor, LONG nViewType, IDispatch** ppDisp) = 0;
	virtual HRESULT __stdcall OnBrowserNewWindow3(IWizHtmlEditor* pEditor, LONG nViewType, IDispatch** ppDisp, LONG nFlags, BSTR bstrUrlContext, BSTR bstrUrl) = 0;
	virtual HRESULT __stdcall OnBrowserStatusTextChange(IWizHtmlEditor* pEditor, LONG nViewType, BSTR bstrText) = 0;
	virtual HRESULT __stdcall OnBrowserGetSearchKeywords(IWizHtmlEditor* pEditor, LONG nViewType, BSTR* pbstrSearchKeywords) = 0;
	virtual HRESULT __stdcall OnBrowserZoomChanged(IWizHtmlEditor* pEditor, LONG nViewType) = 0;
	virtual HRESULT __stdcall OnBeforePreview(IWizHtmlEditor* pEditor, BSTR* pbstrPreviewHtmlFileName) = 0;
	virtual HRESULT __stdcall OnBeforeEdit(IWizHtmlEditor* pEditor, BSTR* pbstrEditHtmlFileName) = 0;
	virtual HRESULT __stdcall OnQueryHyperlink(IWizHtmlEditor* pEditor, BSTR bstrInitURL, BSTR* pbstrResultURL) = 0;
	virtual HRESULT __stdcall OnExternalCommand(IWizHtmlEditor* pEditor, BSTR bstrCommandName, BSTR bstrExOptions) = 0;
	virtual HRESULT __stdcall OnGetDropTarget(IWizHtmlEditor* pEditor, LONG nViewType, IUnknown *pDropTarget, IUnknown** ppUnk) = 0;
	virtual HRESULT __stdcall OnDocumentComplete(IWizHtmlEditor* pEditor, LONG nViewType) = 0;
	virtual HRESULT __stdcall IsDataChanged(IWizHtmlEditor* pEditor, LONG nViewType) = 0;
	virtual HRESULT __stdcall OnOptions() = 0;
};


#define WIZBUBBLE_SHOWLINKURLASMESSAGE		0x01


