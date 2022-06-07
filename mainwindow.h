#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")

#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif

#include "net/stdafx.h"
#include <QWidget>
#include <QThread>
#include<QMainWindow>
#include<QSystemTrayIcon>
#include<QMouseEvent>
#include<QPoint>
#include<QMovie>
#include<QSize>
#include<QLabel>
#include<QPushButton>
#include<QListWidget>
#include<QSignalMapper>
#include<QTcpSocket>
#include<QLabel>
#include<QList>
#include<QTimer>
#include<QMenu>
#include<QDebug>
#include<QPainter>
#include<QBitmap>
#include<QSize>
#include<qdrawutil.h>
#include<QGraphicsDropShadowEffect>
#include<QListWidget>
#include<QHostInfo>
#include <iostream>

#include "net/stdafx.h"
#include "Utils/utils.h"
#include "Utils/inifile.h"
#include "Utils/path.h"
#include "Utils/iulog.h"
#include "UserData/usersessiondata.h"
#include "UserData/usermgr.h"
#include "login.h"
#include "query.h"
#include "verify.h"
#include "tasks/recvmsgthread.h"
#include "tasks/sendmsgthread.h"

class Login;
class Query;
class Verify;
namespace Ui {
class MainWindow;
}



class MainWindow : public QWidget
{
    Q_OBJECT

public:

    QSystemTrayIcon  *systemtrayicon;
    QMenu * menu;                       //菜单
    QMenu * mainmenu;                   //主界面菜单
    QAction *m_pShowAction;             //显示选项
    QAction *m_pCloseAction;            //退出选项
    QAction *m_pOnLineAction;           //在线
    QAction *m_pCallAction;             //call我
    QAction *m_pCloakingAction;         //隐身
    QAction *m_pLeaveAction;            //离开
    QAction *m_pBusyAction;             //忙碌
    QAction *m_pDisturbAction;          //请勿打扰
    QAction *m_pOffLineAtion;           //离线
    /*消息通知*/
    //Traywidget * tarywidget;            //右下角消息显示列表
    QPixmap icondata;                   //用于保存需要闪动头像
    bool iconbool =false;               //和icondata搭配使用
    /*定时器用于托盘头像闪动，显示等*/
    QTimer timerT;
    QTimer timerNoT;
    QTimer timemouse;
    /*账号基本数据*/
    //Usersql sqconn;                 //获取个人信息
    QPixmap icon;                   //头像
    QString account = "";           //账号
    QString name = "";              //昵称
    QString signature ="";          //个性签名
    QList<QPushButton *> listbtn;   //分组名
    QList<QListWidget *> listwidget; //分组列表

    Query * a;          //查找窗口
    Verify * verify;    //验证窗口
    QWidget *myinfo = new QWidget();//当鼠标悬浮头像弹出该窗口
    /*聊天相关*/
    QStringList stringlistdata; //数据池
    QStringList stringaccount;  //消息池
    QList<Chat *> listchat;     //保存聊天窗口
    QVector<int> Globalinfo;    //全局消息管理 1为普通消息，二位验证消息
    /*连接网络*/
    QTcpSocket * tcpClient;//连接网络
    QLabel * LabSocketate; //显示网络类型
    /*鼠标拖动事件*/
    QList<bool> iswidget;    //列表展开
    QPoint last;             //窗口拖动变量
    bool isPressedWidget;
    /*其他*/
    QSignalMapper * myMapper; //信号管理
    QSignalMapper * menuAction;
    bool ishover = false;//判断鼠标是否进过托盘图标
    QVBoxLayout * m_layout;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     CBuddyInfo* GetUserInfo(UINT uAccountID);

     std::string TCHAR2STRING(TCHAR *STR);

     void GetFriendList();

public slots:
     void on_min_tool_clicked();     //最小化
     void on_close_tool_clicked();   //关闭按钮
     //void on_toolButton_3_clicked(); //主界面在线按钮
     void mousePressEvent(QMouseEvent *event);   //鼠标点击
     void mouseMoveEvent(QMouseEvent *event);    //鼠标移动
     void mouseReleaseEvent(QMouseEvent *event); //鼠标释放
//     void onWidgetClicked(int i);              //分组按钮被点击
//     void onDoubleWidgetClicked(QListWidgetItem * witem);//好友列表被双击
//     void on_activatedSysTratIcon(QSystemTrayIcon::ActivationReason reason);//对托盘按钮的点击

    void dealUpdateBuddyInfo(UINT id);

    //void InitUI(std::map<UINT , BuddyInfo*> map);
    void actionexe(int value);

//    private
    void initTeamUI(std::vector<CBuddyTeamInfo*> vec);
    void initUIBuddyPart(std::map<UINT , BuddyInfo*> map);
    void onDoubleWidgetClicked(QListWidgetItem * witem);
    void initBuddyUI(std::vector<CBuddyTeamInfo*> teamVec, std::map<UINT , BuddyInfo*> buddyMap);


public:
    CUserMgr m_UserMgr;
    Login* m_login;
    CSendMsgThread *m_SendMsgThread;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
