
// AppmateDemoDlg.h : 头文件
//

#pragma once

#include <memory>
#include "MsgDefine.h"

class CUpdateCallbackImpl;

// CAppmateDemoDlg 对话框
class CAppmateDemoDlg : public CDialogEx
{
// 构造
public:
	CAppmateDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_APPMATEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
