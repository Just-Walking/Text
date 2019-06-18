#pragma once
#include"GameControl.h"
#include"global.h"
#include"HelpDialog.h"
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();
// 对话框数据
	enum { IDD = IDD_GAME_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	bool m_bPlaying;
	bool m_bPause;
	int timeCount;  
	CDC m_dcMem;
	CDC m_dcBG;	
	CDC m_dcElement;
	CDC m_dcMask;
	CDC m_dcCache;//缓存的内存DC
	CDC m_dcPause;//暂停图片的内存DC
	CRect m_rtGameRect; 
	bool m_bFirstPoint;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	CSize m_sizeElem;
	CGameControl m_gameControl;
	CPoint m_ptGameTop;

	DECLARE_MESSAGE_MAP()
public:
	void DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum);
	void InitBackground(void);
	void DrawTipFrame(int nRow,int nCol);// DDX/DDV 支持
	void InitElement();
	void UpdateMap(void);
	void UpdateWindow(void);
	bool IsLink(void);
	void JudgeWin(void);       //判断胜负
	void DrawTipLine(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButton1();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton4();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime(void);
	afx_msg void OnClickedButtonstop();
	afx_msg void OnBnClickedButton5();
};
