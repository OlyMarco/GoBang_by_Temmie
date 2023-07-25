#ifndef SCOREENGINE_H
#define SCOREENGINE_H

#include "BoardParams/boardParams.h"

#include <iostream>
#include <vector>

class ScoreEngine
{
public:
    // 评分表引擎函数
    std::vector<std::vector<int>> calculateScoreEngine(std::vector<std::vector<int>> gameMapVec, std::vector<std::vector<int>> scoreMapVec);
};

#endif // SCOREENGINE_H
