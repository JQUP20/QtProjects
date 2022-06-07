QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

LIBS += $$PWD/sqlite3.lib

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SourceFiles/messagelogger.cpp \
    SourceFiles/RichEditUtil.cpp \
    SourceFiles/messagelogger.cpp \
    UserData/flamingoclient.cpp \
    UserData/userconfig.cpp \
    UserData/usermgr.cpp \
    UserData/usersessiondata.cpp \
    SourceFiles/LoginAccountList.cpp \
    Utils/buffer.cpp \
    Utils/encodeutil.cpp \
    Utils/file.cpp \
    Utils/file2.cpp \
    Utils/inifile.cpp \
    Utils/iulog.cpp \
    Utils/md5sum.cpp \
    Utils/minibuffer.cpp \
    Utils/path.cpp \
    Utils/performancecounter.cpp \
    Utils/utils.cpp \
    Utils/zlibutil.cpp \
    addfriend.cpp \
    agreefriend.cpp \
    chat.cpp \
#    flamingoclient.cpp \
    globalobserver.cpp \
    jsoncpp-1.9.0/json_reader.cpp \
    jsoncpp-1.9.0/json_value.cpp \
    jsoncpp-1.9.0/json_writer.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    net/iuprotocoldata.cpp \
    net/iusocket.cpp \
    net/protocolstream.cpp \
    performancecounter.cpp \
    query.cpp \
    startup.cpp \
    tasks/CheckNetworkStatusTask.cpp \
    tasks/HeartbeatTask.cpp \
    tasks/ThreadPool.cpp \
    tasks/recvmsgthread.cpp \
    tasks/sendmsgthread.cpp \
    tasks/thread.cpp \
    verify.cpp \
    zlib1.2.11/adler32.c \
    zlib1.2.11/compress.c \
    zlib1.2.11/crc32.c \
    zlib1.2.11/deflate.c \
    zlib1.2.11/gzclose.c \
    zlib1.2.11/gzlib.c \
    zlib1.2.11/gzread.c \
    zlib1.2.11/gzwrite.c \
    zlib1.2.11/infback.c \
    zlib1.2.11/inffast.c \
    zlib1.2.11/inflate.c \
    zlib1.2.11/inftrees.c \
    zlib1.2.11/trees.c \
    zlib1.2.11/uncompr.c \
    zlib1.2.11/zlibdemo.c \
    zlib1.2.11/zutil.c

HEADERS += \
    SQLite3.7.17/sqlite3.h \
    SourceFiles/IImageOle.h \
    SourceFiles/LoginAccountList.h \
    SourceFiles/RichEditUtil.h \
    SourceFiles/messagelogger.h \
    UserData/flamingoclient.h \
    Utils/performancecounter.h \
    addfriend.h \
    agreefriend.h \
    chat.h \
#    flamingoclient.h \
    globalobserver.h \
    jsoncpp-1.9.0/allocator.h \
    jsoncpp-1.9.0/assertions.h \
    jsoncpp-1.9.0/autolink.h \
    jsoncpp-1.9.0/config.h \
    jsoncpp-1.9.0/features.h \
    jsoncpp-1.9.0/forwards.h \
    jsoncpp-1.9.0/json.h \
    jsoncpp-1.9.0/json_tool.h \
    jsoncpp-1.9.0/json_valueiterator.inl \
    jsoncpp-1.9.0/reader.h \
    jsoncpp-1.9.0/stdafx.h \
    jsoncpp-1.9.0/value.h \
    jsoncpp-1.9.0/version.h \
    jsoncpp-1.9.0/writer.h \
    mainwindow.h \
    performancecounter.h \
    query.h \
    resource.h \
    startup.h \
    verify.h \
    zlib1.2.11/crc32.h \
    zlib1.2.11/deflate.h \
    zlib1.2.11/gzguts.h \
    zlib1.2.11/inffast.h \
    zlib1.2.11/inffixed.h \
    zlib1.2.11/inflate.h \
    zlib1.2.11/inftrees.h \
    zlib1.2.11/trees.h \
    zlib1.2.11/zconf.h \
    zlib1.2.11/zlib.h \
    zlib1.2.11/zutil.h \
    SourceFiles/messagelogger.h \
    UserData/userconfig.h \
    UserData/usermgr.h \
    UserData/usersessiondata.h \
    Utils/buffer.h \
    Utils/encodeutil.h \
    Utils/file.h \
    Utils/file2.h \
    Utils/inifile.h \
    Utils/iulog.h \
    Utils/md5sum.h \
    Utils/minibuffer.h \
    Utils/path.h \
    Utils/utils.h \
    Utils/zlibutil.h \
    login.h \
    net/Msg.h \
    net/iuprotocoldata.h \
    net/iusocket.h \
    net/protocolstream.h \
    net/stdafx.h \
    tasks/CheckNetworkStatusTask.h \
    tasks/HeartbeatTask.h \
    tasks/ThreadPool.h \
    tasks/recvmsgthread.h \
    tasks/sendmsgthread.h \
    tasks/thread.h

FORMS += \
    addfriend.ui \
    agreefriend.ui \
    chat.ui \
    globalobserver.ui \
    login.ui \
    mainwindow.ui \
    query.ui \
    verify.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    SourceFiles/sqlite3.lib \
    zlib1.2.11/文件概览.txt
