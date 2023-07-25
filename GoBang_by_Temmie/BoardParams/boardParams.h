#ifndef BOARDPARAMS_H
#define BOARDPARAMS_H

const int ChessBoardSize = 15;   // 棋盘尺寸
const int ChessBoardMargin = 30; // 棋盘边缘空隙
const int ChessBlockSize = 40;   // 格子的大小
const int ChessRadius = 15;      // 棋子半径
const int ChessMarkSize = 6;     // 落子标记边长
const int PosDelta = 20;         // 鼠标点击的模糊距离上限

// 游戏类型，本地，联机，人机
enum GameType
{
    LOCAL_PERSON,
    NET_PERSON,
    BOT
};
// 游戏状态，进行中，胜利，失败，平局
enum GameStatus
{
    PLAYING,
    WIN,
    LOSE,
    DRAW,
    FREE
};
// 请求类型
enum requestType
{
    CONNECT,
    CONNECTED,
    NEXTCHESS,
    DISCONNECTED
};

#endif // BOARDPARAMS_H
