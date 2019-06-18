// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include"GameControl.h"

// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{	m_ptGameTop.x = 50;
	m_ptGameTop.y = 100;

	//��ʼ��ͼƬԪ�ش�С
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//��ʼ����Ϸ��������
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	//��ʼ��ͼ��ѡ��״̬
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
	
	//��õ�ǰ�Ի������Ƶ����
	CClientDC dc(this);

	//��������Ƶ���ݼ��ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&dc);

	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(Backbmp);

	//��ʼ���ڴ�DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 1100, 660);
	m_dcMem.SelectObject(&bmpMem);

	//hu���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, 1100, 660, &m_dcBG, 0, 0, SRCCOPY);

}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0,0,1100,660,&m_dcMem,0,0,SRCCOPY);
	// TODO: �ڴ˴������Ϣ����������
	if (m_bPause)
	{
		dc.BitBlt(m_rtGameRect.left ,
			m_rtGameRect.top , m_rtGameRect.Width() ,
			m_rtGameRect.Height() , &m_dcCache, 0, 0, SRCCOPY);
	}
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
			int nInfo = m_gameControl.GetElement(i, j);       //��ǰԪ��ͼƬ����ֵ
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
	
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcPause.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcPause.SelectObject(bmp1);

	
	m_dcCache.CreateCompatibleDC(&m_dcPause);
	
	CBitmap bmpMem1;
    bmpMem1.CreateCompatibleBitmap(&m_dcPause,690,590);

	m_dcCache.SelectObject(&bmpMem1);
	m_dcCache.BitBlt(0,0,690,590,&m_dcPause,0,0,SRCCOPY);//
}

void CGameDlg::OnClickedButton1()//��ʼ��Ϸ��ť
{
	//��ʼ����Ϸ��ͼ
	m_gameControl.StartGame();

	m_bPlaying=true;


	this->GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);//��ֹ��ť

	m_GameProgress.SetRange(0, 60 * 3);    //��ʼ��Χ
	m_GameProgress.SetStep(-1);				//��ʼ����
	m_GameProgress.SetPos(60 * 3);         //���ó�ʼֵ
	
	//������ʱ��
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
	//���Ƶ�ǰ����

	//DrawGameTime();//����ʱ���ı�

	UpdateMap();

	InvalidateRect(m_rtGameRect,FALSE);
	
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	

		//���·��
		Vertex avPath[MAX_VERTEX_NUM];

		
		int n;
		//�ж��Ƿ�����
		if(m_gameControl.Link(avPath,n))
		{
			//������ʾ
			DrawTipLine(avPath,n);

			
			//���µ�ͼ
			UpdateMap();

			

		}
		Sleep(200);
		InvalidateRect(m_rtGameRect,FALSE);
	}
	JudgeWin();
	/*if(m_gamecontrol.IsWin(m_GameProgress.GetPos()))
	{

		MessageBox(_T("��ʤ"));
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
	//��ȡDC
	CClientDC dc(this);

	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//������ѡ��DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	//����������
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

	//����ܹ���ͨ��������ʾ��������߲�������Ϸ��ͼ
	Vertex avPath[MAX_VERTEX_NUM];     //���·��
	int nVexnum = 0;      //�������
	if (m_gameControl.Help(avPath, nVexnum))
	{

		//����һ�������ʾ��
		DrawTipFrame(avPath[0].row, avPath[0].col);

		//����һ�������ʾ��
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		//����ʾ��
		DrawTipLine(avPath, nVexnum);

		Sleep(1000);    //�ӳ�
						
		UpdateMap();	//���µ�ͼ

		InvalidateRect(m_rtGameRect, FALSE);    //�ֲ����θ���
	}
	
}


void CGameDlg::OnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_gameControl.Reset();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE); 

}

void CGameDlg::JudgeWin(void)//
{
	BOOL bGameStatus = m_gameControl.IsWin(m_GameProgress.GetPos());
	//�ж��Ƿ������Ϸ
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		//����Ϸ��ʶ��Ϊfalse
		m_bPlaying = false;
		//�رն�ʱ��
		KillTimer(PLAY_TIMER_ID);
		//��ʾ��ʤ
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("��ʤ��"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("���ź���ʱ�䵽�ˣ�"), strTitle);
		}
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
}
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


		if(nIDEvent==PLAY_TIMER_ID&&m_bPlaying&&!m_bPause)
	{
		//��Ϸʱ���һ
		m_GameProgress.StepIt();
		DrawGameTime();//����ʱ���ı�
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
	//int x = ((rect.Width() - size.cx) / 2) + 208;//����
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
	if (str == "��ͣ��Ϸ")
	{
		GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("������Ϸ"));

	}
	else
	{
		GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("��ͣ��Ϸ"));

	}

	m_bPause=!m_bPause;
	
	InvalidateRect(m_rtGameRect, FALSE);//����OnPaint
}


void CGameDlg::OnBnClickedButton5()
{
	CHelpDialog dlg;
	dlg.DoModal();
}
