#include "stdafx.h"
#include "WizUIBase.h"


#include <math.h>



void WizGradientFill(HDC hDC, const RECT& rcItem, COLORREF cr1, COLORREF cr2, BOOL bHor)
{
	GRADIENT_RECT grdRect = { 0, 1 };
	TRIVERTEX triVertext[ 2 ] = {
									rcItem.left,
									rcItem.top,
									GetRValue( cr1) << 8,
									GetGValue( cr1) << 8,
									GetBValue( cr1) << 8,
									0x0000,			
									rcItem.right,
									rcItem.bottom,
									GetRValue( cr2) << 8,
									GetGValue( cr2) << 8,
									GetBValue( cr2) << 8,
									0x0000
								};
	
	CDCHandle dc(hDC);
	dc.GradientFill( triVertext, 2, &grdRect, 1, bHor ? GRADIENT_FILL_RECT_H : GRADIENT_FILL_RECT_V);
}


void WizDrawItemBackgroundBox(HDC hDC, const RECT& rcItem, COLORREF rgbBackground, COLORREF rgbOuter, COLORREF rgbInner, COLORREF rgbTop, COLORREF rgbBottom)
{
	CDCHandle dc(hDC);
	//
	CWizDCSaver saver(dc);
	//	
	//
	// draw selected background and border
	CRect rcSelect( rcItem );
		
	CPen penBorder;
	penBorder.CreatePen( PS_SOLID, 1, rgbOuter);
	CBrush bshInterior;
	bshInterior.CreateSolidBrush( rgbBackground );
		
	dc.SelectPen( penBorder );
	dc.SelectBrush( bshInterior );
		
	dc.RoundRect( rcSelect, CPoint( 5, 5 ) );
	rcSelect.DeflateRect( 1, 1 );
		
	CPen penInnerBorder;
	penInnerBorder.CreatePen( PS_SOLID, 1, rgbInner);
	dc.SelectPen( penInnerBorder );
		
	dc.RoundRect( rcSelect, CPoint( 2, 2 ) );
	rcSelect.DeflateRect( 1, 1 );
		
	GRADIENT_RECT grdRect = { 0, 1 };
	TRIVERTEX triVertext[ 2 ] = {
									rcSelect.left,
									rcSelect.top,
									GetRValue( rgbTop) << 8,
									GetGValue( rgbTop) << 8,
									GetBValue( rgbTop) << 8,
									0x0000,			
									rcSelect.right,
									rcSelect.bottom,
									GetRValue( rgbBottom) << 8,
									GetGValue( rgbBottom) << 8,
									GetBValue( rgbBottom) << 8,
									0x0000
								};
	
	dc.GradientFill( triVertext, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
}

void WizDrawItemBackgroundBoxEx(HDC hDC, const RECT& rcItem, COLORREF rgbBackground, COLORREF rgbOuter, COLORREF rgbInner, COLORREF rgbTop, COLORREF rgbBottom,
								int nTop, BOOL bToBottom)
{
	CDCHandle dc(hDC);
	CWizDCSaver saver(dc);
	//	
	BOOL bCustomTop = (nTop != rcItem.top);
	//
	// draw selected background and border
	CRect rcSelect( rcItem );
		
	CPen penBorder;
	penBorder.CreatePen( PS_SOLID, 1, rgbOuter);
	CBrush bshInterior;
	bshInterior.CreateSolidBrush( rgbBackground );
		
	dc.SelectPen( penBorder );
	dc.SelectBrush( bshInterior );
		
	dc.RoundRect( rcSelect, CPoint( 5, 5 ) );
	rcSelect.DeflateRect( 1, 1 );
		
	CPen penInnerBorder;
	penInnerBorder.CreatePen( PS_SOLID, 1, rgbInner);
	dc.SelectPen( penInnerBorder );
		
	dc.RoundRect( rcSelect, CPoint( 2, 2 ) );
	rcSelect.DeflateRect( 1, 1 );
	//
	int top = bCustomTop ? nTop : rcSelect.top;
	//
		
	GRADIENT_RECT grdRect = { 0, 1 };
	if (bToBottom)
	{
		TRIVERTEX triVertext[ 2 ] = {
									rcSelect.left,
									top,
									GetRValue( rgbTop) << 8,
									GetGValue( rgbTop) << 8,
									GetBValue( rgbTop) << 8,
									0x0000,			
									rcSelect.right,
									rcSelect.bottom,
									GetRValue( rgbBottom) << 8,
									GetGValue( rgbBottom) << 8,
									GetBValue( rgbBottom) << 8,
									0x0000
								};
	
		dc.GradientFill( triVertext, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
	}
	else
	{
		TRIVERTEX triVertext[ 2 ] = {
									rcSelect.left,
									rcSelect.top,
									GetRValue( rgbTop) << 8,
									GetGValue( rgbTop) << 8,
									GetBValue( rgbTop) << 8,
									0x0000,			
									rcSelect.right,
									top,
									GetRValue( rgbBottom) << 8,
									GetGValue( rgbBottom) << 8,
									GetBValue( rgbBottom) << 8,
									0x0000
								};
	
		dc.GradientFill( triVertext, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
	}
}


void WizDrawItemBackgroundEmptyBox(HDC hDC, const RECT& rcItem, COLORREF rgbBackground, COLORREF rgbOuter, COLORREF rgbInner)
{
	CDCHandle dc(hDC);
	CWizDCSaver saver(dc);
	//	
	//
	// draw selected background and border
	CRect rcSelect( rcItem );
		
	CPen penBorder;
	penBorder.CreatePen( PS_SOLID, 1, rgbOuter);
	CBrush bshInterior;
	bshInterior.CreateSolidBrush( rgbBackground );
		
	dc.SelectPen( penBorder );
	dc.SelectBrush( bshInterior );
		
	dc.RoundRect( rcSelect, CPoint( 5, 5 ) );
	rcSelect.DeflateRect( 1, 1 );
		
	CPen penInnerBorder;
	penInnerBorder.CreatePen( PS_SOLID, 1, rgbInner);
	dc.SelectPen( penInnerBorder );
		
	dc.RoundRect( rcSelect, CPoint( 2, 2 ) );
}


void WizDrawItemBackground(HWND hWnd, HDC hDC, const RECT& rcItem, UINT nState, COLORREF crDefaultBackgroundColor)
{
	CDCHandle dc(hDC);
	CWizDCSaver saver(dc);
	//
	dc.FillSolidRect(&rcItem, crDefaultBackgroundColor);
	//
	BOOL bSelected = (nState & wizStateSelected) ? TRUE : FALSE;
	BOOL bFocused = (nState & wizStateFocused) ? TRUE : FALSE;
	BOOL bHot = (nState & wizStateHot) ? TRUE : FALSE;
	BOOL bDropTarget = (nState & wizStateControlDropTarget) ? TRUE : FALSE;
	//
	if (bSelected)
	{
		// draw selected background and border
		BOOL bControlFocus = ( GetFocus() == hWnd );
		//
		if (bControlFocus || bDropTarget)
		{
			static COLORREF rgbSelectOuter = RGB( 132, 172, 221);
			static COLORREF rgbSelectInner = RGB( 241, 247, 254);
			static COLORREF rgbSelectTop = RGB( 235, 244, 254);
			static COLORREF rgbSelectBottom = RGB( 207, 228, 254);
			//
			WizDrawItemBackgroundBox(hDC, rcItem, crDefaultBackgroundColor, rgbSelectOuter, rgbSelectInner, rgbSelectTop, rgbSelectBottom);
		}
		else
		{
			static COLORREF rgbNoFocusOuter = RGB( 217, 217, 217);
			static COLORREF rgbNoFocusInner = RGB( 250, 250, 251);
			static COLORREF rgbNoFocusTop = RGB( 248, 248, 248);
			static COLORREF rgbNoFocusBottom = RGB( 229, 229, 229);
			//
			WizDrawItemBackgroundBox(hDC, rcItem, crDefaultBackgroundColor, rgbNoFocusOuter, rgbNoFocusInner, rgbNoFocusTop, rgbNoFocusBottom);
		}
	}
	else if (bHot)
	{
		static COLORREF rgbSelectOuter = RGB( 182, 214, 251);
		static COLORREF rgbSelectInner = RGB( 242, 247, 254 );
		static COLORREF rgbSelectTop = RGB( 250, 251, 253);
		static COLORREF rgbSelectBottom = RGB( 235, 243, 253 );
		//
		WizDrawItemBackgroundBox(hDC, rcItem, crDefaultBackgroundColor, rgbSelectOuter, rgbSelectInner, rgbSelectTop, rgbSelectBottom);
	}
	else if (bFocused)
	{
		static COLORREF rgbSelectOuter = RGB( 132, 172, 221);
		static COLORREF rgbSelectInner = RGB( 241, 247, 254);
		//
		WizDrawItemBackgroundEmptyBox(hDC, rcItem, crDefaultBackgroundColor, rgbSelectOuter, rgbSelectInner);
	}
	//
}

void WizDrawItemBackground_Button(HDC hDC, const RECT& rcItem, BOOL bHover)
{
	CDCHandle dc(hDC);
	//
	dc.FillSolidRect(&rcItem, ::GetSysColor(COLOR_WINDOW));
	//
	if (bHover)
	{
		WizDrawCrystalBackground_Hot(hDC, rcItem, CRect(rcItem).CenterPoint().y); 
	}
	else
	{
		WizDrawCrystalBackground_Pressed(hDC, rcItem, CRect(rcItem).CenterPoint().y); 
	}
}

void WizDrawCrystalBackground(HDC hDC, const RECT& rcItem, int nCenterLine, BOOL bHot)
{
	CDCHandle dc(hDC);
	CWizDCSaver saver(dc);
	//
	COLORREF rgbTop = RGB(255, 255, 255);
	COLORREF rgbCenterTop = bHot ? RGB(243, 243, 243) : RGB(240, 240, 240);
	COLORREF rgbCenterBottom = bHot ? RGB(228, 228, 228) : RGB(232, 232, 232);
	COLORREF rgbBottom = bHot ? RGB(211, 211, 211) : RGB(234, 234, 234);
	//
	CRect rcTop = rcItem;
	rcTop.bottom = nCenterLine;
	//
	CRect rcBottom = rcItem;
	rcBottom.top = rcTop.bottom;
	//
	GRADIENT_RECT grdRect = { 0, 1 };
	TRIVERTEX triVertextTop[ 2 ] = {
									rcTop.left,
									rcTop.top,
									GetRValue( rgbTop) << 8,
									GetGValue( rgbTop) << 8,
									GetBValue( rgbTop) << 8,
									0x0000,			
									rcTop.right,
									rcTop.bottom,
									GetRValue( rgbCenterTop) << 8,
									GetGValue( rgbCenterTop) << 8,
									GetBValue( rgbCenterTop) << 8,
									0x0000
								};
	
	dc.GradientFill( triVertextTop, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
	//
	TRIVERTEX triVertextBottom[ 2 ] = {
									rcBottom.left,
									rcBottom.top,
									GetRValue( rgbCenterBottom) << 8,
									GetGValue( rgbCenterBottom) << 8,
									GetBValue( rgbCenterBottom) << 8,
									0x0000,			
									rcBottom.right,
									rcBottom.bottom,
									GetRValue( rgbBottom) << 8,
									GetGValue( rgbBottom) << 8,
									GetBValue( rgbBottom) << 8,
									0x0000
								};
	
	dc.GradientFill( triVertextBottom, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
}

void WizDrawCrystalBackground_Hot(HDC hDC, const RECT& rcItem, int nCenterLine)
{
	CDCHandle dc(hDC);
	CWizDCSaver saver(dc);
	//
	CRect rcInner = rcItem;
	//
	rcInner.DeflateRect(2, 2);
	WizDrawCrystalBackground(hDC, rcInner, nCenterLine, TRUE);
	//
	dc.SelectBrush((HBRUSH)::GetStockObject(NULL_BRUSH));
	//
	CRect rcBorder = rcItem;
	static COLORREF rgbOuter = RGB( 217, 217, 217);
	static COLORREF rgbInner = RGB( 250, 250, 251);
	//
	CPen penBorder;
	penBorder.CreatePen( PS_SOLID, 1, rgbOuter);
	dc.SelectPen( penBorder );
	dc.RoundRect( rcBorder, CPoint( 2, 2 ) );
	//
	rcBorder.DeflateRect( 1, 1 );
	CPen penInnerBorder;
	penInnerBorder.CreatePen( PS_SOLID, 1, rgbInner);
	dc.SelectPen( penInnerBorder );
	dc.RoundRect( rcBorder, CPoint( 2, 2 ) );
}

void WizDrawCrystalBackground_Pressed(HDC hDC, const RECT& rcItem, int nCenterLine)
{
	CDCHandle dc(hDC);
	CWizDCSaver saver(dc);
	//
	COLORREF rgb1 = RGB(213, 213, 213);
	COLORREF rgb2 = RGB(235, 235, 235);

	COLORREF rgb3 = RGB(233, 233, 233);
	COLORREF rgb4 = RGB(228, 228, 228);

	COLORREF rgb5 = RGB(221, 221, 221);
	COLORREF rgb6 = RGB(221, 221, 221);
	//
	CRect rcBorder = rcItem;
	//
	CRect rcCenter = rcItem;
	rcCenter.DeflateRect(1, 1);
	//
	CRect rc1 = rcCenter;
	rc1.bottom = rcCenter.top + 5;
	//
	CRect rc2 = rcCenter;
	rc2.top = rc1.bottom;
	rc2.bottom = nCenterLine;
	//
	CRect rc3 = rcCenter;
	rc3.top = rc2.bottom;

	GRADIENT_RECT grdRect = { 0, 1 };
	//
	TRIVERTEX triVertext1[ 2 ] = {
									rc1.left,
									rc1.top,
									GetRValue( rgb1) << 8,
									GetGValue( rgb1) << 8,
									GetBValue( rgb1) << 8,
									0x0000,			
									rc1.right,
									rc1.bottom,
									GetRValue( rgb2) << 8,
									GetGValue( rgb2) << 8,
									GetBValue( rgb2) << 8,
									0x0000
								};
	
	dc.GradientFill( triVertext1, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
	//
	TRIVERTEX triVertext2[ 2 ] = {
									rc2.left,
									rc2.top,
									GetRValue( rgb3) << 8,
									GetGValue( rgb3) << 8,
									GetBValue( rgb3) << 8,
									0x0000,			
									rc2.right,
									rc2.bottom,
									GetRValue( rgb4) << 8,
									GetGValue( rgb4) << 8,
									GetBValue( rgb4) << 8,
									0x0000
								};
	
	dc.GradientFill( triVertext2, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
	//
	TRIVERTEX triVertext3[ 2 ] = {
									rc3.left,
									rc3.top,
									GetRValue( rgb5) << 8,
									GetGValue( rgb5) << 8,
									GetBValue( rgb5) << 8,
									0x0000,			
									rc3.right,
									rc3.bottom,
									GetRValue( rgb6) << 8,
									GetGValue( rgb6) << 8,
									GetBValue( rgb6) << 8,
									0x0000
								};
	
	dc.GradientFill( triVertext3, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
	//
	//
	dc.SelectBrush((HBRUSH)::GetStockObject(NULL_BRUSH));
	//
	CPen penBorder;
	penBorder.CreatePen( PS_SOLID, 1, RGB(199, 199, 199));
	dc.SelectPen( penBorder );
	dc.RoundRect( rcBorder, CPoint( 2, 2 ) );
}



void WizDrawLighterGradientLine(HDC hDC, const POINT& ptFrom, const POINT& ptTo)
{
	if (ptFrom.x == ptTo.x)
	{
		int x = ptFrom.x;
		//
		double fRateFrom = 1.03;
		double fRateTo = 1.08;
		//
		int nLength = (ptTo.y - ptFrom.y) / 2;
		int yFrom = ptFrom.y;
		int yTo = yFrom + nLength;
		for (int y = yFrom; y < yTo; y++)
		{
			int n = y - yFrom;
			double fAngle = double(n) / nLength * 90.0;
			double fAngle2 = fAngle * 3.14159265 / 180;
			double fSin = sin(fAngle2);
			//
			double fRate = fRateFrom + (double(n) / nLength * (fRateTo - fRateFrom) * fSin);
			//
			COLORREF crOld1 = ::GetPixel(hDC, x, y);
			COLORREF crNew1 = ::WizColorLighter(crOld1, (float)fRate);
			::SetPixelV(hDC, x, y, crNew1);
			//
			int y2 = ptTo.y - (y - yFrom) - 1;
			COLORREF crOld2 = ::GetPixel(hDC, x, y2);
			COLORREF crNew2 = ::WizColorLighter(crOld2, (float)fRate);
			::SetPixelV(hDC, x, y2, crNew2);
		}
	}
	else if (ptFrom.y == ptTo.y)
	{
	}
	else
	{
		ATLASSERT(FALSE);
	}
}
void WizDrawDarkerGradientLine(HDC hDC, const POINT& ptFrom, const POINT& ptTo)
{
	if (ptFrom.x == ptTo.x)
	{
		int x = ptFrom.x;
		//
		double fRateFrom = 0.98;
		double fRateTo = 0.88;
		//
		int nLength = (ptTo.y - ptFrom.y) / 2;
		int yFrom = ptFrom.y;
		int yTo = yFrom + nLength;
		for (int y = yFrom; y < yTo; y++)
		{
			int n = y - yFrom;
			double fAngle = double(n) / nLength * 90.0;
			double fAngle2 = fAngle * 3.14159265 / 180;
			double fSin = sin(fAngle2);
			//
			double fRate = fRateFrom + (double(n) / nLength * (fRateTo - fRateFrom) * fSin);
			//
			COLORREF crOld1 = ::GetPixel(hDC, x, y);
			COLORREF crNew1 = ::WizColorDarker(crOld1, (float)fRate);
			::SetPixelV(hDC, x, y, crNew1);
			//
			int y2 = ptTo.y - (y - yFrom) - 1;
			COLORREF crOld2 = ::GetPixel(hDC, x, y2);
			COLORREF crNew2 = ::WizColorDarker(crOld2, (float)fRate);
			::SetPixelV(hDC, x, y2, crNew2);
		}
	}
	else if (ptFrom.y == ptTo.y)
	{
	}
	else
	{
		ATLASSERT(FALSE);
	}
}


BOOL WizCreateUIFont(CFont& font, UINT nFlags, LPCTSTR lpszFontName, int nFontHeight)
{
	NONCLIENTMETRICS ncm;
	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
#if (WINVER >= 0x0600)
	ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(ncm.iPaddedBorderWidth);
#else
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
#endif
	//
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	//
	BOOL bBold = (nFlags & WIZUIFONT_BOLD) ? TRUE : FALSE;
	BOOL bItalic = (nFlags & WIZUIFONT_ITALIC) ? TRUE : FALSE;
	BOOL bUnderline = (nFlags & WIZUIFONT_UNDERLINE) ? TRUE : FALSE;
	BOOL bStrikeOut = (nFlags & WIZUIFONT_STRIKEOUT) ? TRUE : FALSE;
	//
	ncm.lfMenuFont.lfWeight = FW_NORMAL;
	//
	LOGFONT lf = ncm.lfMenuFont;
	lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	lf.lfItalic = bItalic;
	lf.lfUnderline = bUnderline;
	lf.lfStrikeOut = bStrikeOut;
	//
	if (lpszFontName && *lpszFontName)
	{
		_tcscpy_s(lf.lfFaceName, LF_FACESIZE, lpszFontName);
	}
	//
	if (nFontHeight != 0)
	{
		lf.lfHeight = nFontHeight;
	}
	else if (nFlags & WIZUIFONT_SMALL)
	{
		if (lf.lfHeight < 0)
		{
			lf.lfHeight += 2;
		}
		else
		{
			lf.lfHeight--;
		}
	}
	else if (nFlags & WIZUIFONT_LARGE)
	{
		if (lf.lfHeight < 0)
		{
			lf.lfHeight -= 2;
		}
		else
		{
			lf.lfHeight++;
		}
	}
	//
	return NULL != font.CreateFontIndirect(&lf);
}


int WizGetFontHeight(HWND hWnd, HFONT hFont)
{
	HDC hDC = GetDC(hWnd);
	//
	int nDC = SaveDC(hDC);
	//
	int nHeight = 0;
	//
	try
	{
		if (hFont)
		{
			SelectObject(hDC, hFont);
		}
		//
		LPCTSTR lpszString = _T("kg中国");
		//
		CSize sz;
		GetTextExtentPoint32(hDC, lpszString, (int)_tcslen(lpszString), &sz);
		//
		nHeight = sz.cy;
	}
	catch (...)
	{
	}
	//
	RestoreDC(hDC, nDC);
	//
	ReleaseDC(hWnd, hDC);
	//
	return nHeight;
}

int WizGetFontHeight(HWND hWnd)
{
	if (!hWnd)
		return 0;
	//
	CClientDC dc(hWnd);
	//
	LPCTSTR lpszString = _T("kg中国");
	//
	CSize sz;
	dc.GetTextExtent(lpszString, -1, &sz);
	//
	return sz.cy;
}

int WizGetTextWidth(HWND hWnd, LPCTSTR lpszText, HFONT hFont)
{
	if (!hWnd)
		return 0;
	//
	CClientDC dc(hWnd);
	//
	HFONT hOldFont = NULL;
	if (hFont)
	{
		hOldFont = dc.SelectFont(hFont);
	}
	//
	CSize sz;
	dc.GetTextExtent(lpszText, -1, &sz);
	//
	if (hFont)
	{
		dc.SelectFont(hOldFont);
	}
	//
	return sz.cx;
}

CWizDCSaver::CWizDCSaver(HDC hDC)
	: m_nSavedDC(0)
	, m_hDC(hDC)
{
	if (m_hDC)
	{
		m_nSavedDC = ::SaveDC(hDC);
	}
}
CWizDCSaver::~CWizDCSaver()
{
	if (m_nSavedDC && m_hDC)
	{
		RestoreDC(m_hDC, m_nSavedDC);
	}
}





CWizToolBarEdit::CWizToolBarEdit()
	: m_fMouseOver(0)
{
}
LRESULT CWizToolBarEdit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
	//
	if(m_fMouseOver == 0)
	{
		m_fMouseOver = 1;
		GetParent().Invalidate();
		GetParent().UpdateWindow();
		StartTrackMouseLeave();
	}
	//
	return lRet;
}

LRESULT CWizToolBarEdit::OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(m_fMouseOver == 1)
	{
		m_fMouseOver = 0;
		GetParent().Invalidate();
		GetParent().UpdateWindow();
	}
	return 0;
}

BOOL CWizToolBarEdit::StartTrackMouseLeave()
{
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	return _TrackMouseEvent(&tme);
}
BOOL CWizToolBarEdit::IsMouseHover() const
{
	if (m_fMouseOver)
		return TRUE;
	//
	return FALSE;
}


CWizLinkToolBarEdit::CWizLinkToolBarEdit()
{
	m_hCursor = NULL;
}
CWizLinkToolBarEdit::~CWizLinkToolBarEdit()
{
	if (m_hCursor)
	{
		DestroyCursor(m_hCursor);
		m_hCursor = NULL;
	}
}
//
LRESULT CWizLinkToolBarEdit::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	m_tip.Create(m_hWnd);
	//
	CString strTooltip = WizTranslationsTranslateString(_T("Ctrl+Click to edit hyperlink"));
	m_tip.AddTool(m_hWnd, (LPCTSTR)strTooltip);
	//
	bHandled = FALSE;
	//
	return 0;
}
LRESULT CWizLinkToolBarEdit::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CWizLinkToolBarEdit::OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_brush.IsNull())
	{
		m_brush.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
	}
	if (m_font.IsNull())
	{
		::WizCreateUIFont(m_font, WIZUIFONT_UNDERLINE);
	}
	//
	HDC hDC = (HDC)wParam;
	CDCHandle dc(hDC);
	dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
	dc.SetTextColor(RGB(0, 0, 255));
	dc.SelectFont(m_font);
	//
	return (LRESULT)m_brush.m_hBrush;
}
//
LRESULT CWizLinkToolBarEdit::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_hCursor)
	{
		m_hCursor = LoadCursor(NULL, IDC_HAND);
	}
	//
	SetCursor(m_hCursor);
	return TRUE;
}
//
LRESULT CWizLinkToolBarEdit::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ToolTipRelayEvent();
	//
	if (GetKeyState(VK_CONTROL) < 0)
	{
	}
	else
	{
		CString strText;
		GetWindowText(strText);
		if (!strText.IsEmpty())
		{
			ShellExecute(NULL, _T("open"), strText, NULL, NULL, SW_SHOW);
		}
	}
	//
	bHandled = FALSE;
	//
	return 0;
}
//

LRESULT CWizLinkToolBarEdit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ToolTipRelayEvent();
	return CWizToolBarEdit::OnMouseMove(uMsg, wParam, lParam, bHandled);
}

//
LRESULT CWizLinkToolBarEdit::OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ToolTipRelayEvent();
	//
	bHandled = FALSE;
	//
	return 0;
}
//
void CWizLinkToolBarEdit::ToolTipRelayEvent()
{
	const MSG* pMsg = GetCurrentMessage();
	if (pMsg)
	{
		MSG msg = *pMsg;
		m_tip.RelayEvent(&msg);
	}
}



void CWizVistaToolBarCtrl::DrawButtonBackground(CDCHandle dc, int nIndex, BOOL bHot)
{
	TBBUTTON button;
	GetButton(nIndex, &button);
	//
	CRect rc;
	GetButtonDrawRect(nIndex, rc);
	//
	if (button.fsStyle & BTNS_SEP)
	{
		CRect rcLine = rc;
		//
		rcLine.DeflateRect(0, 3);
		//
		rcLine.left = rcLine.CenterPoint().x;
		rcLine.right = rcLine.left + 1;
		//
		WizDrawDarkerGradientLine(dc, rcLine.TopLeft(), CPoint(rcLine.left, rcLine.bottom));
		WizDrawLighterGradientLine(dc, CPoint(rcLine.left + 1, rcLine.top), CPoint(rcLine.left + 1, rcLine.bottom));
		return;
	}
	//
	BOOL bDown = (button.fsState & TBSTATE_PRESSED) ? TRUE : FALSE;
	BOOL bChecked = (button.fsState & TBSTATE_CHECKED) ? TRUE : FALSE;
	BOOL bDropDown = m_nDropDown == nIndex;
	//
	if (bDropDown)
	{
		WizDrawCrystalBackground_Hot(dc, rc, m_nCenterLine);
		//
		CRect rcRight = rc;
		rcRight.left = rc.right - 15;
		//
		WizDrawCrystalBackground_Pressed(dc, rcRight, m_nCenterLine);
		//
		DrawSplitterLine(dc, rc, 0x01 | 0x02);
	}
	else if (bDown || bChecked)
	{
		WizDrawCrystalBackground_Pressed(dc, rc, m_nCenterLine);
		if (button.fsStyle & BTNS_DROPDOWN)
		{
			DrawSplitterLine(dc, rc, 0x02);
		}
	}
	else if (bHot)
	{
		WizDrawCrystalBackground_Hot(dc, rc, m_nCenterLine);
		if (button.fsStyle & BTNS_DROPDOWN)
		{
			DrawSplitterLine(dc, rc, 0x01 | 0x02 | 0x04);
		}
	}
	//
}
//
void CWizVistaToolBarCtrl::DrawBackground(CDCHandle dc, const CRect& rc)
{
	m_nCenterLine = rc.top + (rc.Height() - 3) / 2;
	//
	CRect rcBackground = rc;
	rcBackground.bottom -= 3;
	//
	WizDrawCrystalBackground(dc, rcBackground, m_nCenterLine, FALSE);
	//
	COLORREF rgbBottomLine1 = RGB(239, 239, 239);
	COLORREF rgbBottomLine2 = RGB(219, 219, 219);
	COLORREF rgbBottomLine3 = RGB(177, 177, 177);
	//
	dc.FillSolidRect(rc.left, rc.bottom - 3, rc.right, rc.bottom - 2, rgbBottomLine1);
	dc.FillSolidRect(rc.left, rc.bottom - 2, rc.right, rc.bottom - 1, rgbBottomLine2);
	dc.FillSolidRect(rc.left, rc.bottom - 1, rc.right, rc.bottom - 0, rgbBottomLine3);
	//
	if (-1 != m_nHighlightPos)
	{
		int xBegin = m_nHighlightPos - 16;
		for (int x = xBegin; x < m_nHighlightPos; x++)
		{
			for (int y = rc.top; y < rc.bottom - 3; y++)
			{
				float fRate = (100 + (x - xBegin) / 2) / 100.0f;
				//
				COLORREF cr = dc.GetPixel(x, y);
				cr = WizColorLighter(cr, fRate);
				dc.SetPixelV(x, y, cr);
			}
		}
	}
}


HWND CWizSimpleToolBar::CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, HICON* parrayIcon, UINT nIconCount, UINT nToolBarID)
{
	HWND hwnd = Create(hWndParent, lprc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CCS_NODIVIDER | CCS_NORESIZE | CCS_NOPARENTALIGN | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_LIST, nToolBarID);
	if (!hwnd)
		return NULL;
	SetExtendedStyle(TBSTYLE_EX_MIXEDBUTTONS);
	//
	SetButtonSize(22, 22);
	//
	m_il.Create(16, 16, ILC_COLOR32 | ILC_MASK, nIconCount, 0);
	if (parrayIcon)
	{
		for (int i = 0; i < int(nIconCount); i++)
		{
			m_il.AddIcon(parrayIcon[i]);
		}
	}
	//
	SetImageList(m_il);
	//
	CMenu menu;
	if (!menu.LoadMenu(nMenuResourceID))
		return hwnd;
	//
	CMenu menuSub = menu.GetSubMenu(0);
	if (!menuSub.IsMenu())
		return hwnd;
	//
	TCHAR szText[MAX_PATH] = {0};
	//
	int nImageIndex = 0;
	//
	for (int i = 0; i < menuSub.GetMenuItemCount(); i++)
	{
		ZeroMemory(szText, sizeof(TCHAR) * MAX_PATH);
		//
		MENUITEMINFO mii;
		//
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask = MIIM_ID | MIIM_TYPE;
		mii.dwTypeData = szText;
		mii.cch = MAX_PATH;
		//
		menuSub.GetMenuItemInfo(i, TRUE, &mii);
		if (0 == mii.wID)
			continue;
		//
		AddToolButtonNoTextWithToolTip(mii.wID, szText, nImageIndex);
	}
	//
	return hwnd;
}
HWND CWizSimpleToolBar::CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, HICON hIcon, UINT nToolBarID)
{
	return CreateEx(hWndParent, lprc, nMenuResourceID, &hIcon, 1, nToolBarID);
}
HWND CWizSimpleToolBar::CreateEx(HWND hWndParent, LPRECT lprc, UINT nMenuResourceID, LPCTSTR lpszIconFileName, UINT nToolBarID)
{
	HICON hIcon = (HICON)LoadImage(NULL, lpszIconFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	if (!hIcon)
		return NULL;
	//
	HWND hWnd = CreateEx(hWndParent, lprc, nMenuResourceID, hIcon, nToolBarID);
	//
	DestroyIcon(hIcon);
	//
	return hWnd;
}


HWND CWizSimpleToggleButton::CreateToggleButton(HWND hwndParent, LPRECT lprc, UINT nMenuResourceID, LPCTSTR lpszNormalIconFileName, LPCTSTR lpszDownIconFileName, UINT nToolBarID)
{
	HWND hwnd = CreateEx(hwndParent, lprc, nMenuResourceID, lpszNormalIconFileName, nToolBarID);
	if (!hwnd)
		return NULL;
	//
	HICON hIconDown = (HICON)LoadImage(NULL, lpszDownIconFileName, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
	if (!hIconDown)
		return hwnd;
	//
	m_il.AddIcon(hIconDown);
	//
	DestroyIcon(hIconDown);
	//
	return hwnd;
}
//
LRESULT CWizSimpleToggleButton::OnNMClick(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	bHandled = TRUE;
	//
	SetCheck(!GetCheck());
	UpdateStatus();
	//
	return 0;
}
//
UINT CWizSimpleToggleButton::GetButtonID()
{
	if (!IsToggleButton())
		return 0;
	//
	TBBUTTON tb;
	GetButton(0, &tb);
	return tb.idCommand;
}
//
BOOL CWizSimpleToggleButton::IsToggleButton()
{
	if (!IsWindow())
		return FALSE;
	//
	if (1 != GetButtonCount())
		return FALSE;
	//
	return TRUE;
}
BOOL CWizSimpleToggleButton::GetCheck()
{
	if (!IsToggleButton())
		return FALSE;
	//
	return IsButtonChecked(GetButtonID());
}
void CWizSimpleToggleButton::SetCheck(BOOL b)
{
	if (!IsToggleButton())
		return;
	//
	CheckButton(GetButtonID(), b);
	//
	UpdateStatus();
}
//
void CWizSimpleToggleButton::UpdateStatus()
{
	if (!IsToggleButton())
		return;
	//
	int nImage = 0;
	if (GetCheck())
	{
		nImage = 1;
	}
	//
	SetButtonInfo(GetButtonID(), TBIF_IMAGE, 0, 0, NULL, nImage, 0, 0, NULL);
}



CWizFlatToolBarCtrl::CWizFlatToolBarCtrl(COLORREF crBackground)
	: m_crBackground(crBackground)
	, m_bDrawShadow(FALSE)
{
}
void CWizFlatToolBarCtrl::DrawButtonBackground(CDCHandle dc, int nIndex, BOOL bHot)
{
	TBBUTTON button;
	GetButton(nIndex, &button);
	//
	CRect rc;
	GetButtonDrawRect(nIndex, rc);
	//
	if (button.fsStyle & BTNS_SEP)
	{
		CRect rcLine = rc;
		//
		rcLine.DeflateRect(0, 3);
		//
		rcLine.left = rcLine.CenterPoint().x;
		rcLine.right = rcLine.left + 1;
		//
		WizDrawDarkerGradientLine(dc, rcLine.TopLeft(), CPoint(rcLine.left, rcLine.bottom));
		WizDrawLighterGradientLine(dc, CPoint(rcLine.left + 1, rcLine.top), CPoint(rcLine.left + 1, rcLine.bottom));
		return;
	}
	//
	BOOL bDown = (button.fsState & TBSTATE_PRESSED) ? TRUE : FALSE;
	BOOL bChecked = (button.fsState & TBSTATE_CHECKED) ? TRUE : FALSE;
	BOOL bDropDown = m_nDropDown == nIndex;
	//
	int nCenterLine = rc.CenterPoint().y;
	//
	if (bDropDown)
	{
		WizDrawCrystalBackground_Hot(dc, rc, nCenterLine);
		//
		CRect rcRight = rc;
		rcRight.left = rc.right - 15;
		//
		WizDrawCrystalBackground_Pressed(dc, rcRight, nCenterLine);
		//
		DrawSplitterLine(dc, rc, 0x01 | 0x02);
	}
	else if (bDown || bChecked)
	{
		WizDrawCrystalBackground_Pressed(dc, rc, nCenterLine);
		if (button.fsStyle & BTNS_DROPDOWN)
		{
			DrawSplitterLine(dc, rc, 0x02);
		}
	}
	else if (bHot)
	{
		WizDrawCrystalBackground_Hot(dc, rc, nCenterLine);
		if (button.fsStyle & BTNS_DROPDOWN)
		{
			DrawSplitterLine(dc, rc, 0x01 | 0x02 | 0x04);
		}
	}
}

//
void CWizFlatToolBarCtrl::DrawBackground(CDCHandle dc, const CRect& rc)
{
	if (m_bDrawShadow)
	{
		CRect rcBackground = rc;
		rcBackground.bottom -= 1;
		//
		dc.FillSolidRect(&rcBackground, m_crBackground);
		//
		dc.FillSolidRect(rc.left, rc.bottom - 1, rc.right, rc.bottom - 0, RGB(214, 229, 245));
	}
	else
	{
		dc.FillSolidRect(&rc, m_crBackground);
	}
}
//
void CWizFlatToolBarCtrl::SetDrawShadow(BOOL b)
{
	m_bDrawShadow = b;
	//
	if (IsWindow())
	{
		Invalidate();
	}
}

int WizGetTaskBarHeight(int& nAlign)
{
	const LPCTSTR lpszClassName = _T("Shell_TrayWnd");
	HWND hWndTaskBar = ::FindWindow(lpszClassName, NULL);
	if (hWndTaskBar)
	{
		RECT rc;
		::GetWindowRect(hWndTaskBar, &rc);
		if (rc.top < 10 && rc.left < 10)
		{
			nAlign = rc.right > 400 ? WIZ_ALIGN_TOP : WIZ_ALIGN_LEFT;
		}
		else
		{
			nAlign =  rc.left < 10 ? WIZ_ALIGN_BOTTOM : WIZ_ALIGN_RIGHT;
		}
		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
		switch (nAlign)
		{
		case WIZ_ALIGN_TOP:
			return rc.bottom;
		case WIZ_ALIGN_LEFT:
			return rc.right;
		case WIZ_ALIGN_BOTTOM:
			return nScreenHeight - rc.top;
		case WIZ_ALIGN_RIGHT:
			return nScreenWidth - rc.left;
		}
		return min(rc.bottom - rc.top, rc.right - rc.left);
	}
	return 30;
}

void WizSetInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex, HWND hWnd)
{
	WizRegWriteInt64(HKEY_CURRENT_USER, lpszRegKey, WizIntToStr(nInfoWndIndex), __int64(hWnd));
}

BOOL WizIsInfoWindowIndexVisible(LPCTSTR lpszRegKey, int nInfoWndIndex)
{
	__int64 nVal = WizRegReadInt64Def(HKEY_CURRENT_USER, lpszRegKey, WizIntToStr(nInfoWndIndex), 0);
	if (!nVal)
		return FALSE;
	//
	return ::IsWindow((HWND)nVal);
}

RECT WizGetInfoWindowRect(HWND hwnd, LPCTSTR lpszRegKey, int& nInfoWndIndex)
{
	nInfoWndIndex = 0;
	while (1)
	{
		if (!WizIsInfoWindowIndexVisible(lpszRegKey, nInfoWndIndex))
			break;
		//
		nInfoWndIndex++;
	}
	//
	int nAlign = WIZ_ALIGN_BOTTOM;
	int nTaskBarHeight = WizGetTaskBarHeight(nAlign) + 4;
	//
	RECT rc;
	GetWindowRect(hwnd, &rc);
	int nWidth = rc.right - rc.left;
	int nHeight = rc.bottom - rc.top;
	//
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//
	int nScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL) + 4;
	//
	int nX = 0;
	int nY = 0;
	//
	if (nAlign == WIZ_ALIGN_BOTTOM)
	{
		nX = nScreenWidth - nWidth - nScrollBarWidth;
		nY = nScreenHeight - nHeight - nTaskBarHeight;
		nY -= (nInfoWndIndex * nHeight);
	}
	else if (nAlign == WIZ_ALIGN_TOP)
	{
		nX = nScreenWidth - nWidth - nScrollBarWidth;
		nY = nTaskBarHeight;
		nY += (nInfoWndIndex * nHeight);
	}
	else if (nAlign == WIZ_ALIGN_LEFT)
	{
		nX = nTaskBarHeight;
		nY = nScreenHeight - nHeight;
		nY -= (nInfoWndIndex * nHeight);
	}
	else if (nAlign == WIZ_ALIGN_RIGHT)
	{
		nX = nScreenWidth - nWidth - nTaskBarHeight;
		nY = nScreenHeight - nHeight;
		nY -= (nInfoWndIndex * nHeight);
	}
	//
	rc.left = nX;
	rc.top = nY;
	rc.right = rc.left + nWidth;
	rc.bottom = rc.top + nHeight;
	//
	return rc;
}
