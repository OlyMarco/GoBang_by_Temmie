#include "userconnection.h"
/*--------------------------------------------------------------------------------*/
// 断开连接时发送信号
UserConnection::UserConnection(QObject *parent) : QObject(parent)
{
    connect(socket, &QTcpSocket::disconnected, this, &UserConnection::slotDisconnect);
}
/*--------------------------------------------------------------------------------*/
// 四种连接状态
UserConnection::UserConnection(QTcpSocket *tcp)
{
    this->socket = tcp;
    this->status = FREE;
}

UserConnection::~UserConnection()
{
    if (socket->state() == QTcpSocket::ConnectedState)
        socket->close();
}

void UserConnection::slotDisconnect()
{
    emit SignalDisconnect();
}
