#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->username_label->setText(QString::fromLocal8Bit("Account"));
//    ui->signature_label->setText(QString::fromLocal8Bit("用户昵称"));
    //ui->username_label->setText(QString::fromLocal8Bit("Account"));

    //个人信息弹框
    this->myinfo->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::X11BypassWindowManagerHint|Qt::Tool);
    //主窗口样式
    setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground);


    Globalobserver::setMainwindowp(this);

   // m_login = new Login();
//    connect(m_login, SIGNAL(sigInitMainUI(std::map<UINT , BuddyInfo*>)), this, SLOT(InitUI(std::map<UINT , BuddyInfo*>)));
     //connect(this, SIGNAL(sigUpdateUserBasicInfo(UINT)), this, SLOT(dealUpdateBuddyInfo(UINT)));

//    connect(m_login, SIGNAL(sigInitTeamUI(std::vector<CBuddyTeamInfo*> vec)), this, SLOT(initTeamUI(std::vector<CBuddyTeamInfo*>)));



//    systemtrayicon = new QSystemTrayIcon(this);
//    QIcon icon = QIcon(":/lib/fdogicon.png");
//    systemtrayicon->setIcon(icon);
//    QString str = QString("Fdog:%1(%2)\n声音:关闭\n消息提示框:关闭\n会话消息:任务栏头像闪动 ").arg(this->name,this->account);
//    systemtrayicon->setToolTip(str);
//    systemtrayicon->show();
    //设置菜单
    menu = new QMenu(this);
    m_pShowAction = new QAction("显示主界面");
    m_pCloseAction = new QAction("退出");
    m_pOnLineAction = new QAction(QIcon(":/lib/zaixian"),"在线");
    m_pCallAction = new QAction(QIcon(":/lib/xiaolian"),"F我吧");
    m_pCloakingAction = new QAction(QIcon(":/lib/yinshenim"),"隐身");
    m_pLeaveAction = new QAction(QIcon(":/lib/likaishijian"),"离开");
    m_pBusyAction = new QAction(QIcon(":/lib/manglu"),"忙碌");
    m_pDisturbAction = new QAction(QIcon(":/lib/wurao"),"请勿打扰");
    m_pOffLineAtion = new QAction(QIcon(":/lib/lixianim"),"离线");

    menu->addAction(m_pOnLineAction);
    menu->addAction(m_pCallAction);
    menu->addAction(m_pCloakingAction);
    menu->addAction(m_pLeaveAction);
    menu->addAction(m_pBusyAction);
    menu->addAction(m_pDisturbAction);
    menu->addAction(m_pOffLineAtion);
    menu->addSeparator();
    menu->addAction(m_pShowAction);
    menu->addAction(m_pCloseAction);
    menuAction = new QSignalMapper();
    QAction * actionarry[9]={m_pShowAction,m_pCloseAction,m_pOnLineAction,m_pCallAction,
                             m_pCloakingAction,m_pLeaveAction,m_pBusyAction,m_pDisturbAction,m_pOffLineAtion};
    for(int i =0;i<9;i++)
    {
        connect(actionarry[i],SIGNAL(triggered(bool)),menuAction,SLOT(map()));
        menuAction->setMapping(actionarry[i],i);
    }
//    connect(menuAction,SIGNAL(mapped(int)),this,SLOT(actionexe(int)));
//    mainmenu = menu;
//    ui->user_status->setMenu(menu);
//    systemtrayicon->setContextMenu(menu);

    //获取分组列表以及好友
    //添加垂直布局 最外面布局
    QVBoxLayout * layout = new QVBoxLayout();
    //设置边距为0
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

//    for(auto& teamInfo : m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo)
//    {
//        QPushButton * btn = new QPushButton(QIcon(":/lib/jietou.png")," "+ QString::fromWCharArray(teamInfo->m_strName.c_str()));//箭头+分组名
//        btn->setFont(Globalobserver::font1);

//        this->listbtn.append(btn);
//        this->iswidget.append(true);
//        btn->setFixedSize(312,38);
//        QSize btnsize(36,36);
//        btn->setIconSize(btnsize);
//        btn->setStyleSheet("QPushButton{text-align: left;background-color: rgba(203, 203, 203,200);border-style:solid;}"
//                           "QPushButton:hover{text-align: left;background-color: rgb(193, 193, 193);border-style:solid;}");
//        //加入分组信息
//        layout->addWidget(btn);
//        QListWidget * listwidget = new QListWidget(this);
//        connect(listwidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onDoubleWidgetClicked(QListWidgetItem*)));
//        this->listwidget.append(listwidget);
//        listwidget->setFrameShape(QListWidget::NoFrame);
//        listwidget->setGridSize(QSize(312,50));

//        int sum = -1;

//        QHBoxLayout *horLayout = new QHBoxLayout();//水平布局
//        horLayout->setContentsMargins(0,0,0,0);
//        horLayout->setSpacing(0);
//        QLabel * l1 = new QLabel();
//        l1->setFixedSize(15,32);
//        QPushButton * btnicon = new QPushButton();
//        btnicon->setFixedSize(32,32);
//        btnicon->setIconSize(QSize(32,32));
//        //btnicon->setIcon(sqconn.getPixmapIcon(mf.mid(1)));
//        btnicon->setStyleSheet("background:rgba(0,0,0,0)");
////            QLabel * la2 = new QLabel(QString("%1").arg(mf.mid(1)));
////            la2->setObjectName("label2");
////            la2->hide();
////            QLabel * la3 = new QLabel(QString("  %1").arg(mfriendname.at(i)));
////            la3->setObjectName("label3");
////            la3->setFont(Globalobserver::font2);
//        horLayout->addWidget(l1);
//        horLayout->addWidget(btnicon);
////            horLayout->addWidget(la2);
////            horLayout->addWidget(la3);
//        QWidget *widget =new QWidget(this);
//        widget->setLayout(horLayout);
//        widget->setStyleSheet("background:rgba(232, 255, 149,0);");
//        QListWidgetItem * Listitem = new QListWidgetItem(listwidget);
//        Listitem->setSizeHint(QSize(312, 50));  //每次改变Item的高度
//        listwidget->setItemWidget(Listitem,widget);
//        listwidget->setFixedSize(312,50*(sum+1));
//        listwidget->setStyleSheet("QListWidget::Item{background-color: rgba(203, 203, 203,200);}"
//                                  "QListWidget::Item:hover{background-color: rgb(193, 193, 193);}"
//                                  "QListWidget::Item:selected{background-color: rgb(193, 193, 193);}"
//                                  "QListWidget{outline:0px;}");
////        }
////    }
////    btn->setText(grouping.at(j) + "     " + QString::number(sum+1)+"/"+QString::number(sum+1));
//layout->addWidget(listwidget);
////    listwidget->setObjectName(grouping.at(j));

//layout->addStretch();
//ui->scrollAreaWidgetContents->setLayout(layout);

//    }


   // GetFriendList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDoubleWidgetClicked(QListWidgetItem * witem)
{
    QWidget * pwig=NULL;
    for(int i =0;i<this->listwidget.length();i++)
    {
        pwig = this->listwidget[i]->itemWidget(witem);
       if(pwig!=NULL)break;
    }
    //判断当前窗口在不在
    bool isshow = false;
    for(int i=0;i<listchat.length();i++)
    {
        if(listchat[i]->getOtheraccount()==pwig->findChild<QLabel *>("label2")->text())
        {
            isshow=true;
            listchat[i]->show();
        }
    }
    if(!isshow)
    {
        Chat * chat = new Chat(this->icon,this->icon,
                               pwig->findChild<QLabel *>("label2")->text(),
                               pwig->findChild<QLabel *>("label3")->text(),this);
        chat->setAccount(this->account);
        chat->setAttribute(Qt::WA_DeleteOnClose);
        listchat.append(chat);

        connect(chat,SIGNAL(sendData(QString)),this,SLOT(MainSendData(QString)));
        connect(chat,SIGNAL(sendCount(QString)),this,SLOT(listchatcount(QString)));
        chat->show();
    }
}

//        struct BuddyInfo
//        {
//            UINT	uAccountID;
//            TCHAR	szAccountName[32];
//            TCHAR	szMarkName[32];
//            long	nTeamIndex;
//            long	nGroupCount;		//群个数
//            UINT	GroupID[64];		//群号ID
//        };

//std::string TCHAR2STRING(TCHAR *STR)
//{
//    int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
//    char* chRtn = new char[iLen*sizeof(char)];
//    WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
//    std::string str(chRtn);
//    delete chRtn;
//    return str;
//}

void MainWindow::initBuddyUI(std::vector<CBuddyTeamInfo *> teamVec, std::map<UINT, BuddyInfo *> buddyMap)
{
    LOG_INFO("MainWindow::initBuddyUI(std::vector<CBuddyTeamInfo *> teamVec, std::map<UINT, BuddyInfo *> buddyMap");

    ui->username_label->setText(QString::fromLocal8Bit("Account"));
    ui->signature_label->setText(QString::fromLocal8Bit("用户昵称"));
    QVBoxLayout * layout = new QVBoxLayout();
    //设置边距为0
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

 /*   m_layout = new QVBoxLayout();

    m_layout = new QVBoxLayout();
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0)*/;



    for(auto& teamInfo : teamVec)
    {
        QPushButton * btn = new QPushButton(QIcon(":/lib/jietou.png")," "+ QString::fromWCharArray(teamInfo->m_strName.c_str()));//箭头+分组名
        btn->setFont(Globalobserver::font1);

        this->listbtn.append(btn);
        this->iswidget.append(true);
        btn->setFixedSize(312,38);

        QSize btnsize(36,36);
        btn->setIconSize(btnsize);
        btn->setStyleSheet("QPushButton{text-align: left;background-color: rgba(203, 203, 203,200);border-style:solid;}"
                           "QPushButton:hover{text-align: left;background-color: rgb(193, 193, 193);border-style:solid;}");

        //ui->signature_label->setText(QString::fromLocal8Bit("用户昵称"));
        //加入分组信息
        /*this->m_layout = new QVBoxLayout();
        this->m_layout->setContentsMargins(0,0,0,0);
        this->m_layout->setSpacing(0);*/
        layout->addWidget(btn);
        QListWidget * listwidget = new QListWidget(this);
        connect(listwidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onDoubleWidgetClicked(QListWidgetItem*)));
        this->listwidget.append(listwidget);
        listwidget->setFrameShape(QListWidget::NoFrame);
        listwidget->setGridSize(QSize(312,50));
        int sum = -1;

        for(auto& buddyInfo :  buddyMap)
        {
            std::string accountName = TCHAR2STRING(buddyInfo.second->szAccountName);
            LOG_INFO("buddyInfo->nTeamIndex --> %d", buddyInfo.second->nTeamIndex);

            sum++;
            QHBoxLayout *horLayout = new QHBoxLayout();//水平布局
            horLayout->setContentsMargins(0,0,0,0);
            horLayout->setSpacing(0);
            QLabel * l1 = new QLabel();
            l1->setFixedSize(15,32);
            QPushButton * btnicon = new QPushButton();
            btnicon->setFixedSize(32,32);
            btnicon->setIconSize(QSize(32,32));
            btnicon->setIcon(QIcon(":/Image/DefBuddyHeadPicOffline.png"));
            btnicon->setStyleSheet("background:rgba(0,0,0,0)");
            QLabel * la2 = new QLabel(QString("%1").arg("test"));
            la2->setObjectName("label2");
            la2->hide();
            QLabel * la3 = new QLabel(QString("  %1").arg(QString::fromStdString(accountName)));
            la3->setObjectName("label3");
            la3->setFont(Globalobserver::font2);

            horLayout->addWidget(l1);
            horLayout->addWidget(btnicon);
            horLayout->addWidget(la2);
            horLayout->addWidget(la3);
            QWidget *widget =new QWidget(this);
            widget->setLayout(horLayout);
            widget->setStyleSheet("background:rgba(232, 255, 149,0);");
            QListWidgetItem * Listitem = new QListWidgetItem(listwidget);
            Listitem->setSizeHint(QSize(312, 50));  //每次改变Item的高度
            listwidget->setItemWidget(Listitem,widget);
            listwidget->setFixedSize(312,50*(sum+1));
            listwidget->setStyleSheet("QListWidget::Item{background-color: rgba(203, 203, 203,200);}"
                                      "QListWidget::Item:hover{background-color: rgb(193, 193, 193);}"
                                      "QListWidget::Item:selected{background-color: rgb(193, 193, 193);}"
                                      "QListWidget{outline:0px;}");


        }

        btn->setText(QString::fromWCharArray(teamInfo->m_strName.c_str()));
        layout->addWidget(listwidget);
        listwidget->setObjectName(QString::fromWCharArray(teamInfo->m_strName.c_str()));


    }
    layout->addStretch();
    ui->scrollAreaWidgetContents->setLayout(layout);

    this->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    last = event->globalPos();
//    if (event->button() == Qt::LeftButton)
//    {
//        m_point = event->globalPos()-frameGeometry().topLeft();
//    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
        {
            int dx = event->globalX() - last.x();
            int dy = event->globalY() - last.y();
            last = event->globalPos();
            move(x()+dx, y()+dy);
        }
    //move(event->globalPos() - m_point);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
    isPressedWidget = false; // 鼠标松开时，置为false
}

void MainWindow::on_close_tool_clicked()
{
    qDebug()<<"执行关闭1";
//    systemtrayicon->hide();
    qDebug()<<"执行关闭2";
    this->close();
    qDebug()<<"执行关闭3";
    /*sqconn.setSate(-1);
    sqconn.AccountIP(getLocalIP());      //获取ip登录离线
    qDebug()<<"执行关闭4";
    //断开连接
    if(tcpClient->state()==QAbstractSocket::ConnectedState)
    {
        tcpClient->disconnectFromHost();
    }
    qDebug()<<"执行关闭5";
    //释放内存 把窗口释放s
//    qDeleteAll(this->listchat);
    qDebug()<<"释放";
//    emit sendquitData();*/
}

void MainWindow::on_min_tool_clicked()
{
     this->hide();
}



CBuddyInfo *MainWindow::GetUserInfo(UINT uAccountID)
{
    LOG_INFO("MainWindow::GetUserInfo(UINT uAccountID) ... ");
    m_login = new Login;
    LOG_INFO("uAccountID --> %d", uAccountID);
    LOG_INFO("m_login->m_UserMgr.m_UserInfo.m_uUserID --> %d", m_login->m_UserMgr.m_UserInfo.m_uUserID);
    if(uAccountID==0 || uAccountID==m_login->m_UserMgr.m_UserInfo.m_uUserID)
        return &m_UserMgr.m_UserInfo;

    CBuddyTeamInfo* pTeamInfo = nullptr;
    CBuddyInfo* pBuddyInfo = nullptr;
    for(size_t i=0; i < m_login->m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo.size(); ++i)
    {
        pTeamInfo = m_login->m_UserMgr.m_BuddyList.m_arrBuddyTeamInfo[i];
        for(size_t j=0; j<pTeamInfo->m_arrBuddyInfo.size(); ++j)
        {
            pBuddyInfo = pTeamInfo->m_arrBuddyInfo[j];
            if(uAccountID == pBuddyInfo->m_uUserID)
                return pBuddyInfo;
        }
    }


    CGroupInfo* pGroupInfo = NULL;
    for(size_t i=0; i<m_login->m_UserMgr.m_GroupList.m_arrGroupInfo.size(); ++i)
    {
        pGroupInfo = m_login->m_UserMgr.m_GroupList.m_arrGroupInfo[i];
        for(size_t j=0; j<pGroupInfo->m_arrMember.size(); ++j)
        {
            pBuddyInfo = pGroupInfo->m_arrMember[j];
            if(uAccountID == pBuddyInfo->m_uUserID)
                return pBuddyInfo;
        }
    }

    return nullptr;
}

std::string MainWindow::TCHAR2STRING(TCHAR *STR)
{
    int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
    char* chRtn = new char[iLen*sizeof(char)];
    WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
    std::string str(chRtn);
    delete chRtn;
    return str;
}

void MainWindow::GetFriendList()
{
    std::cout << "FlamingoClient::GetFriendList() 。。。 " << std::endl;
    CUserBasicInfoRequest* pBasicInfoRequest = new CUserBasicInfoRequest();
    pBasicInfoRequest->m_setAccountID.insert(m_UserMgr.m_UserInfo.m_uUserID);
    m_SendMsgThread->HandleItem(pBasicInfoRequest);
}

void MainWindow::dealUpdateBuddyInfo(UINT id)
{
    //ui->username_label->setText(QString::fromLocal8Bit("Account"));
    LOG_INFO("MainWindow::dealUpdateBuddyInfo(UINT id)");

    LOG_INFO("id --> %d", id);
    UINT nUTalkUin = id;
    if (0 == nUTalkUin)
            return ;
    //ui->username_label->setText(QString::fromLocal8Bit("Account"));


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


    CBuddyInfo* lpBuddyInfo = GetUserInfo(nUTalkUin);
//    LOG_INFO("lpBuddyInfo->m_strAccount --> %s", lpBuddyInfo->m_strAccount.c_str());

//    if (lpBuddyInfo == nullptr)	// 更新用户昵称
//        return ;
    ui->username_label->setText(QString::fromLocal8Bit("用户昵称"));

//    QString account = QString::fromStdWString(lpBuddyInfo->m_strAccount);
//    QString nickName = QString::fromStdWString(lpBuddyInfo->m_strNickName);
//    if(lpBuddyInfo->m_uUserID == m_login->m_UserMgr.m_UserInfo.m_uUserID)
//    {
//        if(lpBuddyInfo->m_strNickName.empty())
//            ui->username_label_2->setText("Account");
//        else
//            ui->username_label_2->setText(nickName);
//    }

}



void MainWindow::actionexe(int value)
{
    //-1离线 0在线 1F我吧 2隐身 3离开 4忙碌 5勿扰
    switch(value)
    {
    case 0:
        this->show();
        break;
    case 1:
        this->close();
        break;
//    case 2:
//        ui->user_status->setIcon(QIcon(":/lib/zaixian"));
//        break;
//    case 3:
//        ui->user_status->setIcon(QIcon(":/lib/xiaolian"));
//        break;
//    case 4:
//        ui->user_status->setIcon(QIcon(":/lib/yinshenim"));
//        break;
//    case 5:
//        ui->user_status->setIcon(QIcon(":/lib/likaishijian"));
//        break;
//    case 6:
//        ui->user_status->setIcon(QIcon(":/lib/wanglu"));
//        break;
//    case 7:
//        ui->user_status->setIcon(QIcon(":/lib/wurao"));
//        break;
//    case 8:
//        ui->user_status->setIcon(QIcon(":/lib/lixianim"));
        break;
    }
}

void MainWindow::initTeamUI(std::vector<CBuddyTeamInfo *> vec)
{
    LOG_INFO("MainWindow::initTeamUI(std::vector<CBuddyTeamInfo *> vec) ...... ");

    ui->username_label->setText(QString::fromLocal8Bit("Account"));
    ui->signature_label->setText(QString::fromLocal8Bit("用户昵称"));
    QVBoxLayout * layout = new QVBoxLayout();
    //设置边距为0
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);



    for(auto& teamInfo : vec)
    {
        QPushButton * btn = new QPushButton(QIcon(":/lib/jietou.png")," "+ QString::fromWCharArray(teamInfo->m_strName.c_str()));//箭头+分组名
        btn->setFont(Globalobserver::font1);

        this->listbtn.append(btn);
        this->iswidget.append(true);

        QSize btnsize(36,36);
        btn->setIconSize(btnsize);
        btn->setStyleSheet("QPushButton{text-align: left;background-color: rgba(203, 203, 203,200);border-style:solid;}"
                           "QPushButton:hover{text-align: left;background-color: rgb(193, 193, 193);border-style:solid;}");

        //ui->signature_label->setText(QString::fromLocal8Bit("用户昵称"));
        //加入分组信息
        this->m_layout = new QVBoxLayout();
        this->m_layout->setContentsMargins(0,0,0,0);
        this->m_layout->setSpacing(0);
        this->m_layout->addWidget(btn);
        QListWidget * listwidget = new QListWidget(this);
        //connect(listwidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onDoubleWidgetClicked(QListWidgetItem*)));
        this->listwidget.append(listwidget);
        listwidget->setFrameShape(QListWidget::NoFrame);
        listwidget->setGridSize(QSize(312,50));
        int sum = -1;



    }

    this->show();




}

void MainWindow::initUIBuddyPart(std::map<UINT, BuddyInfo *> map)
{
    LOG_INFO("MainWindow::initUIBuddyPart(std::map<UINT, BuddyInfo *> map)  ...... ");
}


