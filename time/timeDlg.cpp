
// timeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "time.h"
#include "timeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtimeDlg �Ի���

BEGIN_DHTML_EVENT_MAP(CtimeDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



CtimeDlg::CtimeDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CtimeDlg::IDD, CtimeDlg::IDH, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtimeDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_kill1, &CtimeDlg::OnBnClickedkill1)
	ON_BN_CLICKED(IDC_kill2, &CtimeDlg::OnBnClickedkill2)
	ON_BN_CLICKED(IDC_ClickedDraw, &CtimeDlg::OnBnClickedClickeddraw)
END_MESSAGE_MAP()


// CtimeDlg ��Ϣ�������

BOOL CtimeDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	SetTimer(1,3000,NULL);
	SetTimer(2,5000,NULL);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtimeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CtimeDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CtimeDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}


void CtimeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC;
	CPen newpen,*oldpen;
	newpen.CreatePen(PS_SOLID,10,RGB(0,0,255));
    pDC=GetDC();
	oldpen=pDC->SelectObject(&newpen);
	pDC->MoveTo(0,0);
	pDC->LineTo(point.x,point.y);
	pDC->SelectObject(oldpen);
	CDHtmlDialog::OnLButtonUp(nFlags, point);
}


void CtimeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACE("x=%d,y=%d\n",point.x,point.y);
	if(point.x<10&&point.y<10)
		MessageBox(L"Hi");
	CDHtmlDialog::OnMouseMove(nFlags, point);
}


void CtimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==1)
		MessageBox(L"Hi Timer 1111");
	if(nIDEvent==2)
		MessageBox(L"Hi Timer 222");
	CDHtmlDialog::OnTimer(nIDEvent);
}


void CtimeDlg::OnBnClickedkill1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
}


void CtimeDlg::OnBnClickedkill2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(2);
}


void CtimeDlg::OnBnClickedClickeddraw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDC *pDC;
	CPen newpen,*oldpen;
	newpen.CreatePen(PS_SOLID,10,RGB(0,0,255));
    pDC=GetDC();
	oldpen=pDC->SelectObject(&newpen);
	pDC->MoveTo(0,0);
	pDC->LineTo(100,100);
	pDC->SelectObject(oldpen);
}
