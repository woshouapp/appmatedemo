#pragma once

#ifdef APPMATE_EXPORTS
#define APPMATE_API __declspec(dllexport)
#else
#define APPMATE_API __declspec(dllimport)
#endif

enum UpdateFlag
{
	UF_NONE = 0,//����Ҫ����
	UF_FORCE = 1,//ǿ������
	UF_SILENT = 2,//��Ĭ����
	UF_OPTION = 3,//��ѡ����
};

class CUpdateCallback
{
public:
	//CUpdateCallback();
	//~CUpdateCallback();

	virtual void OnCheckResult(int nUpdateFlag, const char* szVersion
		, const char* szVersionDescription, bool bManual) = 0;

	virtual void DownloadProgress(int nCur, int nTotal, int nSpeed) = 0;

	virtual void OnDownloadFinish(int nTipLevel) = 0;
};

//
//#ifdef __cplusplus
//extern "C"{
//#endif
//
APPMATE_API void AppMate_Init(const char* szAppID, CUpdateCallback* pUpdateCallback);
	//, const char* szVersion = nullptr);//Ҫ����Ӧ���Լ����汾�ţ���Ϊ��һ���Ե�ǰexe�İ汾��Ϊ׼

APPMATE_API void AppMate_UnInit();

//ֻ��һ�������ļ�����������Ϣ
//ֻ��һ����¼���Ͳ������ݿ���
APPMATE_API void AppMate_CheckUpdate();

APPMATE_API void AppMate_UpdateNext();//��һ��

//////////////////////////////////////////////////////////////////////////
APPMATE_API void AppMate_Report(const char* szEvent, const char* szValue);

//
//#ifdef __cplusplus
//};
//#endif
