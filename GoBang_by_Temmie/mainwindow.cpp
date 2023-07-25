#include "mainWindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
/*--------------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://logo.ico"));
    // 菜单栏里的返回开始界面按钮的link
    connect(&g, &GameWindow::backBaseWindow, this, &MainWindow::backBaseWindow);
    /*--------------------------------------------------------------------------------*/
    // 联机游戏行为link
    // 初始化游戏，接受LanBattle窗口传来player对象来初始化游戏
    connect(&l, &LanBattle::initGame, &g, &GameWindow::initGame);
    // 初始化游戏时，游戏界面显示
    connect(&l, &LanBattle::initGame, this, [=]()
            {
        g.show(); });
    // 联机模式下，当本地下棋之后，将player1传给服务端，由服务端转发给对方
    connect(&g, &GameWindow::netPlayer1Chess, &l, &LanBattle::slotNextChess);
    // 联机模式下，当对方下棋之后，接收传来的数据，并将其在本地进行操作
    connect(&l, &LanBattle::hasNextChess, &g, &GameWindow::chessOneByNet);
    // 当联机时，双方连接中断后，进行弹窗警告，并返回主界面
    connect(&l, &LanBattle::hasDisconnected, this, [=]()
            {
        QMessageBox::warning(&g,"Game Over","Disconnected",QMessageBox::Yes);
        MainWindow::backBaseWindow(); });
    /*--------------------------------------------------------------------------------*/
}

// 返回开始界面
void MainWindow::backBaseWindow()
{
    g.close();
    this->show();
}
/*--------------------------------------------------------------------------------*/
// 四个按钮的回调函数
void MainWindow::on_Man_AI_clicked()
{
    GameType type = BOT;
    GameCore::user player1;
    GameCore::user player2;

    player1.gameType = type;
    player2.gameType = type;

    player1.color = true;
    player2.color = false;

    player1.name = "Human";
    player2.name = "AI";

    g.initGame(&player1, &player2);
    g.setWindowTitle("Man-AI Battle");
    g.show();
    this->hide();
}

void MainWindow::on_Man_Man_clicked()
{
    GameType type = LOCAL_PERSON;
    GameCore::user player1;
    GameCore::user player2;

    player1.gameType = type;
    player2.gameType = type;

    player1.color = true;
    player2.color = false;

    player1.name = "1P";
    player2.name = "2P";

    g.initGame(&player1, &player2);
    g.setWindowTitle("Man-Man Battle");
    g.show();
    this->hide();
}

void MainWindow::on_Lan_Battle_clicked()
{
    l.show();
    l.move((QApplication::desktop()->width() - l.width()) / 3,
           (QApplication::desktop()->height() - l.height()) / 4);
}

void MainWindow::on_NetServer_clicked()
{
    n.show();
    n.move((QApplication::desktop()->width() - n.width()) / 6,
           2 * (QApplication::desktop()->height() - n.height()) / 3);
}
/*--------------------------------------------------------------------------------*/
MainWindow::~MainWindow()
{
    delete ui;
}
