#include "scoreEngine.h"
/*--------------------------------------------------------------------------------*/
// 计算评分函数
std::vector<std::vector<int>> ScoreEngine::calculateScoreEngine(std::vector<std::vector<int>> gameMapVec, std::vector<std::vector<int>> scoreMapVec)
{
    // 统计玩家或者电脑连成的子
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0;    // AI连成子的个数
    int emptyNum = 0;  // 各方向空白位的个数

    // 清空评分数组
    scoreMapVec.clear();
    for (int i = 0; i < ChessBoardSize; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < ChessBoardSize; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }
    /*--------------------------------------------------------------------------------*/
    // 完全遍历计分法
    for (int row = 0; row < ChessBoardSize; row++)
        for (int col = 0; col < ChessBoardSize; col++)
        {
            // 空白点就算
            if (gameMapVec[(unsigned)row][(unsigned)col] == 0)
            {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;
                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子
                            /*--------------------------------------------------------------------------------*/
                            // 对玩家黑子评分（正反两个方向）
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y >= 0 && row + i * y < ChessBoardSize &&
                                    col + i * x >= 0 && col + i * x < ChessBoardSize &&
                                    gameMapVec[(unsigned)(row + i * y)][(unsigned)(col + i * x)] == 1) // 黑子
                                {
                                    personNum++;
                                }
                                else if (row + i * y >= 0 && row + i * y < ChessBoardSize &&
                                         col + i * x >= 0 && col + i * x < ChessBoardSize &&
                                         gameMapVec[(unsigned)(row + i * y)][(unsigned)(col + i * x)] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else // 出边界
                                    break;
                            }
                            /*--------------------------------------------------------------------------------*/
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y >= 0 && row - i * y < ChessBoardSize &&
                                    col - i * x >= 0 && col - i * x < ChessBoardSize &&
                                    gameMapVec[(unsigned)(row - i * y)][(unsigned)(col - i * x)] == 1) // 黑子
                                {
                                    personNum++;
                                }
                                else if (row - i * y >= 0 && row - i * y < ChessBoardSize &&
                                         col - i * x >= 0 && col - i * x < ChessBoardSize &&
                                         gameMapVec[(unsigned)(row - i * y)][(unsigned)(col - i * x)] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else // 出边界
                                    break;
                            }
                            /*--------------------------------------------------------------------------------*/
                            if (personNum == 1) // 杀二
                                scoreMapVec[(unsigned)row][(unsigned)col] += 10;
                            else if (personNum == 2) // 杀三
                            {
                                if (emptyNum == 1)
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 30;
                                else if (emptyNum == 2)
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 40;
                            }
                            else if (personNum == 3) // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 55;
                                else if (emptyNum == 2)
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 100;
                            }
                            else if (personNum == 4) // 杀五
                                scoreMapVec[(unsigned)row][(unsigned)col] += 10000;

                            // 进行一次清空
                            emptyNum = 0;
                            /*--------------------------------------------------------------------------------*/
                            // 对AI黑子评分
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y >= 0 && row + i * y < ChessBoardSize &&
                                    col + i * x >= 0 && col + i * x < ChessBoardSize &&
                                    gameMapVec[(unsigned)(row + i * y)][(unsigned)(col + i * x)] == -1) // 白子
                                {
                                    botNum++;
                                }
                                else if (row + i * y >= 0 && row + i * y < ChessBoardSize &&
                                         col + i * x >= 0 && col + i * x < ChessBoardSize &&
                                         gameMapVec[(unsigned)(row + i * y)][(unsigned)(col + i * x)] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else // 出边界
                                    break;
                            }
                            /*--------------------------------------------------------------------------------*/
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y >= 0 && row - i * y < ChessBoardSize &&
                                    col - i * x >= 0 && col - i * x < ChessBoardSize &&
                                    gameMapVec[(unsigned)(row - i * y)][(unsigned)(col - i * x)] == -1) // 白子
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < ChessBoardSize &&
                                         col - i * x > 0 && col - i * x < ChessBoardSize &&
                                         gameMapVec[(unsigned)(row - i * y)][(unsigned)(col - i * x)] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else // 出边界
                                    break;
                            }
                            /*--------------------------------------------------------------------------------*/
                            if (botNum == 0) // 普通下子
                                scoreMapVec[(unsigned)row][(unsigned)col] += 5;
                            else if (botNum == 1) // 活二
                                scoreMapVec[(unsigned)row][(unsigned)col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1) // 死三
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 25;
                                else if (emptyNum == 2)
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 50; // 活三
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1) // 死四
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 60;
                                else if (emptyNum == 2)
                                    scoreMapVec[(unsigned)row][(unsigned)col] += 110; // 活四
                            }
                            else if (botNum >= 4)
                                scoreMapVec[(unsigned)row][(unsigned)col] += 10100; // 活五
                        }
                    }
            }
        }
    return scoreMapVec;
}
