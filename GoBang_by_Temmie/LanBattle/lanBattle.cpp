#include "lanBattle.h"
#include "ui_LanBattle.h"
/*--------------------------------------------------------------------------------*/
// LanBattle窗口创建
LanBattle::LanBattle(QWidget *parent) : QMainWindow(parent),
                                        ui(new Ui::LanBattle)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://logo.ico"));
    setWindowTitle("Join a Server");
    // 设置文本框默认值
    ui->port->setText("25565");
    ui->ipAddr->setText("127.0.0.1");
    ui->disconnect->setDisabled(true);

    tcp = new QTcpSocket(this);
    // 连接成功后，给服务端发送本机player信息
    connect(tcp, &QTcpSocket::connected, this, &LanBattle::slotNewConnect);
    // 当接收到消息时，即是对方发送了player信息，此时将其赋给player2进行下一步操作
    connect(tcp, &QTcpSocket::readyRead, this, &LanBattle::receivePlayer2);
    // 断开连接后，关闭tcp连接
    connect(tcp, &QTcpSocket::disconnected, this, &LanBattle::slotDisconnect);

    // 状态栏
    m_status = new QLabel;
    m_status->setText("Disconnected");
    ui->statusbar->addWidget(new QLabel("Status："));
    ui->statusbar->addWidget(m_status);
}
/*--------------------------------------------------------------------------------*/
// 发送请求，请求与服务端连接
void LanBattle::on_connect_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    QString ip = ui->ipAddr->text();
    tcp->abort();
    tcp->connectToHost(QHostAddress(ip), port);

    ui->connect->setDisabled(true);
    ui->disconnect->setEnabled(true);
}
/*--------------------------------------------------------------------------------*/
// player1与服务器建立连接，等待与player2进行配对
void LanBattle::slotNewConnect()
{
    std::string user_name = ui->username->text().toStdString();
    player1.gameType = NET_PERSON; // player1相对于另一位玩家是player2
    player1.name = user_name;
    player1.color = true;
    player1.request = CONNECT;

    QByteArray data;
    data.append(reinterpret_cast<char *>(&player1), sizeof(player1));
    tcp->write(data.data(), sizeof(player1));
    m_status->setText("Waiting...");
}
/*--------------------------------------------------------------------------------*/
// 双方已经连接成功，此时进行游戏初始化功能
void LanBattle::connectSuccess()
{
    emit initGame(&player1, &player2);
}
/*--------------------------------------------------------------------------------*/
// player1走一步，发给联机玩家
void LanBattle::slotNextChess(GameCore::user play)
{
    play.request = NEXTCHESS;
    QByteArray data;
    data.append(reinterpret_cast<char *>(&play), sizeof(play));
    tcp->write(data.data(), sizeof(play));
}
/*--------------------------------------------------------------------------------*/
// 发送本机player1信息给服务端
void LanBattle::sendPlayer1()
{
    QByteArray data;
    data.append(reinterpret_cast<char *>(&player1), sizeof(player1));
    tcp->write(data.data(), sizeof(player1));
}
/*--------------------------------------------------------------------------------*/
// 接收服务端转发回来的信息
void LanBattle::receivePlayer2()
{
    QByteArray data = tcp->readAll();
    if (!data.isEmpty())
    {
        GameCore::user *temp = reinterpret_cast<GameCore::user *>(data.data());
        player2 = *temp;
    }
    if (player2.request == CONNECT) // 当请求为连接时
    {
        player1.request = CONNECTED;
        player1.color = !player2.color;
        sendPlayer1();
        connectSuccess();
        m_status->setText("Connected");
    }
    else if (player2.request == CONNECTED) // 当请求为已连接时
    {
        connectSuccess();
        m_status->setText("Connected");
    }
    else if (player2.request == NEXTCHESS) // 当请求为下棋时
    {
        emit hasNextChess(&player2);
    }
    else if (player2.request == DISCONNECTED) // 当请求为断开连接时
    {
        slotDisconnect();
    }
}
/*--------------------------------------------------------------------------------*/
// 与服务端断开连接
void LanBattle::on_disconnect_clicked()
{
    tcp->close();
    m_status->setText("Disconnected");
    ui->connect->setDisabled(false);
    ui->disconnect->setDisabled(true);
}
/*--------------------------------------------------------------------------------*/
// 当与联机用户断开连接时
void LanBattle::slotDisconnect()
{
    // 发出断连的信号
    emit hasDisconnected();

    tcp->close();
    m_status->setText("Disconnected");
    ui->connect->setDisabled(false);
    ui->disconnect->setDisabled(true);
}
/*--------------------------------------------------------------------------------*/
LanBattle::~LanBattle()
{
    delete ui;
}
