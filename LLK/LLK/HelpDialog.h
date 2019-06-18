#pragma once


// CHelpDialog 对话框

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHelpDialog();

	virtual BOOL OnInitDialog();

    // 对话框数据
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_dcMem;//内存DC
	CDC m_dcMem2;
	CDC m_dcHelp;//暂停图片的内存DC
	CDC m_dcHelp2;
	CRect m_rtHelp;//
	CRect m_rtHelp2;
	HICON m_hIcon;//图标
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	
	void UpdateHelp(int nPos);
	
};
