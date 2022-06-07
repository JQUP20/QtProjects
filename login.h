#ifndef LOGIN_H
#define LOGIN_H

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

#include <QThread>
#include<QSystemTrayIcon>
#include <QWidget>
#include<QMovie>
#include<QSize>
#include<QMouseEvent>
#include<QPoint>
#include<QStringList>
#include<QListWidget>
#include<QPainter>
#include<QDesktopServices>
#include<QListView>
#include<QDebug>
#include<qdrawutil.h>
#include<QGraphicsDropShadowEffect>
#include<QDir>
#include<QCoreApplication>
#include<QFile>
#include<QTextCodec>
#include<QMenu>
#include<QMessageBox>
#include<algorithm>
#include<QTimer>
#include<QHBoxLayout>
#include <QSignalMapper>
#include <QTcpSocket>
#include "Utils/iulog.h"
#include <QThread>
#include <iostream>

#include "net/stdafx.h"
#include "Utils/utils.h"
#include "Utils/inifile.h"
#include "Utils/path.h"
#include "UserData/usersessiondata.h"
#include "Utils/encodeutil.h"
#include "net/iusocket.h"
#include "net/iuprotocoldata.h"
#include "net/Msg.h"
#include "UserData/usermgr.h"
#include "tasks/recvmsgthread.h"
#include "tasks/sendmsgthread.h"
#include "tasks/CheckNetworkStatusTask.h"
#include "SourceFiles/LoginAccountList.h"

#include "jsoncpp-1.9.0/json.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globalobserver.h"


class CLoginResult;
class CUserConfig;
class CUserMgr;
class CRecvMsgThread;
class CSendMsgThread;
class CCheckNetworkStatusTask;
class MainWindow;
class CFlamingoClient;
class LoginThread;


namespace Ui {
class Login;
}

//extern Login *login;

class Login : public QWidget
{
    Q_OBJECT
    QTcpSocket * tcpClient = NULL;//连接网络
    QSystemTrayIcon  * systemtrayicon = NULL;  //系统托盘
    QPoint m_point;                     //点类
    QMovie * m_movie = NULL;                   //添加动态图
    QMovie * m_movie2 = NULL;                  //添加动态图2
    QSize m_si;                         //动态图压缩大小
    QSize m_si2;                        //动态图压缩大小2
    //Usersql sqconn;                     //数据库类
    //FlamingoClient * w = NULL;                     //主界面类
    QString account ="";                //查询账户
    QPoint last;                        //窗口拖动用变量
    bool isPressedWidget;
    bool ispasswd=false;                //判断是否是密码
    QStringList infoList;               //用户账号
    QStringList infopasswd;             //用户密码
    QStringList icon;                   //头像保存地址
    QListWidget * m_AccountList = NULL;        //下拉列表框
    QMenu * menu = NULL;                       //右击菜单
    QAction *m_pShowAction = NULL;             //显示选项
    QAction *m_pCloseAction = NULL;            //退出选项
    QSignalMapper * myMapper = NULL;
    QVector<int> infoListsign;
    QTimer timesignin;
    quint16 port;
    QString addr ;
    bool network = true; //是否能正常连接主机

    QAction * searchAction = NULL;
    QAction * searchAction_2 = NULL;
    QAction * searchAction_3 = NULL;
    QHBoxLayout *horLayout = NULL;
    QPushButton * la = NULL;
    QLabel * la2 = NULL;
    QPushButton * b1 = NULL;

    QList<QPushButton *> listbtn;   //分组名
    QList<QListWidget *> listwidget; //分组列表

    /*鼠标拖动事件*/
    QList<bool> iswidget;    //列表展开
    //QPoint last;             //窗口拖动变量
    QThread* LoginThread;


public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放

    void InitUI();
    void InitMainUI();

    void DoLogin();

    static UINT WINAPI LoginThreadProc(void* pParam);

    bool InitNetThreads();

    void GetFriendList();

    void LoadUserConfig();

    CBuddyInfo* GetUserInfo(UINT uAccountID);
    long GetStatus();

    void CreateEssentialDirectories();

    std::string TCHAR2STRING(TCHAR *STR);

//    static Login  *GetInstance();



 //   void run();


//    class LoginThread: public QThread
//    {


//    public:
//        explicit LoginThread(QObject * parent = 0);

//        static LoginThread* GetInstance();

//    private:
//        void run();
//    };

signals:
    void sigLoginResult(CLoginResult* pLoginResult);
    void sigUpdateUserBasicInfo(UINT id);
    void sigInitBuddyUI(std::vector<CBuddyTeamInfo*> vec, std::map<UINT , BuddyInfo*> map);
    //void sigInitUITeamPart(std::vector<CBuddyTeamInfo*> vec);

   // void GetFriendList();

public slots:
    void on_pushButton_clicked();
    void showWidget();
    void closeWidget();

   void LoginThreadProc();

   void dealLoginResult(CLoginResult* pLoginResult);
   void dealUpdateBuddyInfo(UINT id);
   void test();

public:
   CFlamingoClient*			m_FMGClient;
   CUserMgr                         m_UserMgr;
   CCheckNetworkStatusTask			m_CheckNetworkStatusTask;

   CSendMsgThread*					m_SendMsgThread;
   CRecvMsgThread*                   m_RecvMsgThread;

   CLoginAccountList				m_LoginAccountList;
   LOGIN_ACCOUNT_INFO				m_stAccountInfo;						//当前即将要登录的账户信息

   CUserConfig						m_UserConfig;

   bool m_bEnableReconnect;
   UINT                            m_uReconnectInterval;                   //重连时间间隔，必须大于0，单位毫秒
  // class LoginThread* m_loginThread;

   //static Login *m_login;

private slots:
//   void on_miniMainWnd_clicked();

//   void on_closeMainWnd_clicked();

public:
    Ui::Login *ui;
    MainWindow *mainWnd;
    Ui::MainWindow *mainUI;
};

extern Login *login;


class LoginThread : public QThread
{
    Q_OBJECT
public:
    explicit LoginThread(QObject * parent = 0);

//    static LoginThread* GetInstance();

private:
    void run();

signals:
    void sigLoginThread();

public slots:
    void test();

public:
    Login* m_login;

};




#endif // LOGIN_H
