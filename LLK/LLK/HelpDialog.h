#pragma once


// CHelpDialog �Ի���

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHelpDialog();

	virtual BOOL OnInitDialog();

    // �Ի�������
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CDC m_dcMem;//�ڴ�DC
	CDC m_dcMem2;
	CDC m_dcHelp;//��ͣͼƬ���ڴ�DC
	CDC m_dcHelp2;
	CRect m_rtHelp;//
	CRect m_rtHelp2;
	HICON m_hIcon;//ͼ��
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	
	void UpdateHelp(int nPos);
	
};
