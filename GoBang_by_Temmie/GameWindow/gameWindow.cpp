#include "gameWindow.h"

#include <math.h>
/*--------------------------------------------------------------------------------*/
// GameWindow窗口创建
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon("://logo.ico"));
    // 设置GameWindow窗体大小
    setFixedSize(ChessBoardMargin * 2 + ChessBlockSize * (ChessBoardSize - 1), ChessBoardMargin * 2 + ChessBlockSize * (ChessBoardSize - 1));
    // 设置鼠标移动监听必须打开
    setMouseTracking(true);
    // 显示现在的下棋颜色
    showNowPlayer = new QLabel(this);
    showNowPlayer->setGeometry(30, 0, 100, 30);
    // 显示当前下棋选手的名字
    showName = new QLabel(this);
    showName->setGeometry(120, 0, 500, 30);
}

// 发送返回主界面的信号
void GameWindow::sendBackSlot()
{
    emit backBaseWindow();
}
/*--------------------------------------------------------------------------------*/
// 根据传过来的两个player来进行游戏初始化
void GameWindow::initGame(GameCore::user *play1, GameCore::user *play2)
{
    player1 = play1;
    player2 = play2;

    game = new GameCore;
    game->gameType = player1->gameType;
    game->player = true; // 默认先手颜色为黑色
    game_type = player1->gameType;
    game->gameStatus = PLAYING;

    game->player1 = *player1;
    game->player2 = *player2;
    game->startGame(&game->player1, &game->player2);
    update(); // 通过update函数维持游戏循环
}
/*--------------------------------------------------------------------------------*/
// 绘图事件，绘制GameWindow窗口棋盘等组件，通过update调用
void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // 获取和显示当前棋手的颜色
    QString color = game->player ? "Black" : "White";
    showNowPlayer->setText("# Color:" + color);
    QString username;
    std::string name;
    // 获取和显示当前棋手
    if (game->gameType == NET_PERSON)
    {
        name = game->player == game->player1.color ? "You" : "The Other";
    }
    else
    {
        if (game->player == game->player1.color)
            name = game->player1.name;
        else
            name = game->player2.name;
    }
    username = QString::fromStdString(name);
    showName->setText("# Player：" + username);
    /*--------------------------------------------------------------------------------*/
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    for (int i = 0; i < ChessBoardSize; i++)
    {
        painter.drawLine(ChessBoardMargin + ChessBlockSize * i,
                         ChessBoardMargin,
                         ChessBoardMargin + ChessBlockSize * i,
                         size().height() - ChessBoardMargin);
        painter.drawLine(ChessBoardMargin,
                         ChessBoardMargin + ChessBlockSize * i,
                         size().width() - ChessBoardMargin,
                         ChessBoardMargin + ChessBlockSize * i);
    }
    /*--------------------------------------------------------------------------------*/
    QBrush brush; // 画刷
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow >= 0 && clickPosRow < ChessBoardSize &&
        clickPosCol >= 0 && clickPosCol < ChessBoardSize &&
        game->gameMapVec[(unsigned)clickPosRow][(unsigned)clickPosCol] == 0)
    // 判断鼠标范围有效时
    {
        if (game->player)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        // 画一个实心矩形的落子标记
        painter.drawRect(ChessBoardMargin + ChessBlockSize * clickPosCol - ChessMarkSize / 2,
                         ChessBoardMargin + ChessBlockSize * clickPosRow - ChessMarkSize / 2,
                         ChessMarkSize, ChessMarkSize);
    }
    /*--------------------------------------------------------------------------------*/
    // 绘制棋子
    for (int i = 0; i < ChessBoardSize; i++)
        for (int j = 0; j < ChessBoardSize; j++)
        {
            // 绘制白棋子
            if (game->gameMapVec[(unsigned)i][(unsigned)j] == 1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(ChessBoardMargin + ChessBlockSize * j - ChessRadius,
                                    ChessBoardMargin + ChessBlockSize * i - ChessRadius,
                                    ChessRadius * 2, ChessRadius * 2);
            }
            // 绘制黑棋子
            if (game->gameMapVec[(unsigned)i][(unsigned)j] == -1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(ChessBoardMargin + ChessBlockSize * j - ChessRadius,
                                    ChessBoardMargin + ChessBlockSize * i - ChessRadius,
                                    ChessRadius * 2, ChessRadius * 2);
            }
        }
}
/*--------------------------------------------------------------------------------*/
// 鼠标移动检测事件
void GameWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= ChessBoardMargin &&
        x <= size().width() - ChessBoardMargin &&
        y >= ChessBoardMargin &&
        y <= size().height() - ChessBoardMargin)
    {
        // 获取最近的左上角的点
        int col = x / ChessBlockSize;
        int row = y / ChessBlockSize;

        int leftTopPosX = ChessBoardMargin + ChessBlockSize * col;
        int leftTopPosY = ChessBoardMargin + ChessBlockSize * row;
        /*--------------------------------------------------------------------------------*/
        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        // 初始化最终的值
        clickPosRow = -1;
        clickPosCol = -1;
        int len = 0;
        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < PosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - ChessBlockSize) * (x - leftTopPosX - ChessBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < PosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - ChessBlockSize) * (y - leftTopPosY - ChessBlockSize));
        if (len < PosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - ChessBlockSize) * (x - leftTopPosX - ChessBlockSize) + (y - leftTopPosY - ChessBlockSize) * (y - leftTopPosY - ChessBlockSize));
        if (len < PosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
        /*--------------------------------------------------------------------------------*/
        update();
    }
}
/*--------------------------------------------------------------------------------*/
// 鼠标点击事件
void GameWindow::mouseReleaseEvent(QMouseEvent *)
{
    // 鼠标点击处务必在格子内，而且该点必须无棋子
    if (clickPosCol >= 0 && clickPosRow >= 0 && clickPosCol < ChessBoardSize && clickPosRow < ChessBoardSize && game->gameMapVec[(unsigned)clickPosRow][(unsigned)clickPosCol] == 0)
    {
        /*--------------------------------------------------------------------------------*/
        // 本机玩家点击时，将本机玩家数据传输过去
        if (game_type == NET_PERSON && game->player1.color == game->player)
        {
            game->player1.col = clickPosCol;
            game->player1.row = clickPosRow;
            emit netPlayer1Chess(game->player1);
        }
        /*--------------------------------------------------------------------------------*/
        // 默认player1为本机玩家，联机对战中，player2为联机玩家
        if (game->player1.color == game->player)
        {
            game->player1.col = clickPosCol;
            game->player1.row = clickPosRow;

            if (game->player == game->player1.color)
            {
                chessOneByPerson(&game->player1);
            }
            // 人机模式时，AI延时
            if (game_type == BOT && game->player1.color != game->player)
            {
                // 随机数
                qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
                // 用定时器做一个随机延迟
                QTimer::singleShot(qrand() % 1500 + 500, this, [=]()
                                   { chessOneByAI(&game->player2); });
            }
        }
        /*--------------------------------------------------------------------------------*/
        // 本地双人模式
        else if (game->player2.color == game->player && game_type == LOCAL_PERSON)
        {
            game->player2.col = clickPosCol;
            game->player2.row = clickPosRow;
            chessOneByPerson(&game->player2);
        }
    }
}
/*--------------------------------------------------------------------------------*/
// 窗口关闭事件
void GameWindow::closeEvent(QCloseEvent *)
{
    sendBackSlot();
}
/*--------------------------------------------------------------------------------*/
// 游戏结果判断
void GameWindow::judge(GameCore::user *play)
{
    /*--------------------------------------------------------------------------------*/
    // 判断死局
    if (game->isDraw())
    {
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "draw!");
        if (btnValue == QMessageBox::Ok)
        {
            game->startGame(&game->player1, &game->player2);
            game->gameStatus = PLAYING;
        }
    }
    /*--------------------------------------------------------------------------------*/
    // 判断输赢
    if (game->isWin(play->row, play->col) && game->gameStatus == PLAYING)
    {
        game->gameStatus = WIN;
        QString winner;
        if (game->gameMapVec[(unsigned)play->row][(unsigned)play->col] == 1)
            winner = "Black";
        else if (game->gameMapVec[(unsigned)play->row][(unsigned)play->col] == -1)
            winner = "White";
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "Game Over", "Winner is " + winner);
        /*--------------------------------------------------------------------------------*/
        // 重置游戏状态
        if (btnValue == QMessageBox::Ok)
        {
            game->startGame(&game->player1, &game->player2);
            game->gameStatus = PLAYING;
        }
    }
}
/*--------------------------------------------------------------------------------*/
// 联机模式player2下棋
void GameWindow::chessOneByNet(GameCore::user *play)
{
    game->player2 = *play;
    if (game->player2.color == game->player)
    {
        game->actionByNet(&game->player2);
        update();
        GameWindow::judge(play);
    }
}
/*--------------------------------------------------------------------------------*/
// player下棋
void GameWindow::chessOneByPerson(GameCore::user *play)
{
    game->actionByPerson(play);
    update();
    GameWindow::judge(play);
}
/*--------------------------------------------------------------------------------*/
// AI下棋
void GameWindow::chessOneByAI(GameCore::user *play)
{
    game->actionByAI(play);
    update();
    GameWindow::judge(play);
}
/*--------------------------------------------------------------------------------*/
GameWindow::~GameWindow()
{
    // 清空游戏指针
    if (game)
    {
        delete game;
        game = nullptr;
    }
}
