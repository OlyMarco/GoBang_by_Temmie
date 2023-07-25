#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GameCore/gameCore.h"
#include "BoardParams/boardParams.h"
#include "ScoreEngine/scoreEngine.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QLabel>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QAction>
/*--------------------------------------------------------------------------------*/
class GameWindow : public QMainWindow
{
    Q_OBJECT
    /*--------------------------------------------------------------------------------*/
public:
    void initGame(GameCore::user *, GameCore::user *);

    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void sendBackSlot();                  // 发送返回请求
    void chessOneByNet(GameCore::user *); // 联机下棋
    /*--------------------------------------------------------------------------------*/
private:
    GameCore *game;     // 游戏指针
    GameType game_type; // 存储游戏类型
    GameCore::user *player1;
    GameCore::user *player2;

    int clickPosRow, clickPosCol; // 存储将点击的位置
    void judge(GameCore::user *); // 判断游戏胜负平
    // 玩家和颜色名称
    QLabel *showNowPlayer;
    QLabel *showName;

private slots:
    void chessOneByPerson(GameCore::user *); // 人下棋走步
    void chessOneByAI(GameCore::user *);     // AI下棋走步
    /*--------------------------------------------------------------------------------*/
protected:
    // 绘制
    void paintEvent(QPaintEvent *event);
    // 监听鼠标移动情况，方便落子
    void mouseMoveEvent(QMouseEvent *event);
    // 实际落子
    void mouseReleaseEvent(QMouseEvent *event);
    // 窗口关闭事件
    void closeEvent(QCloseEvent *);
    /*--------------------------------------------------------------------------------*/
signals:
    void backBaseWindow();                // 返回主菜单信号
    void netPlayer1Chess(GameCore::user); // 联机模式player1已经下棋了的信号
};

#endif // GAMEWINDOW_H
