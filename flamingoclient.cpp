#include "flamingoclient.h"
#include "net/stdafx.h"
#include "Utils/inifile.h"
#include "login.h"
#include "net/iuprotocoldata.h"
#include "Utils/iulog.h"
//#include "UpdateDlg.h"
#include "Utils/encodeutil.h"
#include "UserData/usersessiondata.h"
//#include "CustomMsgDef.h"
#include "startup.h"
#include "Utils/file2.h"
#include "Utils/path.h"
#include "net/Msg.h"
#include <sstream>

CFlamingoClient& CFlamingoClient::GetInstance()
{
    LOG_INFO("CFlamingoClient& CFlamingoClient::GetInstance()");
    static CFlamingoClient client;
    return client;
}


CFlamingoClient::CFlamingoClient(void)
{
    LOG_INFO("CFlamingoClient::CFlamingoClient(void)");
    m_ServerTime = 0;

    m_bNetworkAvailable = TRUE;

    m_hwndRegister = NULL;
    m_hwndFindFriend = NULL;
    m_hwndModifyPassword = NULL;

    m_bBuddyIDsAvailable = FALSE;
    m_bBuddyListAvailable = FALSE;

    m_nGroupCount = 0;
    m_bGroupInfoAvailable = FALSE;
    m_bGroupMemberInfoAvailable = FALSE;

    m_SendMsgThread.m_lpUserMgr = &m_UserMgr;
    m_RecvMsgThread.m_lpUserMgr = &m_UserMgr;
    m_RecvMsgThread.m_pFMGClient = this;
//    m_FileTask.m_lpFMGClient = this;
//    m_ImageTask.m_lpFMGClient = this;
}

CFlamingoClient::~CFlamingoClient(void)
{

}

