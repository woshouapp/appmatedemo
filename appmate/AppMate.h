#pragma once

#ifdef APPMATE_EXPORTS
#define APPMATE_API __declspec(dllexport)
#else
#define APPMATE_API __declspec(dllimport)
#endif

enum UpdateFlag
{
	UF_NONE = 0,//不需要升级
	UF_FORCE = 1,//强制升级
	UF_SILENT = 2,//静默升级
	UF_OPTION = 3,//可选升级
};

class CUpdateCallback
{
public:
	virtual void OnCheckResult(int nUpdateFlag, const char* szVersion
		, const char* szVersionDescription, bool bManual) = 0;

	virtual void DownloadProgress(int nCur, int nTotal, int nSpeed) = 0;

	virtual void OnDownloadFinish(int nTipLevel) = 0;
};

APPMATE_API void AppMate_Init(const char* szAppID, CUpdateCallback* pUpdateCallback);

APPMATE_API void AppMate_UnInit();

APPMATE_API void AppMate_CheckUpdate();

APPMATE_API void AppMate_UpdateNext();

APPMATE_API void AppMate_Report(const char* szEvent, const char* szValue);
