#include "stdafx.h"
#include "UpdateCallbackImpl.h"

#include "MsgDefine.h"
#include "AppmateDemo.h"

CUpdateCallbackImpl::CUpdateCallbackImpl()
{
}


CUpdateCallbackImpl::~CUpdateCallbackImpl()
{
}

void CUpdateCallbackImpl::OnCheckResult(int nUpdateFlag, const char* szVersion
	, const char* szVersionDescription, bool bManual)
{
	if (nUpdateFlag == UF_FORCE || nUpdateFlag == UF_OPTION)
	{
		if (szVersion != nullptr && szVersionDescription != nullptr)
		{
			std::string* strVersion = new std::string(szVersion);
			std::string* strDesc = new std::string(szVersionDescription);
			theApp.GetMainWnd()->PostMessage(MSG_CHECKRESULT, (WPARAM)strVersion, (LPARAM)strDesc);
		}
	}

	if (nUpdateFlag == UF_FORCE || nUpdateFlag == UF_SILENT)
	{
		AppMate_UpdateNext();
	}
}

//完全由使用者实现
void CUpdateCallbackImpl::DownloadProgress(int nCur, int nTotal, int nSpeed)
{
	double nPercent = 0.0;
	if (nTotal != 0)
	{
		nPercent = double(nCur) / nTotal;
	}
	if (theApp.GetMainWnd() != NULL)
	{
		theApp.GetMainWnd()->PostMessage(MSG_DOWNLOADPROGRESS, WPARAM(nPercent * 100), nSpeed);
	}
}

void CUpdateCallbackImpl::OnDownloadFinish(int nTipLevel)
{
	if (nTipLevel == UF_FORCE)//强制升级，不提示
	{
		AppMate_UpdateNext();
		//theApp.GetMainWnd()->PostMessage(MSG_DOWNLOADFINISH, 0, 0);
		theApp.GetMainWnd()->PostMessage(WM_QUIT, 0, 0);
	}
}
