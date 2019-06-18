// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include"GameControl.h"

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{	m_ptGameTop.x = 50;
	m_ptGameTop.y = 100;

	//初始化图片元素大小
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	//初始化图标选中状态
	m_bFirstPoint = true;
	m_bPause == false;
	m_bPlaying=false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnClickedButton1)
ON_WM_LBUTTONUP()
ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnClickedButton4)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON2, &CGameDlg::OnClickedButtonstop)
ON_BN_CLICKED(IDC_BUTTON5, &CGameDlg::OnBnClickedButton5)
END_MESSAGE_MAP()



void CGameDlg::InitBackground(void)
{	
	HANDLE Backbmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//获得当前对话框的视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBG.SelectObject(Backbmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 1100, 660);
	m_dcMem.SelectObject(&bmpMem);

	//hu绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 1100, 660, &m_dcBG, 0, 0, SRCCOPY);

}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0,0,1100,660,&m_dcMem,0,0,SRCCOPY);
	// TODO: 在此处添加消息处理程序代码
	if (m_bPause)
	{
		dc.BitBlt(m_rtGameRect.left ,
			m_rtGameRect.top , m_rtGameRect.Width() ,
			m_rtGameRect.Height() , &m_dcCache, 0, 0, SRCCOPY);
	}
	// 不为绘图消息调用 CDialogEx::OnPaint()
}

void CGameDlg::UpdateMap(void){
	int nLeft=m_ptGameTop.x;
	int nTop=m_ptGameTop.y;
	int nElemW=m_sizeElem.cx;
	int nEleH=m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for(int i=0;i<MAX_ROW;i++){
		for(int j=0;j<MAX_COL;j++){
			int nInfo = m_gameControl.GetElement(i, j);       //当前元素图片的数值
			if (nInfo == BLANK)  continue;
			//m_dcMem.BitBlt(nLeft+j*nElemW,nTop+i*nEleH,nElemW,nEleH,&m_dcElement,0,m_anMap[i][j]*nEleH,SRCCOPY);	
			m_dcMem.BitBlt(nLeft+j*nElemW,nTop+i*nEleH,nElemW,nEleH,&m_dcMask,0,nInfo*nEleH,SRCPAINT);	
			m_dcMem.BitBlt(nLeft+j*nElemW,nTop+i*nEleH,nElemW,nEleH,&m_dcElement,0,nInfo*nEleH,SRCAND);	
		}
	}
}
void CGameDlg::UpdateWindow(void){
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int a=rtWin.Width()-rtClient.Width();
	int b=rtWin.Height()-rtClient.Height();
	MoveWindow(0,0,1100+a,660+b);
	CenterWindow();
}
void CGameDlg::InitElement(){
	
	CClientDC dc(this);
	HANDLE bmpBG=::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(bmpBG);

	HANDLE bmp2=::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bmp2);

	HANDLE bmp1=::LoadImage(NULL,_T("theme\\picture\\fruit_pause.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//创建与视频内存兼容的内存DC
	m_dcPause.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcPause.SelectObject(bmp1);

	
	m_dcCache.CreateCompatibleDC(&m_dcPause);
	
	CBitmap bmpMem1;
    bmpMem1.CreateCompatibleBitmap(&m_dcPause,690,590);

	m_dcCache.SelectObject(&bmpMem1);
	m_dcCache.BitBlt(0,0,690,590,&m_dcPause,0,0,SRCCOPY);//
}

void CGameDlg::OnClickedButton1()//开始游戏按钮
{
	//初始化游戏地图
	m_gameControl.StartGame();

	m_bPlaying=true;


	this->GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);//禁止按钮

	m_GameProgress.SetRange(0, 60 * 3);    //初始范围
	m_GameProgress.SetStep(-1);				//初始步数
	m_GameProgress.SetPos(60 * 3);         //设置初始值
	
	//启动定时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	//绘制当前秒数

	//DrawGameTime();//绘制时间文本

	UpdateMap();

	InvalidateRect(m_rtGameRect,FALSE);
	
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(point.x<m_ptGameTop.x||point.y<m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp( nFlags,point);
	}

	int nRow=(point.y-m_ptGameTop.y)/m_sizeElem.cy;
	int nCol=(point.x-m_ptGameTop.x)/m_sizeElem.cx;

	if(nRow>=MAX_ROW||nCol>=MAX_COL|| !m_bPlaying)
	{
		return CDialogEx::OnLButtonUp(nFlags,point);

	}
	if(m_bFirstPoint){
			DrawTipFrame(nRow,nCol);
			m_gameControl.SetFirstPoint(nRow,nCol);
			
	
	}
	else{
		DrawTipFrame(nRow,nCol);
		m_gameControl.SetSecPoint(nRow,nCol);
	

		//获得路径
		Vertex avPath[MAX_VERTEX_NUM];

		
		int n;
		//判断是否连接
		if(m_gameControl.Link(avPath,n))
		{
			//画线提示
			DrawTipLine(avPath,n);

			
			//更新地图
			UpdateMap();

			

		}
		Sleep(200);
		InvalidateRect(m_rtGameRect,FALSE);
	}
	JudgeWin();
	/*if(m_gamecontrol.IsWin(m_GameProgress.GetPos()))
	{

		MessageBox(_T("获胜"));
		m_bPlaying=false;
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}*/

	m_bFirstPoint=!m_bFirstPoint;

}

void CGameDlg::DrawTipFrame(int nRow,int nCol){
	CClientDC dc(this);
	CBrush brush(RGB(233,43,43));
	CRect rtTipFrame;
	rtTipFrame.left=m_ptGameTop.x+nCol*m_sizeElem.cx;
	rtTipFrame.top=m_ptGameTop.y+nRow*m_sizeElem.cy;
	rtTipFrame.right=rtTipFrame.left+m_sizeElem.cx;
	rtTipFrame.bottom=rtTipFrame.top+m_sizeElem.cy;
	dc.FrameRect(rtTipFrame,&brush);
}

void CGameDlg::DrawTipLine(Vertex avPath[MAX_VERTEX_NUM], int nVexnum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}


void CGameDlg::OnClickedButton3()
{
	if (m_bPlaying == false)
		return;

	//如果能够连通，绘制提示框和连接线并更新游戏地图
	Vertex avPath[MAX_VERTEX_NUM];     //获得路径
	int nVexnum = 0;      //顶点个数
	if (m_gameControl.Help(avPath, nVexnum))
	{

		//画第一个点的提示框
		DrawTipFrame(avPath[0].row, avPath[0].col);

		//画第一个点的提示框
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		//画提示线
		DrawTipLine(avPath, nVexnum);

		Sleep(1000);    //延迟
						
		UpdateMap();	//更新地图

		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
	}
	
}


void CGameDlg::OnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_gameControl.Reset();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE); 

}

void CGameDlg::JudgeWin(void)//
{
	BOOL bGameStatus = m_gameControl.IsWin(m_GameProgress.GetPos());
	//判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//将游戏标识改为false
		m_bPlaying = false;
		//关闭定时器
		KillTimer(PLAY_TIMER_ID);
		//提示获胜
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("获胜！"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾，时间到了！"), strTitle);
		}
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
}
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


		if(nIDEvent==PLAY_TIMER_ID&&m_bPlaying&&!m_bPause)
	{
		//游戏时间减一
		m_GameProgress.StepIt();
		DrawGameTime();//绘制时间文本
		JudgeWin();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::DrawGameTime(void)
{		CFont timeFont;
	timeFont.CreatePointFont(200, _T("Consolas"));
	CFont * oldFont;
	oldFont = m_dcMem.SelectObject(&timeFont);
	m_dcMem.SetTextColor(RGB(255, 0, 0));
	m_dcMem.SetBkColor(RGB(0, 255, 255));
	int time = m_GameProgress.GetPos();
	CString strTime;

	if(100<=time&&time<=300)
	{
	strTime.Format(_T("%ds"), time);
	}
	else if(10<=time&&time<=99)
	{
	strTime.Format(_T( "  %ds"), time);

	}
	else if(time<10)
	{
		strTime.Format(_T("   %ds"), time);
	}
	
	//CRect rect;
	//GetClientRect(&rect);
	CSize size;
	size = m_dcMem.GetTextExtent(strTime, strTime.GetLength());
	//int x = ((rect.Width() - size.cx) / 2) + 208;//居中
	//int y = ((rect.Height() - size.cy) / 2) + 293;

	CRect rectw;
	rectw.left=755;
	rectw.top=600;
	rectw.bottom=600+size.cy;
	rectw.right=755+size.cx;


	m_dcMem.TextOutW(755, 600, strTime);
	m_dcMem.SelectObject(&timeFont);
	InvalidateRect(rectw, FALSE);
	//Invalidate(FALSE);


}


void CGameDlg::OnClickedButtonstop()
{
	if(!m_bPlaying)return;
	CString str;
	GetDlgItem(IDC_BUTTON2)->GetWindowTextW(str);
	if (str == "暂停游戏")
	{
		GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("继续游戏"));

	}
	else
	{
		GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("暂停游戏"));

	}

	m_bPause=!m_bPause;
	
	InvalidateRect(m_rtGameRect, FALSE);//调用OnPaint
}


void CGameDlg::OnBnClickedButton5()
{
	CHelpDialog dlg;
	dlg.DoModal();
}
