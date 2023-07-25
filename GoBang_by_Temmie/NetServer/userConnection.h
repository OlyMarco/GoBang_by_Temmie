#ifndef USERCONNECTION_H
#define USERCONNECTION_H

#include "BoardParams/boardParams.h"

#include <QObject>
#include <QTcpSocket>
/*--------------------------------------------------------------------------------*/
class UserConnection : public QObject
{
    Q_OBJECT
    /*--------------------------------------------------------------------------------*/
public:
    UserConnection(QTcpSocket *);

    explicit UserConnection(QObject *parent = nullptr);
    ~UserConnection();

    QString status;
    QTcpSocket *socket;
    QString nextChess;
    QString request;
    /*--------------------------------------------------------------------------------*/
private slots:
    void slotDisconnect();
    /*--------------------------------------------------------------------------------*/
signals:
    void SignalDisconnect();
    void SignalRemoveThis();
};

#endif // USERCONNECTION_H
