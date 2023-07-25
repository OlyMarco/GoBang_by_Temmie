#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameCore/gameCore.h"
#include "BoardParams/boardParams.h"
#include "GameWindow/gameWindow.h"
#include "LanBattle/lanBattle.h"
#include "NetServer/netServer.h"

#include <QMainWindow>
#include <QLabel>
/*--------------------------------------------------------------------------------*/
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /*--------------------------------------------------------------------------------*/
public:
    void backBaseWindow();

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*--------------------------------------------------------------------------------*/
private:
    Ui::MainWindow *ui;

    GameWindow g;
    LanBattle l;
    NetServer n;

private slots:
    // 主界面四个按钮的回调函数
    void on_Man_AI_clicked();
    void on_Man_Man_clicked();
    void on_Lan_Battle_clicked();
    void on_NetServer_clicked();
    /*--------------------------------------------------------------------------------*/
};

#endif // MAINWINDOW_H
