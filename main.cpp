#pragma comment(lib,"ws2_32.lib")
#include "login.h"
#include <QDebug>
#include <Ws2tcpip.h>
#include <QApplication>
#include "Utils/iulog.h"
#include "performancecounter.h"
#include "startup.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;

//    WORD sockVersion = MAKEWORD(2, 2);
//    WSADATA data;
//    if (WSAStartup(sockVersion, &data) != 0)
//    {
//        return 0;
//    }

//    SYSTEMTIME st = {0};
//    ::GetLocalTime(&st);

//    DWORD dwProcessId = ::GetCurrentProcessId();
//    TCHAR szLogFileName[MAX_PATH] = {0};
//    _stprintf_s(szLogFileName, MAX_PATH, _T("%s\\Logs\\%04d%02d%02d%02d%02d%02d_%d.log"), g_szHomePath, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, (int32_t)dwProcessId);
//    CIULog::Init(true, false, szLogFileName);

    //    //初始化性能计数器
    //    TCHAR szPerformanceFileName[MAX_PATH] = { 0 };
    //    _stprintf_s(szPerformanceFileName, MAX_PATH, _T("%s\\Logs\\%04d%02d%02d%02d%02d%02d_%d.perf"), g_szHomePath, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, (int32_t)dwProcessId);
    //    CPerformanceCounter::Init(true, szPerformanceFileName);

    //    //TODO: 统一到AppConfig类中去
    //    CIniFile iniFile;
    //    CString strIniFilePath(g_szHomePath);
    //    strIniFilePath += _T("config\\flamingo.ini");
    //    bool bNeedClear = true;
    //    if (iniFile.ReadInt(_T("app"), _T("clearexpirelog"), 0, strIniFilePath) == 0)
    //        bNeedClear = false;

    //    if (bNeedClear)
    //    {
    //        //清理过期的日志文件
    //        ClearExpiredLog(_T("log"));
    //        ClearExpiredLog(_T("perf"));
    //    }

    //    //日志级别
    //    int nLogLevel = iniFile.ReadInt(_T("app"), _T("loglevel"), 0, strIniFilePath);
    //    CIULog::SetLevel((LOG_LEVEL)nLogLevel);

    if(!InitSocket())
        return 0;

//    UnInitSocket();

//    CIULog::Uninit();


    //创建Users目录
//    CString strAppPath(g_szHomePath);
//    CString strUsersDirectory(strAppPath);
//    strUsersDirectory += _T("Users");
//    if(!Hootina::CPath::IsDirectoryExist(strUsersDirectory))
//        Hootina::CPath::CreateDirectory(strUsersDirectory);

//    // 加载系统表情列表
//    tstring strFileName = Hootina::CPath::GetAppPath() + _T("Face\\FaceConfig.xml");
//    m_FaceList.LoadConfigFile(strFileName.c_str());

//    // 加载登录帐号列表
//    strFileName = Hootina::CPath::GetAppPath()+_T("Users\\LoginAccountList.dat");
//    m_LoginAccountList.LoadFile(strFileName.c_str());

   // login.DoLogin();

    qDebug() << "test ... " << endl;

    w.show();
    return a.exec();
}
