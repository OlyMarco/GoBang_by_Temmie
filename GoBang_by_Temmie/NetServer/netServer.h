#ifndef NETSERVER_H
#define NETSERVER_H

#include "BoardParams/boardParams.h"
#include "userConnection.h"

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QString>
/*--------------------------------------------------------------------------------*/
namespace Ui
{
    class NetServer;
}

class NetServer : public QMainWindow
{
    Q_OBJECT
    /*--------------------------------------------------------------------------------*/
public:
    explicit NetServer(QWidget *parent = nullptr);
    ~NetServer();

    typedef struct user
    {
        std::string name;
        bool color;
        int row;
        int col;
        requestType request;
        GameType gameType;
    } user;
    /*--------------------------------------------------------------------------------*/
private:
    Ui::NetServer *ui;

    QTcpServer *m_s;
    QVector<UserConnection *> Tcp_List;
    QVector<UserConnection *> freeUser;
    QVector<UserConnection *> busyUser;
    QVector<UserConnection *> waitUser;

private slots:
    void slotNewConnect();

    void on_SetListen_clicked();
};
#endif // NETSERVER_H
