
    【沃手应用伴侣】是首家支持桌面应用的第三方数据服务组件。提供数据上报统计、自动版本升级等接口，轻松接入，让您不再需要自己开发，更专注应用的业务，释放您的业务能量。

沃手应用伴侣sdk集成

一、获取AppKey
请先到沃手应用伴侣官网（http://www.woshouapp.com/ ）中注册账号，登录可添加新应用，添加完成后系统会自动生成AppKey。
二、配置文件
按VC项目配置，把AppMate的头文件appmate.h及库文件appmatedll.lib所在路径添加到相应配置中，即可使用接口，运行时把AppMate的dll文件appmate.dll和exe文件appmate.exe放到运行目录中，appmate.exe是升级时替换文件所需。
三、接口说明
3.1 概览
沃手应用伴侣现提供数据统计和自动升级两个功能，有5个接口，接口都没有返回值，调用后不再作处理。
3.2 void AppMate_Init(const char* szAppID, CUpdateCallback* pUpdateCallback);
参数：szAppID是从官网生成的AppKey
pUpdateCallback是实现自动升级的回调，需要实现检查结果处理，下载进度及下载完成处理
备注：初始化会自动检查升级及上报启动事件，程序启动时调用，建议在第一个窗口创建完成后调用
3.3 void AppMate_UnInit();
参数：无
备注：程序退出前调用
3.4 void AppMate_CheckUpdate();
参数：无
备注：该接口只作手机检查升级用，如果是自动检查的不需要调用，AppMate_Init默认会自动检查升级。
3.5 void AppMate_UpdateNext();
参数：无
备注：升级下一步，不管是哪种升级方式，只要继续升级，就只要调这个接口。
3.6 void AppMate_Report(const char* szEvent, const char* szValue);
参数：szEvent，上报事件，为空时不上报
szValue，事件值，可选参数
备注：统计上报唯一接口，用于上报自定义事件

四、其它
Sdk中Demo给了简单的使用示例，可参考，如有问题，欢迎联系我们service@woshouapp.com，我们会第一时间回复，欢迎使用沃手应用伴侣，谢谢！

官网：http://www.woshouapp.com/
