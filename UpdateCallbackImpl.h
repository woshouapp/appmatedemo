#pragma once

#include "AppMate.h"

class CUpdateCallbackImpl:public CUpdateCallback
{
public:
	CUpdateCallbackImpl();
	~CUpdateCallbackImpl();


	virtual void OnCheckResult(int nUpdateFlag, const char* szVersion
		, const char* szVersionDescription, bool bManual);

	virtual void DownloadProgress(int nCur, int nTotal, int nSpeed);

	virtual void OnDownloadFinish(int nTipLevel);

};

