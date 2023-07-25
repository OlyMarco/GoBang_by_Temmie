#include "gameCore.h"
/*--------------------------------------------------------------------------------*/
void GameCore::startGame(user *player1, user *)
{
    surplusBoard = ChessBoardSize * ChessBoardSize; // 变量剩余空位
    gameType = player1->gameType;
    gameMapVec.clear();
    scoreMapVec.clear();
    for (int i = 0; i < ChessBoardSize; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < ChessBoardSize; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }

    if (gameType == BOT)
    {
        for (int i = 0; i < ChessBoardSize; i++)
        {
            std::vector<int> lineBoard;
            for (int j = 0; j < ChessBoardSize; j++)
                lineBoard.push_back(0);
            scoreMapVec.push_back(lineBoard);
        }
    }
    player = true; // 默认先手黑棋
}
/*--------------------------------------------------------------------------------*/
void GameCore::updateGameMap(user *play)
{
    if (play->color)
        gameMapVec[(unsigned)play->row][(unsigned)play->col] = 1;
    else
        gameMapVec[(unsigned)play->row][(unsigned)play->col] = -1;
    player = !player;
}
/*--------------------------------------------------------------------------------*/
void GameCore::actionByPerson(user *play)
{
    updateGameMap(play);
}
/*--------------------------------------------------------------------------------*/
void GameCore::actionByNet(user *play)
{
    updateGameMap(play);
}
/*--------------------------------------------------------------------------------*/
void GameCore::actionByAI(user *play)
{
    // 获取评分表
    scoreMapVec = engine.calculateScoreEngine(gameMapVec, scoreMapVec);
    typedef struct point
    {
        int row = -1;
        int col = -1;
        int score = INT_MIN;
    } P;
    std::stack<point> pointStk;
    P maxPoint;
    maxPoint.score = INT_MIN;
    pointStk.push(maxPoint);
    for (int i = 0; i < ChessBoardSize; i++)
    {
        for (int j = 0; j < ChessBoardSize; j++)
        {
            if (gameMapVec[(unsigned)i][(unsigned)j] == 0) // 首先该位置不能已被占用
            {
                if (scoreMapVec[i][j] >= pointStk.top().score)
                {
                    maxPoint.row = i;
                    maxPoint.col = j;
                    maxPoint.score = scoreMapVec[(unsigned)i][(unsigned)j];
                    pointStk.push(maxPoint); // 遇到有最大的，直接入栈
                }
            }
        }
    }
    // 使用最后一个分值最大值的点作为AI下棋的点
    play->row = pointStk.top().row;
    play->col = pointStk.top().col;
    updateGameMap(play);
}
/*--------------------------------------------------------------------------------*/
// 每下一个棋子，对其周围是否凑成5个进行判断
bool GameCore::isWin(int row, int col)
{

    // 横向判断，判断该点是否一排五个点中的最右点，若不是，则向左位移一位再进行判断，位移四次
    for (int i = 0; i < 5; i++)
    {
        if (row + i < ChessBoardSize &&
            row + i - 4 >= 0 &&
            gameMapVec[(unsigned)(row + i)][(unsigned)col] ==
                gameMapVec[(unsigned)(row + i - 1)][(unsigned)col] &&
            gameMapVec[(unsigned)(row + i)][(unsigned)col] ==
                gameMapVec[(unsigned)(row + i - 2)][(unsigned)col] &&
            gameMapVec[(unsigned)(row + i)][(unsigned)col] ==
                gameMapVec[(unsigned)(row + i - 3)][(unsigned)col] &&
            gameMapVec[(unsigned)(row + i)][(unsigned)col] ==
                gameMapVec[(unsigned)(row + i - 4)][(unsigned)col])
            return true;
    }
    // 纵向判断，规则同上，判断是否最下点
    for (int i = 0; i < 5; i++)
    {
        if (col + i < ChessBoardSize &&
            col + i - 4 >= 0 &&
            gameMapVec[(unsigned)row][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)row][(unsigned)(col + i - 1)] &&
            gameMapVec[(unsigned)row][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)row][(unsigned)(col + i - 2)] &&
            gameMapVec[(unsigned)row][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)row][(unsigned)(col + i - 3)] &&
            gameMapVec[(unsigned)row][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)row][(unsigned)(col + i - 4)])
            return true;
    }
    // 左斜
    for (int i = 0; i < 5; i++)
    {
        if (col + i < ChessBoardSize &&
            col + i - 4 >= 0 &&
            row + i < ChessBoardSize &&
            row + i - 4 >= 0 &&
            gameMapVec[(unsigned)(row + i)][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)(row + i - 1)][(unsigned)(col + i - 1)] &&
            gameMapVec[(unsigned)(row + i)][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)(row + i - 2)][(unsigned)(col + i - 2)] &&
            gameMapVec[(unsigned)(row + i)][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)(row + i - 3)][(unsigned)(col + i - 3)] &&
            gameMapVec[(unsigned)(row + i)][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)(row + i - 4)][(unsigned)(col + i - 4)])
            return true;
    }
    // 右斜
    for (int i = 0; i < 5; i++)
    {
        if (col + i < ChessBoardSize &&
            col + i - 4 > 0 &&
            row - i > 0 &&
            row - i + 4 < ChessBoardSize &&
            gameMapVec[(unsigned)(row - i)][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)(row - i + 1)][(unsigned)(col + i - 1)] &&
            gameMapVec[(unsigned)(row - i)][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)(row - i + 2)][(unsigned)(col + i - 2)] &&
            gameMapVec[(unsigned)(row - i)][(unsigned)col + i] ==
                gameMapVec[(unsigned)(row - i + 3)][(unsigned)(col + i - 3)] &&
            gameMapVec[(unsigned)(row - i)][(unsigned)(col + i)] ==
                gameMapVec[(unsigned)(row - i + 4)][(unsigned)(col + i - 4)])
            return true;
    }
    return false;
}
/*--------------------------------------------------------------------------------*/
bool GameCore::isDraw()
{
    surplusBoard--;
    if (surplusBoard == 0)
        return true;
    return false;
}
