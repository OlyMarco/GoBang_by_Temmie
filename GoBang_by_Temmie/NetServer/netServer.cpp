#include "netServer.h"
#include "ui_netserver.h"

#include <QNetworkInterface>
/*--------------------------------------------------------------------------------*/
NetServer::NetServer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NetServer)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://logo.ico"));
    ui->port->setText("25565");
    /*--------------------------------------------------------------------------------*/
    // 标题显示IP地址
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QString ip = nullptr;
    foreach (QHostAddress address, list)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost)
        {
            ip = address.toString();
        }
    }

    if (ip != nullptr)
    {
        setWindowTitle("Server IP: " + ip);
    }
    else
    {
        setWindowTitle("Create a Server");
    }
    /*--------------------------------------------------------------------------------*/
    m_s = new QTcpServer(this);
    Tcp_List.clear();
    connect(m_s, &QTcpServer::newConnection, this, &NetServer::slotNewConnect);
}
/*--------------------------------------------------------------------------------*/
void NetServer::slotNewConnect()
{
    if (m_s->hasPendingConnections())
    {
        QTcpSocket *new_tcp = m_s->nextPendingConnection();
        UserConnection *user = new UserConnection(new_tcp);
        Tcp_List.append(user);
        // 接收到信息时，将该信息转发给除自己以外的所有客户端
        connect(user->socket, &QTcpSocket::readyRead, this, [=]()
                {
            QByteArray data = user->socket->readAll();
            // 将从本客户端接收的消息转发给其他客户端
            for(int i = 0; i < Tcp_List.size(); i++){
                if(Tcp_List.at(i)->socket != user->socket){
                    Tcp_List.at(i)->socket->write(data);
                }
            } });
        // 当与某客户端断开连接时，将其断开信息转发给其他所有客户端，并将该客户端从连接池中删除
        connect(user->socket, &QTcpSocket::disconnected, this, [=]()
                {
            NetServer::user temp;
            temp.request = DISCONNECTED;

            QByteArray data;
            data.append(reinterpret_cast<char*>(&temp),sizeof(temp));
            QVector<UserConnection*>::iterator it;
            for(it=Tcp_List.begin();it!=Tcp_List.end();it++){
                if(*it == user){
                    Tcp_List.erase(it);
                    it--;// qvector迭代器会自动前移
                }
                else{
                    UserConnection* sendTemp = *it;
                    sendTemp->socket->write(data.data(),sizeof(temp));
                }
                if(Tcp_List.empty())// 若删除之后qvector为空，退出
                    break;
            } });
    }
}
/*--------------------------------------------------------------------------------*/
void NetServer::on_SetListen_clicked()
{
    // 按钮标签改变
    if (ui->SetListen->text() == "Go")
    {
        unsigned short port = ui->port->text().toUShort();
        m_s->listen(QHostAddress::Any, port);
        ui->SetListen->setText("Disconnected");
    }
    else if (ui->SetListen->text() == "Disconnected")
    {
        ui->SetListen->setText("Go");
        m_s->close();
    }
}
/*--------------------------------------------------------------------------------*/
NetServer::~NetServer()
{
    delete ui;
}
