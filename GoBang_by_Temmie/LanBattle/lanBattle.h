#ifndef LANBATTLE_H
#define LANBATTLE_H

#include "GameCore/gameCore.h"

#include <QMainWindow>
#include <QLabel>
#include <QHostAddress>
/*--------------------------------------------------------------------------------*/
namespace Ui
{
    class LanBattle;
}

class LanBattle : public QMainWindow
{
    Q_OBJECT
    /*--------------------------------------------------------------------------------*/
public:
    QTcpSocket *tcp;
    GameCore::user player1;
    GameCore::user player2;

    explicit LanBattle(QWidget *parent = nullptr);
    ~LanBattle();

public slots:
    // 接受本地走步信号，向联机玩家传输player1
    void slotNextChess(GameCore::user);
    /*--------------------------------------------------------------------------------*/
private:
    Ui::LanBattle *ui;

    QLabel *m_status;

private slots:
    // 与服务器新建连接
    void slotNewConnect();
    // 连接按钮按下
    void on_connect_clicked();
    // 取消连接按钮按下
    void on_disconnect_clicked();
    // 断开连接时
    void slotDisconnect();
    // 确认双方已经连接成功
    void connectSuccess();
    // 将player1发送给服务端
    void sendPlayer1();
    // 从服务端接收player2
    void receivePlayer2();
    /*--------------------------------------------------------------------------------*/
signals:
    void connected();
    void hasNextChess(GameCore::user *);
    void initGame(GameCore::user *, GameCore::user *);
    void hasDisconnected();
};

#endif // LANBATTLE_H
