# --------------------------------------------------------------------------------
# A Qt GoBang Demo Made by Temmie
# Last Save: 2023/06/30
# Open Source: MIT
# --------------------------------------------------------------------------------
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoBang_by_Temmie
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        BoardParams/boardParams.cpp \
        GameCore/gameCore.cpp \
        GameWindow/gameWindow.cpp \
        LanBattle/lanBattle.cpp \
        NetServer/netServer.cpp \
        NetServer/userConnection.cpp \
        ScoreEngine/scoreEngine.cpp \
        main.cpp \
        mainWindow.cpp

HEADERS += \
    BoardParams/boardParams.h \
    GameCore/gameCore.h \
    GameWindow/gameWindow.h \
    LanBattle/lanBattle.h \
    NetServer/netServer.h \
    NetServer/userConnection.h \
    ScoreEngine/scoreEngine.h \
    mainWindow.h

FORMS += \
        lanbattle.ui \
        mainwindow.ui \
        netserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

RC_FILE = icon.rc
