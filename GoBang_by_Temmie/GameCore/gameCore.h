#ifndef GAMECORE_H
#define GAMECORE_H

#include "BoardParams/boardParams.h"
#include "ScoreEngine/scoreEngine.h"

#include <iostream>
#include <vector>
#include <stack>

#include <QTcpSocket>
/*--------------------------------------------------------------------------------*/
class GameCore
{
/*--------------------------------------------------------------------------------*/
public:
    // player数据结构体
    typedef struct user
    {
        QString NET_NAME; //序列化名称
        std::string name; //非序列化名称
        bool color;
        int row;
        int col;
        requestType request;
        GameType gameType;
    } user;

    std::vector<std::vector<int>> gameMapVec;  // 存储当前下子情况，空白为0，白为1，黑为-1
    std::vector<std::vector<int>> scoreMapVec; // 根据当前下子情况分析AI下棋分值

    bool player;							   // 标志当前该下棋的棋手颜色
    int surplusBoard;						   // 空棋盘位
    std::string player2name;                   //固定player2名称

    GameType gameType;						   // 游戏模式
    GameStatus gameStatus;					   // 游戏状态
    user player1;
    user player2;

    void startGame(user *, user *); // 开始游戏
    void actionByAI(user *);		// 机器下棋
    void actionByPerson(user *);	// 人执行下棋
    void actionByNet(user *);		// 联网执行下棋
    void updateGameMap(user *);		// 落子后更新棋盘

    bool isWin(int row, int col);	// 判断是否胜利
    bool isDraw();					// 判断平手

private:
    // 实例化评分表引擎
    ScoreEngine engine;
/*--------------------------------------------------------------------------------*/
};

#endif // GAMECORE_H
