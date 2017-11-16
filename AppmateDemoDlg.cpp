
// AppmateDemoDlg.cpp : ʵ���ļ�
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


// CAppmateDemoDlg �Ի���



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


// CAppmateDemoDlg ��Ϣ�������

BOOL CAppmateDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_UpdateCallback = std::make_shared<CUpdateCallbackImpl>();

	AppMate_Init("e286866dd45b740caef57163f9455a24", m_UpdateCallback.get());

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAppmateDemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AppMate_Report("reporttest", "");
}
