
// timeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "time.h"
#include "timeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CtimeDlg 对话框

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


// CtimeDlg 消息处理程序

BOOL CtimeDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	SetTimer(1,3000,NULL);
	SetTimer(2,5000,NULL);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtimeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACE("x=%d,y=%d\n",point.x,point.y);
	if(point.x<10&&point.y<10)
		MessageBox(L"Hi");
	CDHtmlDialog::OnMouseMove(nFlags, point);
}


void CtimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==1)
		MessageBox(L"Hi Timer 1111");
	if(nIDEvent==2)
		MessageBox(L"Hi Timer 222");
	CDHtmlDialog::OnTimer(nIDEvent);
}


void CtimeDlg::OnBnClickedkill1()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}


void CtimeDlg::OnBnClickedkill2()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(2);
}


void CtimeDlg::OnBnClickedClickeddraw()
{
	// TODO: 在此添加控件通知处理程序代码
	CDC *pDC;
	CPen newpen,*oldpen;
	newpen.CreatePen(PS_SOLID,10,RGB(0,0,255));
    pDC=GetDC();
	oldpen=pDC->SelectObject(&newpen);
	pDC->MoveTo(0,0);
	pDC->LineTo(100,100);
	pDC->SelectObject(oldpen);
}
