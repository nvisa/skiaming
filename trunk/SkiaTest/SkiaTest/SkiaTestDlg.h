
// SkiaTestDlg.h : 头文件
//

#pragma once


// CSkiaTestDlg 对话框
class SkCanvas;
class SkBitmap;
class CSkiaTestDlg : public CDialogEx
{
// 构造
public:
	CSkiaTestDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CSkiaTestDlg();

// 对话框数据
	enum { IDD = IDD_SKIATEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	SkCanvas* m_pCanvas;
	SkBitmap* m_pBitmap;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBntDraw();
	afx_msg void OnBnClickedBtnOut();
	afx_msg void OnSelchangeCombo();
};
