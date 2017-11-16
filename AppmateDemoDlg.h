
// AppmateDemoDlg.h : ͷ�ļ�
//

#pragma once

#include <memory>
#include "MsgDefine.h"

class CUpdateCallbackImpl;

// CAppmateDemoDlg �Ի���
class CAppmateDemoDlg : public CDialogEx
{
// ����
public:
	CAppmateDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_APPMATEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg LRESULT CheckHandler(WPARAM, LPARAM);
	afx_msg LRESULT ProgressHandler(WPARAM, LPARAM);
	afx_msg LRESULT DownloadFinishHandler(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

private:
	std::shared_ptr<CUpdateCallbackImpl> m_UpdateCallback;
public:
	afx_msg void OnBnClickedButton1();
};
