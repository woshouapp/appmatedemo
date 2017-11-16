
// AppmateDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AppmateDemo.h"
#include "AppmateDemoDlg.h"
#include "afxdialogex.h"

#include "resource.h"

#include "UpdateCallbackImpl.h"

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


// CAppmateDemoDlg 对话框



CAppmateDemoDlg::CAppmateDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppmateDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAppmateDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAppmateDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(MSG_CHECKRESULT, CheckHandler)
	ON_MESSAGE(MSG_DOWNLOADPROGRESS, ProgressHandler)
	ON_MESSAGE(MSG_DOWNLOADFINISH, DownloadFinishHandler)
	ON_BN_CLICKED(IDC_BUTTON1, &CAppmateDemoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAppmateDemoDlg 消息处理程序

BOOL CAppmateDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_UpdateCallback = std::make_shared<CUpdateCallbackImpl>();

	AppMate_Init("e286866dd45b740caef57163f9455a24", m_UpdateCallback.get());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAppmateDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAppmateDemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAppmateDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CAppmateDemoDlg::CheckHandler(WPARAM wParam, LPARAM lParam)
{
	shared_ptr<std::string> pstrVersion((std::string*)wParam);
	shared_ptr<std::string> pstrDesc((std::string*)lParam);

	SetDlgItemText(IDC_STATIC_VERSION, (LPCTSTR)CA2W(pstrVersion->c_str(), CP_UTF8));
	SetDlgItemText(IDC_EDIT_DESC, (LPCTSTR)CA2W(pstrDesc->c_str(), CP_UTF8));

	return 0;
}

LRESULT CAppmateDemoDlg::ProgressHandler(WPARAM wParam, LPARAM lParam)
{
	CProgressCtrl* pProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	if (pProgress != nullptr)
	{
		pProgress->SetPos(int(wParam));
	}
	CString strSpeed;
	strSpeed.Format(_T("%d KB/s"), lParam/1024);
	SetDlgItemText(IDC_STATIC_SPEED, strSpeed);
	return 0;
}
LRESULT CAppmateDemoDlg::DownloadFinishHandler(WPARAM wParam, LPARAM lParam)
{
	AppMate_UpdateNext();
	return 0;
}


void CAppmateDemoDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	AppMate_Report("reporttest", "");
}
