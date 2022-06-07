#include "login.h"
#include "ui_login.h"

#include <QTcpSocket>
#include "atlstr.h"
#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <process.h>
#include <QThread>
#include <iostream>

//Login* m_login = nullptr;
LoginThread* m_loginThread= nullptr;
//Login* login = new Login();
Login* login;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    InitUI();

    mainWnd = new MainWindow;
   // m_loginThread = new class LoginThread();

    //connect(m_loginThread, SIGNAL(sigLoginThread()), this, SLOT(test()));

    connect(this, SIGNAL(sigLoginResult(CLoginResult *)), this, SLOT(dealLoginResult(CLoginResult*)));
    connect(this, SIGNAL(sigUpdateUserBasicInfo(UINT)), this, SLOT(dealUpdateBuddyInfo(UINT)));
//    connect(ui->pushButton, &QPushButton::clicked, this, LoginThreadProc());

//    void sigInitBuddyUI(std::vector<CBuddyTeamInfo*> vec, std::map<UINT , BuddyInfo*> map);
//    initBuddyUI(std::vector<CBuddyTeamInfo *> teamVec, std::map<UINT, BuddyInfo *> buddyMap)
    connect(this, SIGNAL(sigInitBuddyUI(std::vector<CBuddyTeamInfo *>, std::map<UINT, BuddyInfo *>)), mainWnd, SLOT(initBuddyUI(std::vector<CBuddyTeamInfo *>, std::map<UINT, BuddyInfo *>)));
    //connect(this, SIGNAL(sigInitUIBuddyPart(std::map<UINT , BuddyInfo*>)), mainWnd, SLOT());

    //GetFriendList();

  //  m_loginThread = new Login();

//    m_loginThread = new class LoginThread();

//    LoginThread = new QThread;
//    //m_login = new Login;
//    //connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(LoginThreadProc()));

//    m_loginThread->moveToThread(LoginThread);
//    LoginThread->start();

}

Login::~Login()
{
    delete ui;
}

void Login::InitUI()
{
    ui->widget_2->hide();
    ui->label_16->hide();
    ui->toolButton_6->hide();
//    ui->toolButton_3->show();
//    ui->toolButton_4->show();
    ui->horizontalWidget->show();
    //窗体风格
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);//WindowStaysOnTopHint窗口顶置
    //窗体透明
    setAttribute(Qt::WA_TranslucentBackground);
    //初始化系统托盘
    systemtrayicon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/lib/qusefdogicon.png");
    //添加图标
    systemtrayicon->setIcon(icon);
    //当鼠标悬浮，显示文字
    systemtrayicon->setToolTip(QObject::trUtf8("Fdog"));
    //显示图标
    menu = new QMenu(this);
    m_pShowAction = new QAction("打开主界面 ");
    m_pCloseAction = new QAction("退出 ");
    menu->addAction(m_pShowAction);
    menu->addSeparator();
    menu->addAction(m_pCloseAction);
    connect(m_pShowAction, SIGNAL(triggered(bool)),this,SLOT(showWidget()));
    connect(m_pCloseAction,SIGNAL(triggered(bool)),this,SLOT(closeWidget()));
    systemtrayicon->setContextMenu(menu);
    systemtrayicon->show();
    //加载动态图
    m_movie = new QMovie(":/lib/mian2.gif");
    m_movie2 = new QMovie(":/lib/mian2.gif");
    //设置动态图大小
    m_si.setWidth(431);
    m_si.setHeight(151);
    m_movie->setScaledSize(m_si);

    m_si2.setWidth(431);
    m_si2.setHeight(331);
    m_movie2->setScaledSize(m_si2);
    //添加动态图
    ui->mian_label->setMovie(m_movie);
    ui->label_3->setMovie(m_movie2);
    //开始动画
    m_movie->start();

    //创建一个action
    searchAction = new QAction(ui->lineEdit_2);
    //填加图标897669vv
    searchAction->setIcon(QIcon(":/lib/suo.png"));
    //表示action所在方位（左侧）。
    ui->lineEdit->addAction(searchAction,QLineEdit::LeadingPosition);

    searchAction_2 = new QAction(ui->lineEdit);
    searchAction_2->setIcon(QIcon(":/lib/jianpan.png"));
    //表示action所在方位（右侧）。
    ui->lineEdit->addAction(searchAction_2,QLineEdit::TrailingPosition);

    searchAction_3 = new QAction(ui->lineEdit);
    searchAction_3->setIcon(QIcon(":/lib/fdog.png"));
    //表示action所在方位（左侧）。
    ui->lineEdit_2->addAction(searchAction_3,QLineEdit::LeadingPosition);

//    m_loginThread = new Login();

//    LoginThread = new QThread;
//    //m_login = new Login;
//    //connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(LoginThreadProc()));

//    this->moveToThread(LoginThread);
//    LoginThread->start();

}

void Login::InitMainUI()
{

}

void Login::DoLogin()

{
//    QThread *runLoginThread = nullptr;
//    runLoginThread = new QThread;

    LOG_INFO("CLoginDlg::DoLogin()  .,.. ");
        HANDLE hLoginThread = (HANDLE)::_beginthreadex(NULL, 0, LoginThreadProc, this, 0, NULL);
        if (hLoginThread != NULL)
            ::CloseHandle(hLoginThread);
}


//QString user = Login::ui->lineEdit->text();
//QString passwd = this->ui->lineEdit_2->text();


UINT Login::LoginThreadProc(void *pParm)
{
    LOG_INFO("Login::LoginThread::run()  ...");
//    Login* m_login;
//    m_login = new Login();

    QString user = "110";
    QString passwd = "123456";

    QByteArray bUser = user.toLatin1();
    char *szUser = bUser.data();
    LOG_INFO("szUser --> %s", szUser);

    QByteArray bPasswd = passwd.toLatin1();
    char *szPassword = bPasswd.data();
    LOG_INFO("szPassword --> %s", szPassword);

//        EncodeUtil::UnicodeToUtf8(this->m_stAccountInfo.szUser, szUser, ARRAYSIZE(szUser));

//        EncodeUtil::UnicodeToUtf8(pLoginDlg->m_stAccountInfo.szPwd, szPassword, ARRAYSIZE(szPassword));

    std::string strReturnData;
    //超时时间设置为3秒
    bool bRet = CIUSocket::GetInstance().Login(szUser, szPassword, 1, online_type_pc_online, 3, strReturnData);
    //bool bRet = true;
    int nRet = LOGIN_FAILED;
    CLoginResult* pLoginResult = new CLoginResult();
    pLoginResult->m_LoginResultCode = LOGIN_FAILED;
    if (bRet)
    {
        //{"code": 0, "msg": "ok", "userid": 8}
        Json::Reader JsonReader;
        Json::Value JsonRoot;
        if (JsonReader.parse(strReturnData, JsonRoot) && !JsonRoot["code"].isNull() && JsonRoot["code"].isInt())
        {
            int nRetCode = JsonRoot["code"].asInt();

            if (nRetCode == 0)
            {
                if (!JsonRoot["userid"].isInt() || !JsonRoot["username"].isString() || !JsonRoot["nickname"].isString() ||
                    !JsonRoot["facetype"].isInt() || !JsonRoot["gender"].isInt() || !JsonRoot["birthday"].isInt() ||
                    !JsonRoot["signature"].isString() || !JsonRoot["address"].isString() ||
                    !JsonRoot["customface"].isString() || !JsonRoot["phonenumber"].isString() ||
                    !JsonRoot["mail"].isString())
                {
                    LOG_ERROR(_T("login failed, login response json is invalid, json=%s"), strReturnData.c_str());
                    pLoginResult->m_LoginResultCode = LOGIN_FAILED;
                }
                else
                {
                    pLoginResult->m_LoginResultCode = 0;
                    pLoginResult->m_uAccountID = JsonRoot["userid"].asInt();
                    strcpy_s(pLoginResult->m_szAccountName, ARRAYSIZE(pLoginResult->m_szAccountName), JsonRoot["username"].asCString());
                    strcpy_s(pLoginResult->m_szNickName, ARRAYSIZE(pLoginResult->m_szNickName), JsonRoot["nickname"].asCString());
                    //pLoginResult->m_nStatus = JsonRoot["status"].asInt();
                    pLoginResult->m_nFace = JsonRoot["facetype"].asInt();
                    pLoginResult->m_nGender = JsonRoot["gender"].asInt();
                    pLoginResult->m_nBirthday = JsonRoot["birthday"].asInt();
                    strcpy_s(pLoginResult->m_szSignature, ARRAYSIZE(pLoginResult->m_szSignature), JsonRoot["signature"].asCString());
                    strcpy_s(pLoginResult->m_szAddress, ARRAYSIZE(pLoginResult->m_szAddress), JsonRoot["address"].asCString());
                    strcpy_s(pLoginResult->m_szCustomFace, ARRAYSIZE(pLoginResult->m_szCustomFace), JsonRoot["customface"].asCString());
                    strcpy_s(pLoginResult->m_szPhoneNumber, ARRAYSIZE(pLoginResult->m_szPhoneNumber), JsonRoot["phonenumber"].asCString());
                    strcpy_s(pLoginResult->m_szMail, ARRAYSIZE(pLoginResult->m_szMail), JsonRoot["mail"].asCString());
                }
            }
            else if (nRetCode == 102)
                pLoginResult->m_LoginResultCode = LOGIN_UNREGISTERED;
            else if (nRetCode == 103)
                pLoginResult->m_LoginResultCode = LOGIN_PASSWORD_ERROR;
            else
                pLoginResult->m_LoginResultCode = LOGIN_FAILED;
        }
    }

    emit login->sigLoginResult(pLoginResult);
   //emit sigUpdateUserBasicInfo(m_UserMgr.m_UserInfo.m_uUserID);

    return 1;
}

bool Login::InitNetThreads()
{
//    LOG_INFO("CFlamingoClient::InitNetThreads()");
//    CIUSocket::GetInstance().SetRecvMsgThread(&m_RecvMsgThread);
//    CIUSocket::GetInstance().Init();

//    m_SendMsgThread.Start();
//    m_RecvMsgThread.Start();

    return true;
}

void Login::GetFriendList()
{
    m_UserMgr.m_UserInfo.m_uUserID = 110;
    CUserBasicInfoRequest* pBasicInfoRequest = new CUserBasicInfoRequest();
    pBasicInfoRequest->m_setAccountID.insert(m_UserMgr.m_UserInfo.m_uUserID);
    m_SendMsgThread->AddItem(pBasicInfoRequest);
}

void Login::LoadUserConfig()
{
//    if(m_UserMgr.m_UserInfo.m_strAccount.empty())
//            return;

//    PCTSTR pszAccount = m_UserMgr.m_UserInfo.m_strAccount.c_str();

//    TCHAR szConfigPath[MAX_PATH] = {0};
//    _stprintf_s(szConfigPath, MAX_PATH, _T("%sUsers\\%s\\%s.cfg"), g_szHomePath, pszAccount, pszAccount);

    //    m_UserConfig.LoadConfig(szConfigPath);
}

CBuddyInfo *Login::GetUserInfo(UINT uAccountID)
{
    if(uAccountID==0 || uAccountID==m_UserMgr.m_UserInfo.m_uUserID)
        return &m_UserMgr.m_UserInfo;

    CBuddyTeamInfo* pTeamInfo = nullptr;
    CBuddyInfo* pBuddyInfo = nullptr;
    for(size_t i=0; i < m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo.size(); ++i)
    {
        pTeamInfo = m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo[i];
        for(size_t j=0; j<pTeamInfo->m_arrBuddyInfo.size(); ++j)
        {
            pBuddyInfo = pTeamInfo->m_arrBuddyInfo[j];
            if(uAccountID == pBuddyInfo->m_uUserID)
                return pBuddyInfo;
        }
    }


    CGroupInfo* pGroupInfo = NULL;
    for(size_t i=0; i<m_UserMgr.m_GroupList.m_arrGroupInfo.size(); ++i)
    {
        pGroupInfo = m_UserMgr.m_GroupList.m_arrGroupInfo[i];
        for(size_t j=0; j<pGroupInfo->m_arrMember.size(); ++j)
        {
            pBuddyInfo = pGroupInfo->m_arrMember[j];
            if(uAccountID == pBuddyInfo->m_uUserID)
                return pBuddyInfo;
        }
    }

    return nullptr;
}

long Login::GetStatus()
{
    return m_UserMgr.m_UserInfo.m_nStatus;
}

void Login::CreateEssentialDirectories()
{
    LOG_INFO("Login::CreateEssentialDirectories() ....  ");
    CString strAppPath(g_szHomePath);

    CString strUsersDirectory(strAppPath);
    strUsersDirectory += _T("Users");
    if(!Hootina::CPath::IsDirectoryExist(strUsersDirectory))
    {
        LOG_INFO("Directory1 Not Exist  ... ");
        Hootina::CPath::CreateDirectory(strUsersDirectory);
    }

    CString strCurrentUserDirectory;
    strCurrentUserDirectory.Format(_T("%s\\%s"), (LPCTSTR)strUsersDirectory, m_UserMgr.m_UserInfo.m_strAccount.c_str());

    if(!Hootina::CPath::IsDirectoryExist(strCurrentUserDirectory))
    {
        LOG_INFO("Directory2 Not Exist  ... ");
        Hootina::CPath::CreateDirectory(strCurrentUserDirectory);
    }

    CString strChatImagesDirectory;
    strChatImagesDirectory.Format(_T("%s\\ChatImage\\"), (LPCTSTR)strCurrentUserDirectory);
    if(!Hootina::CPath::IsDirectoryExist(strChatImagesDirectory))
        Hootina::CPath::CreateDirectory(strChatImagesDirectory);

    CString strUserThumbDirectory;
    strUserThumbDirectory.Format(_T("%s\\UserThumb\\"), (LPCTSTR)strCurrentUserDirectory);
    if(!Hootina::CPath::IsDirectoryExist(strUserThumbDirectory))
        Hootina::CPath::CreateDirectory(strUserThumbDirectory);
}

std::string Login::TCHAR2STRING(TCHAR *STR)
{
    int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
    char* chRtn = new char[iLen*sizeof(char)];
    WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
    std::string str(chRtn);
    delete chRtn;
    return str;
}

//Login *Login::GetInstance()
//{
//    if(nullptr == m_login)
//    {
//        m_login = new Login();
//    }

//    return m_login;
//}

//void Login::run()
//{
//    LoginThreadProc();
//}

void Login::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    QPixmap pixmap(":/lib/background.png");
    qDrawBorderPixmap(&painter, this->rect(), QMargins(0, 0, 0, 0), pixmap);
    QRect rect(this->rect().x()+8, this->rect().y()+8, this->rect().width()-16, this->rect().height()-16);
    painter.fillRect(rect, QColor(255, 255, 255));
}

void Login::mousePressEvent(QMouseEvent *event)
{
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    last = event->globalPos();
}

void Login::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
        {
            int dx = event->globalX() - last.x();
            int dy = event->globalY() - last.y();
            last = event->globalPos();
            move(x()+dx, y()+dy);
        }
}

void Login::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
    isPressedWidget = false; // 鼠标松开时，置为false
}

void Login::on_pushButton_clicked()
{
    LOG_INFO("Login::on_pushButton_clicked() ... ");

//    m_loginThread = new class LoginThread();

//    m_loginThread->start();10

    //LoginThread = new QThread;
    //m_login = new Login;
    //connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(LoginThreadProc()));

   // m_loginThread->moveToThread(LoginThread);
    //LoginThread->start();
    LoginThreadProc();
}

void Login::showWidget()
{
    this->show();
}

void Login::closeWidget()
{
    systemtrayicon->hide();
    this->close();
}

void Login::LoginThreadProc()
{
    LOG_INFO("Login::LoginThread::run()  ...");
//    Login* m_login;
//    m_login = new Login();

    QString user = this->ui->lineEdit->text();
    QString passwd = this->ui->lineEdit_2->text();

    QByteArray bUser = user.toLatin1();
    char *szUser = bUser.data();
    LOG_INFO("szUser --> %s", szUser);

    QByteArray bPasswd = passwd.toLatin1();
    char *szPassword = bPasswd.data();
    LOG_INFO("szPassword --> %s", szPassword);

//        EncodeUtil::UnicodeToUtf8(this->m_stAccountInfo.szUser, szUser, ARRAYSIZE(szUser));

//        EncodeUtil::UnicodeToUtf8(pLoginDlg->m_stAccountInfo.szPwd, szPassword, ARRAYSIZE(szPassword));

    std::string strReturnData;
    //超时时间设置为3秒
    bool bRet = CIUSocket::GetInstance().Login(szUser, szPassword, 1, online_type_pc_online, 3, strReturnData);
    //bool bRet = true;
    int nRet = LOGIN_FAILED;
    CLoginResult* pLoginResult = new CLoginResult();
    pLoginResult->m_LoginResultCode = LOGIN_FAILED;
    if (bRet)
    {
        //{"code": 0, "msg": "ok", "userid": 8}
        Json::Reader JsonReader;
        Json::Value JsonRoot;
        if (JsonReader.parse(strReturnData, JsonRoot) && !JsonRoot["code"].isNull() && JsonRoot["code"].isInt())
        {
            int nRetCode = JsonRoot["code"].asInt();

            if (nRetCode == 0)
            {
                if (!JsonRoot["userid"].isInt() || !JsonRoot["username"].isString() || !JsonRoot["nickname"].isString() ||
                    !JsonRoot["facetype"].isInt() || !JsonRoot["gender"].isInt() || !JsonRoot["birthday"].isInt() ||
                    !JsonRoot["signature"].isString() || !JsonRoot["address"].isString() ||
                    !JsonRoot["customface"].isString() || !JsonRoot["phonenumber"].isString() ||
                    !JsonRoot["mail"].isString())
                {
                    LOG_ERROR(_T("login failed, login response json is invalid, json=%s"), strReturnData.c_str());
                    pLoginResult->m_LoginResultCode = LOGIN_FAILED;
                }
                else
                {
                    pLoginResult->m_LoginResultCode = 0;
                    pLoginResult->m_uAccountID = JsonRoot["userid"].asInt();
                    strcpy_s(pLoginResult->m_szAccountName, ARRAYSIZE(pLoginResult->m_szAccountName), JsonRoot["username"].asCString());
                    strcpy_s(pLoginResult->m_szNickName, ARRAYSIZE(pLoginResult->m_szNickName), JsonRoot["nickname"].asCString());
                    //pLoginResult->m_nStatus = JsonRoot["status"].asInt();
                    pLoginResult->m_nFace = JsonRoot["facetype"].asInt();
                    pLoginResult->m_nGender = JsonRoot["gender"].asInt();
                    pLoginResult->m_nBirthday = JsonRoot["birthday"].asInt();
                    strcpy_s(pLoginResult->m_szSignature, ARRAYSIZE(pLoginResult->m_szSignature), JsonRoot["signature"].asCString());
                    strcpy_s(pLoginResult->m_szAddress, ARRAYSIZE(pLoginResult->m_szAddress), JsonRoot["address"].asCString());
                    strcpy_s(pLoginResult->m_szCustomFace, ARRAYSIZE(pLoginResult->m_szCustomFace), JsonRoot["customface"].asCString());
                    strcpy_s(pLoginResult->m_szPhoneNumber, ARRAYSIZE(pLoginResult->m_szPhoneNumber), JsonRoot["phonenumber"].asCString());
                    strcpy_s(pLoginResult->m_szMail, ARRAYSIZE(pLoginResult->m_szMail), JsonRoot["mail"].asCString());
                }
            }
            else if (nRetCode == 102)
                pLoginResult->m_LoginResultCode = LOGIN_UNREGISTERED;
            else if (nRetCode == 103)
                pLoginResult->m_LoginResultCode = LOGIN_PASSWORD_ERROR;
            else
                pLoginResult->m_LoginResultCode = LOGIN_FAILED;
        }
    }

    emit sigLoginResult(pLoginResult);
   // emit sigUpdateUserBasicInfo(m_UserMgr.m_UserInfo.m_uUserID);
}

//class CLoginResult : public CNetData
//{
//public:
//    CLoginResult();
//    ~CLoginResult();
//public:
//    long m_LoginResultCode;
//    UINT m_uAccountID;
//    char m_szAccountName[32];
//    char m_szNickName[32];
//    char m_szSignature[256];
//    long m_nFace;
//    char m_szCustomFace[64];
//    int  m_nGender;
//    int  m_nBirthday;
//    char m_szAddress[512];
//    char m_szPhoneNumber[64];
//    char m_szMail[256];
//    long m_nStatus;
//};

void Login::dealLoginResult(CLoginResult *pLoginResult)
{
    LOG_INFO(" Login::dealLoginResult(CLoginResult *pLoginResult)");

    if(pLoginResult == nullptr)
        return;

    long nLoginResultCode = pLoginResult->m_LoginResultCode;
    UINT uAccountID = pLoginResult->m_uAccountID;

    if(uAccountID > 0)
            m_UserMgr.m_UserInfo.m_uUserID = uAccountID;

    switch(nLoginResultCode)
    {
    case LOGIN_SUCCESS:
    {
        m_UserMgr.m_UserInfo.m_nStatus = STATUS_ONLINE;
        TCHAR szAccountName[64] = {0};
        EncodeUtil::Utf8ToUnicode(pLoginResult->m_szAccountName, szAccountName, ARRAYSIZE(szAccountName));
        m_UserMgr.m_UserInfo.m_strAccount = szAccountName;
        TCHAR szNickName[64] = { 0 };
        EncodeUtil::Utf8ToUnicode(pLoginResult->m_szNickName, szNickName, ARRAYSIZE(szNickName));
        m_UserMgr.m_UserInfo.m_strNickName = szNickName;
        m_UserMgr.m_UserInfo.m_nFace = pLoginResult->m_nFace;
        m_UserMgr.m_UserInfo.m_nGender = pLoginResult->m_nGender;
        m_UserMgr.m_UserInfo.m_nBirthday = pLoginResult->m_nBirthday;

        TCHAR szSignature[512] = { 0 };
        EncodeUtil::Utf8ToUnicode(pLoginResult->m_szSignature, szSignature, ARRAYSIZE(szSignature));
        m_UserMgr.m_UserInfo.m_strSign = szSignature;

        TCHAR szAddress[512] = { 0 };
        EncodeUtil::Utf8ToUnicode(pLoginResult->m_szAddress, szAddress, ARRAYSIZE(szAddress));
        m_UserMgr.m_UserInfo.m_strAddress = szAddress;

        TCHAR szPhoneNumber[64] = { 0 };
        EncodeUtil::Utf8ToUnicode(pLoginResult->m_szPhoneNumber, szPhoneNumber, ARRAYSIZE(szPhoneNumber));
        m_UserMgr.m_UserInfo.m_strMobile = szPhoneNumber;

        TCHAR szMail[512] = { 0 };
        EncodeUtil::Utf8ToUnicode(pLoginResult->m_szMail, szMail, ARRAYSIZE(szMail));
        m_UserMgr.m_UserInfo.m_strEmail = szMail;

        m_UserMgr.m_UserInfo.m_strCustomFaceName = pLoginResult->m_szCustomFace;

        m_FMGClient = new CFlamingoClient();
        m_FMGClient->InitNetThreads();


//        CIUSocket::GetInstance().SetRecvMsgThread(m_RecvMsgThread);
//        CIUSocket::GetInstance().Init();

//        m_SendMsgThread->Start();
//        m_RecvMsgThread->Start();

        CIniFile iniFile;
        CString strIniFile;
        strIniFile.Format(_T("%sconfig\\flamingo.ini"), g_szHomePath);

        if (iniFile.ReadInt(_T("server"), _T("enablereconnect"), 1, strIniFile) != 0)
            m_bEnableReconnect = true;
        else
            m_bEnableReconnect = false;

        //如果都不重连，就没必要读取重连时间间隔了
       if (m_bEnableReconnect)
       {
           m_uReconnectInterval = iniFile.ReadInt(_T("server"), _T("reconnectinterval"), 5000, strIniFile);
           if (m_uReconnectInterval <= 0)
               m_uReconnectInterval = 5000;
       }

       CreateEssentialDirectories();





        m_FMGClient->GetFriendList();
        m_FMGClient->StartCheckNetworkStatusTask();

        // 保存登录帐号列表
        LOGIN_ACCOUNT_INFO* lpAccount = m_LoginAccountList.Find(m_stAccountInfo.szUser);
        if (lpAccount != NULL)
            memcpy(lpAccount, &m_stAccountInfo, sizeof(LOGIN_ACCOUNT_INFO));
        else
            m_LoginAccountList.Add(m_stAccountInfo.szUser, m_stAccountInfo.szPwd,
                m_stAccountInfo.nStatus, m_stAccountInfo.bRememberPwd, m_stAccountInfo.bAutoLogin);
        m_LoginAccountList.SetLastLoginUser(m_stAccountInfo.szUser);
        tstring strFileName = Hootina::CPath::GetAppPath()+_T("Users\\LoginAccountList.dat");
        m_LoginAccountList.SaveFile(strFileName.c_str());

//        加载加好友通知Icon
//        LoadAddFriendIcon();

        m_FMGClient->LoadUserConfig();
//        加载头像风格信息
//        m_nBuddyListHeadPicStyle = m_FMGClient.m_UserConfig.GetBuddyListHeadPicStyle();
//        m_BuddyListCtrl.SetStyle((BLCTRL_STYLE)m_nBuddyListHeadPicStyle);
//        m_bShowBigHeadPicInSel = m_FMGClient.m_UserConfig.IsEnableBuddyListShowBigHeadPicInSel();
//        m_BuddyListCtrl.SetShowBigIconInSel(m_bShowBigHeadPicInSel);

//        重连成功后，保持主窗口原来的位置
//        if (m_nMainPanelStatus != MAINPANEL_STATUS_RECONNECTING)
//        {
//            SetWindowPos(NULL,2
//                m_FMGClient.m_UserConfig.GetMainDlgX(),
//                m_FMGClient.m_UserConfig.GetMainDlgY(),
//                m_FMGClient.m_UserConfig.GetMainDlgWidth(),
//                m_FMGClient.m_UserConfig.GetMainDlgHeight(),
//                SWP_SHOWWINDOW);
//        }

        //m_FMGClient->m_UserMgr.LoadTeamInfo();
        m_UserMgr.LoadTeamInfo();
        //m_FMGClient->m_UserMgr.LoadBuddyInfo();
        m_UserMgr.LoadBuddyInfo();
        //加载最近联系人列表
        //m_FMGClient->m_UserMgr.LoadRecentList();
        m_UserMgr.LoadRecentList();

        LOG_INFO("m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo.size()   --> %d", m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo.size());

        LOG_INFO("m_UserMgr.m_mapLocalBuddyInfo.size()  ---> %d", m_UserMgr.m_mapLocalBuddyInfo.size());
//        struct BuddyInfo
//        {
//            UINT	uAccountID;
//            TCHAR	szAccountName[32];
//            TCHAR	szMarkName[32];
//            long	nTeamIndex;
//            long	nGroupCount;		//群个数
//            UINT	GroupID[64];		//群号ID
//        };

        //LOG_INFO("m_UserMgr.uAccountID --> %d", m_UserMgr.m_mapLocalBuddyInfo[0]->uAccountID);

//        class CBuddyTeamInfo		// 好友分组信息
//        {
//        public:
//            CBuddyTeamInfo(void);
//            ~CBuddyTeamInfo(void);

//        public:
//            void Reset();
//            int GetBuddyCount();
//            int GetOnlineBuddyCount();
//            CBuddyInfo* GetBuddy(int nIndex);
//            void Sort();

//        public:
//            int m_nIndex;			// 索引
//            int m_nSort;			// 排列顺序
//            tstring m_strName;		// 分组名称
//            std::vector<CBuddyInfo*> m_arrBuddyInfo;
//        };

        //emit sigInitUITeamPart(m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo);

        for(auto& teamInfo : m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo)
        {
            std::wcout << "teamInfo->m_nIndex --> " << teamInfo->m_nIndex
                      << "teamInfo->m_strName.c_str()    --> " <<   teamInfo->m_strName.c_str()  << std::endl;
            //LOG_INFO("teamInfo->m_strName.c_str()    -->   %s", wide_Char_To_Multi_Byte((teamInfo->m_strName.c_str()));
        }


        for(auto& info : m_UserMgr.m_mapLocalBuddyInfo)
        {
            std::cout << info.first << " -- " << "uAccountID : " << info.second->uAccountID
                      << "szAccountName : " << TCHAR2STRING(info.second->szAccountName)
                      << "szMarkName ：" << TCHAR2STRING(info.second->szMarkName) << std::endl;
        }

        //emit sigInitUIBuddyPart(m_UserMgr.m_mapLocalBuddyInfo);
        emit sigInitBuddyUI(m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo, m_UserMgr.m_mapLocalBuddyInfo);

//        mainWnd = new MainWindow;
//        mainWnd->show();
        this->hide();
       // mainWnd->signature.s

//        QVBoxLayout * layout = new QVBoxLayout();
//        //设置边距为0
//        layout->setContentsMargins(0,0,0,0);
//        layout->setSpacing(0);

        //for(int i = 0; i < m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo.size(); i++)
//        for(auto& teamInfo : m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo)
//        {
//            QPushButton * btn = new QPushButton(QIcon(":/lib/jietou.png")," "+ QString::fromWCharArray(teamInfo->m_strName.c_str()));//箭头+分组名
//            btn->setFont(Globalobserver::font1);

//            mainWnd->listbtn.append(btn);
//            mainWnd->iswidget.append(true);

//            QSize btnsize(36,36);
//            btn->setIconSize(btnsize);
//            btn->setStyleSheet("QPushButton{text-align: left;background-color: rgba(203, 203, 203,200);border-style:solid;}"
//                               "QPushButton:hover{text-align: left;background-color: rgb(193, 193, 193);border-style:solid;}");
//            //加入分组信息
//            mainWnd->m_layout = new QVBoxLayout();
//            mainWnd->m_layout->setContentsMargins(0,0,0,0);
//            mainWnd->m_layout->setSpacing(0);
//            mainWnd->m_layout->addWidget(btn);
//            QListWidget * listwidget = new QListWidget(this);
//            connect(listwidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onDoubleWidgetClicked(QListWidgetItem*)));
//            mainWnd->listwidget.append(listwidget);
//            listwidget->setFrameShape(QListWidget::NoFrame);
//       s     listwidget->setGridSize(QSize(312,50));
//            int sum = -1;

//        }

//        for(int i = 0; i < m_UserMgr.m_mapLocalBuddyInfo.size(); i++)
//        {
//            //创建分组信息
//            //QPushButton * btn = new QPushButton(QIcon(":/lib/jietou.png")," "+grouping.at(j));//箭头+分组名
//            //btn->setFont(Globalobserver::font1);
//        }






    }
    break;
    }

}

std::string TCHAR2STRING(TCHAR *STR)
{
    int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
    char* chRtn = new char[iLen*sizeof(char)];
    WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
    std::string str(chRtn);
    delete chRtn;
    return str;
}


//不要忘记使用完char*后delete[]释放内存
char* wide_Char_To_Multi_Byte(wchar_t* pWCStrKey)
{
    //第一次调用确认转换后单字节字符串的长度，用于开辟空间
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize+1];
    //第二次调用将双字节字符串转换成单字节字符串
    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    return pCStrKey;

    //如果想要转换成string，直接赋值即可
    //string pKey = pCStrKey;
}

//    class CBuddyInfo			// 好友信息
//    {
//    public:
//        CBuddyInfo(void);
//        ~CBuddyInfo(void);

//    public:
//        void Reset();
//        void FillFakeData();	//TODO: 填充虚假数据，仅为了测试，实际的数据应该等服务器端完善以后从服务器获取
//        void SetBuddyInfo(CBuddyInfo* lpBuddyInfo);

//    public:
//        UINT		m_uUserID;			//用户ID，唯一标识该用户
//        tstring		m_strAccount;		//用户账户名
//        tstring		m_strPassword;		// 密码
//        tstring		m_strNickName;		// 昵称
//        tstring		m_strMarkName;		// 备注
//        long		m_nTeamIndex;		// 分组索引
//        UINT		m_nFace;			// 头像
//        long		m_nStatus;			// 在线状态
//        long        m_nClientType;      // 客户端类型
//        tstring		m_strSign;			// 个性签名
//        long		m_nGender;			// 性别
//        long		m_nBirthday;		// 生日
//        tstring		m_strMobile;		// 手机
//        tstring		m_strAddress;		// 用户地址信息
//        tstring		m_strEmail;
//        BOOL		m_bUseCustomFace;		//是否使用自定义头像
//        BOOL		m_bCustomFaceAvailable;	//自定义头像是否可用
//        tstring		m_strCustomFace;	    // 自定有头像名（文件名不是路径，本地不存在需要从服务器下载）
//        tstring		m_strRawCustomFace;		//原始自定义头像内容

//        CStringA    m_strCustomFaceName;

//        UINT		m_uMsgID;			//会话消息ID，初始值为0，只存在于内存中不存档
//    };

void Login::dealUpdateBuddyInfo(UINT id)
{
    LOG_INFO("Login::dealUpdateBuddyInfo(UINT id)  ...");
    UINT nUTalkUin = id;
    if (0 == nUTalkUin)
            return ;

    QString test = "Account";
    CBuddyInfo* lpBuddyInfo = GetUserInfo(nUTalkUin);
    if (lpBuddyInfo == nullptr)	// 更新用户昵称
        return ;

    LOG_INFO("lpBuddyInfo->m_strAccout --> %s", lpBuddyInfo->m_strNickName.c_str());

    QString account = QString::fromStdWString(lpBuddyInfo->m_strAccount);
    QString nickName = QString::fromStdWString(lpBuddyInfo->m_strNickName);
//    if(lpBuddyInfo->m_uUserID == m_UserMgr.m_UserInfo.m_uUserID)
//    {
//        if(lpBuddyInfo->m_strNickName.empty())
//            mainUI->username_label_2->setText(account);
//        else
//            mainUI->username_label_2->setText(nickName);

//        long nStatus = GetStatus();
//        //根据状态更新图标
//    }



}

void Login::test()
{
    LOG_INFO("Login::test() ... ... ..  ");
}

//void Login::on_miniMainWnd_clicked()
//{
//    this->hide();
//}

//void Login::on_closeMainWnd_clicked()
//{
//    this->close();
//}

//Login::LoginThread::LoginThread(QObject *parent)
//{

//}

//Login::LoginThread *Login::LoginThread::GetInstance()
//{
//    if(m_loginThread == nullptr)
//    {
//        m_loginThread = new Login::LoginThread();
//        m_loginThread->start();
//    }

//    return m_loginThread;
//}

//void Login::LoginThread::run()
//{
//   // m_login = new Login();
//    //m_login->LoginThreadProc();
//    //this->LoginThreadProc();
//}

LoginThread::LoginThread(QObject *parent)
{
   // m_login = new Login;
   connect(this, SIGNAL(sigLoginThread()), this, SLOT(test()));

}

//LoginThread *LoginThread::GetInstance()
//{

//}

void LoginThread::run()
{
    LOG_INFO("LoginThread::run()    ... ... ");

    emit sigLoginThread();

    LOG_INFO("sig  Sent    ... ... ");
//    QString user = m_login->ui->lineEdit->text();
//    QString passwd = m_login->ui->lineEdit_2->text();

    QString user = "110";
    QString passwd = "123456";

    QByteArray bUser = user.toLatin1();
    char *szUser = bUser.data();
    LOG_INFO("szUser --> %s", szUser);

    QByteArray bPasswd = passwd.toLatin1();
    char *szPassword = bPasswd.data();
    LOG_INFO("szPassword --> %s", szPassword);

//        EncodeUtil::UnicodeToUtf8(this->m_stAccountInfo.szUser, szUser, ARRAYSIZE(szUser));

//        EncodeUtil::UnicodeToUtf8(pLoginDlg->m_stAccountInfo.szPwd, szPassword, ARRAYSIZE(szPassword));

    std::string strReturnData;
    //超时时间设置为3秒
    bool bRet = CIUSocket::GetInstance().Login(szUser, szPassword, 1, online_type_pc_online, 3, strReturnData);
    //bool bRet = true;
    int nRet = LOGIN_FAILED;
    CLoginResult* pLoginResult = new CLoginResult();
    pLoginResult->m_LoginResultCode = LOGIN_FAILED;
    if (bRet)
    {
        //{"code": 0, "msg": "ok", "userid": 8}
        Json::Reader JsonReader;
        Json::Value JsonRoot;
        if (JsonReader.parse(strReturnData, JsonRoot) && !JsonRoot["code"].isNull() && JsonRoot["code"].isInt())
        {
            int nRetCode = JsonRoot["code"].asInt();

            if (nRetCode == 0)
            {
                if (!JsonRoot["userid"].isInt() || !JsonRoot["username"].isString() || !JsonRoot["nickname"].isString() ||
                    !JsonRoot["facetype"].isInt() || !JsonRoot["gender"].isInt() || !JsonRoot["birthday"].isInt() ||
                    !JsonRoot["signature"].isString() || !JsonRoot["address"].isString() ||
                    !JsonRoot["customface"].isString() || !JsonRoot["phonenumber"].isString() ||
                    !JsonRoot["mail"].isString())
                {
                    LOG_ERROR(_T("login failed, login response json is invalid, json=%s"), strReturnData.c_str());
                    pLoginResult->m_LoginResultCode = LOGIN_FAILED;
                }
                else
                {
                    pLoginResult->m_LoginResultCode = 0;
                    pLoginResult->m_uAccountID = JsonRoot["userid"].asInt();
                    strcpy_s(pLoginResult->m_szAccountName, ARRAYSIZE(pLoginResult->m_szAccountName), JsonRoot["username"].asCString());
                    strcpy_s(pLoginResult->m_szNickName, ARRAYSIZE(pLoginResult->m_szNickName), JsonRoot["nickname"].asCString());
                    //pLoginResult->m_nStatus = JsonRoot["status"].asInt();
                    pLoginResult->m_nFace = JsonRoot["facetype"].asInt();
                    pLoginResult->m_nGender = JsonRoot["gender"].asInt();
                    pLoginResult->m_nBirthday = JsonRoot["birthday"].asInt();
                    strcpy_s(pLoginResult->m_szSignature, ARRAYSIZE(pLoginResult->m_szSignature), JsonRoot["signature"].asCString());
                    strcpy_s(pLoginResult->m_szAddress, ARRAYSIZE(pLoginResult->m_szAddress), JsonRoot["address"].asCString());
                    strcpy_s(pLoginResult->m_szCustomFace, ARRAYSIZE(pLoginResult->m_szCustomFace), JsonRoot["customface"].asCString());
                    strcpy_s(pLoginResult->m_szPhoneNumber, ARRAYSIZE(pLoginResult->m_szPhoneNumber), JsonRoot["phonenumber"].asCString());
                    strcpy_s(pLoginResult->m_szMail, ARRAYSIZE(pLoginResult->m_szMail), JsonRoot["mail"].asCString());
                }
            }
            else if (nRetCode == 102)
                pLoginResult->m_LoginResultCode = LOGIN_UNREGISTERED;
            else if (nRetCode == 103)
                pLoginResult->m_LoginResultCode = LOGIN_PASSWORD_ERROR;
            else
                pLoginResult->m_LoginResultCode = LOGIN_FAILED;
        }
    }

    emit login->sigLoginResult(pLoginResult);
   // emit m_login->sigUpdateUserBasicInfo(m_UserMgr.m_UserInfo.m_uUserID);
}

void LoginThread::test()
{
    LOG_INFO("Test..................");
}
