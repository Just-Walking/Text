// HelpDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "HelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//加载系统图标
	m_rtHelp.left = 0;
	m_rtHelp.right = 300;
	m_rtHelp.top = 0;
	m_rtHelp.bottom = 500;

	m_rtHelp2.left = 0;
	m_rtHelp2.right = 500;
	m_rtHelp2.top = 500;
	m_rtHelp2.bottom = 540;

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()



BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	CClientDC dc(this);
	
	//加载bmp图片资源
	HANDLE hbmpHelp=::LoadImage(NULL,_T("theme\\picture\\Help.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//创建与视频内存兼容的内存DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcHelp.SelectObject(hbmpHelp);
	
	//创建内存dc大小
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc,rtClient.Width(),rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	 //绘制白色背景
	m_dcMem.BitBlt(0,0,rtClient.Width(),rtClient.Height(),NULL,0,0,WHITENESS);

	//绘制帮助信息
	UpdateHelp(0);

	//设置滚动条范围
	CBitmap bmpHelp;
	bmpHelp.Attach(hbmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);  //获得bmpHelp的位图结构
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0,bmpInfo.bmHeight);
	///////////////////
	//加载bmp图片资源
	HANDLE hbmpHelp2=::LoadImage(NULL,_T("theme\\picture\\Help2.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//创建与视频内存兼容的内存DC
	m_dcHelp2.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcHelp2.SelectObject(hbmpHelp2);
	
	m_dcMem2.CreateCompatibleDC(&m_dcHelp2);
	CBitmap bmpMem2;
	bmpMem2.CreateCompatibleBitmap(&m_dcHelp2,500,40);
	m_dcMem2.SelectObject(&bmpMem2);
	InvalidateRect(m_rtHelp2,FALSE);
	///////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	int pos = pScrollBar->GetScrollPos();
	int nMinPos;
	int nMaxPos;
	pScrollBar->GetScrollRange(&nMinPos, &nMaxPos);
	switch(nSBCode)
	{
	case SB_LINEUP:   //向上按钮
		pos-=1;
		break;
	case SB_LINEDOWN:  //向下按钮
		pos+=1;
		break;
	case SB_PAGEUP:   //向上翻页
		pos-=10;
		break;
	case SB_PAGEDOWN:  //向下翻页
		pos+=10;
		break;
	case SB_TOP:    //顶部
		pos=nMinPos;
		break;
	case SB_BOTTOM:  //底部
		pos=nMaxPos;
		break;
	case SB_THUMBPOSITION:   //点击在滑块上
		pos=nPos;
		break;
	default:
		break;

	}

	//设置滑动条与当前点的值
	pScrollBar->SetScrollPos(pos,TRUE);
	//更新帮助信息
	UpdateHelp(pos);


	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);

}

void CHelpDialog::UpdateHelp(int nPos)
{
	//将重绘区绘制成白色
	m_dcMem.BitBlt(m_rtHelp.left,m_rtHelp.top,m_rtHelp.Width(),m_rtHelp.Height(),NULL,0,0,WHITENESS);
	//绘制当前点的帮助信息
	m_dcMem.BitBlt(m_rtHelp.left,m_rtHelp.top,m_rtHelp.Width(),m_rtHelp.Height(),&m_dcHelp,0,nPos,SRCCOPY);
	
	
	//更新界面
	InvalidateRect(m_rtHelp,FALSE);
	
}

void CHelpDialog::OnPaint()//绘图方法
{

	CPaintDC dc(this);

	// TODO: 在此处添加消息处理程序代码CDialogEx::OnPaint();

	
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	
	dc.BitBlt(0,0,rtClient.Width(),rtClient.Height(),&m_dcMem,0,0,SRCCOPY);
	
	dc.BitBlt(m_rtHelp2.left,m_rtHelp2.top,500,40,&m_dcHelp2,0,0,SRCCOPY);//绘图位置

}