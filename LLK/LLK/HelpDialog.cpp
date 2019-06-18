// HelpDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "HelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog �Ի���

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//����ϵͳͼ��
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	CClientDC dc(this);
	
	//����bmpͼƬ��Դ
	HANDLE hbmpHelp=::LoadImage(NULL,_T("theme\\picture\\Help.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcHelp.SelectObject(hbmpHelp);
	
	//�����ڴ�dc��С
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc,rtClient.Width(),rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	 //���ư�ɫ����
	m_dcMem.BitBlt(0,0,rtClient.Width(),rtClient.Height(),NULL,0,0,WHITENESS);

	//���ư�����Ϣ
	UpdateHelp(0);

	//���ù�������Χ
	CBitmap bmpHelp;
	bmpHelp.Attach(hbmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);  //���bmpHelp��λͼ�ṹ
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0,bmpInfo.bmHeight);
	///////////////////
	//����bmpͼƬ��Դ
	HANDLE hbmpHelp2=::LoadImage(NULL,_T("theme\\picture\\Help2.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcHelp2.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcHelp2.SelectObject(hbmpHelp2);
	
	m_dcMem2.CreateCompatibleDC(&m_dcHelp2);
	CBitmap bmpMem2;
	bmpMem2.CreateCompatibleBitmap(&m_dcHelp2,500,40);
	m_dcMem2.SelectObject(&bmpMem2);
	InvalidateRect(m_rtHelp2,FALSE);
	///////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	int pos = pScrollBar->GetScrollPos();
	int nMinPos;
	int nMaxPos;
	pScrollBar->GetScrollRange(&nMinPos, &nMaxPos);
	switch(nSBCode)
	{
	case SB_LINEUP:   //���ϰ�ť
		pos-=1;
		break;
	case SB_LINEDOWN:  //���°�ť
		pos+=1;
		break;
	case SB_PAGEUP:   //���Ϸ�ҳ
		pos-=10;
		break;
	case SB_PAGEDOWN:  //���·�ҳ
		pos+=10;
		break;
	case SB_TOP:    //����
		pos=nMinPos;
		break;
	case SB_BOTTOM:  //�ײ�
		pos=nMaxPos;
		break;
	case SB_THUMBPOSITION:   //����ڻ�����
		pos=nPos;
		break;
	default:
		break;

	}

	//���û������뵱ǰ���ֵ
	pScrollBar->SetScrollPos(pos,TRUE);
	//���°�����Ϣ
	UpdateHelp(pos);


	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);

}

void CHelpDialog::UpdateHelp(int nPos)
{
	//���ػ������Ƴɰ�ɫ
	m_dcMem.BitBlt(m_rtHelp.left,m_rtHelp.top,m_rtHelp.Width(),m_rtHelp.Height(),NULL,0,0,WHITENESS);
	//���Ƶ�ǰ��İ�����Ϣ
	m_dcMem.BitBlt(m_rtHelp.left,m_rtHelp.top,m_rtHelp.Width(),m_rtHelp.Height(),&m_dcHelp,0,nPos,SRCCOPY);
	
	
	//���½���
	InvalidateRect(m_rtHelp,FALSE);
	
}

void CHelpDialog::OnPaint()//��ͼ����
{

	CPaintDC dc(this);

	// TODO: �ڴ˴������Ϣ����������CDialogEx::OnPaint();

	
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	
	dc.BitBlt(0,0,rtClient.Width(),rtClient.Height(),&m_dcMem,0,0,SRCCOPY);
	
	dc.BitBlt(m_rtHelp2.left,m_rtHelp2.top,500,40,&m_dcHelp2,0,0,SRCCOPY);//��ͼλ��

}