#pragma once
#include"GameControl.h"
#include"global.h"
#include"HelpDialog.h"
// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();
// �Ի�������
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
	CDC m_dcCache;//������ڴ�DC
	CDC m_dcPause;//��ͣͼƬ���ڴ�DC
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
	void DrawTipFrame(int nRow,int nCol);// DDX/DDV ֧��
	void InitElement();
	void UpdateMap(void);
	void UpdateWindow(void);
	bool IsLink(void);
	void JudgeWin(void);       //�ж�ʤ��
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
