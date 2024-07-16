#pragma once

#include <chrono>
#include <random>
#include <thread>
#include <utility>

#include "Board.hpp"
#include "../hpp/Setting.hpp"

class AIPlayer {
public:
    AIPlayer(Board& board);
    std::pair<std::size_t, std::size_t> selectMoveAi(const int level = 1);
    void setLevel(const int level) noexcept;
    std::pair<std::size_t, std::size_t> easyModel()noexcept;
    std::pair<std::size_t, std::size_t> mediumModel()noexcept;
    
    int minimax(Board& board, int depth, bool isMaximizing, int maxDepth, int alpha, int beta)noexcept;
    int getLevel() const noexcept;

private:
    std::pair<std::size_t, std::size_t> selectMoveRandomAi();
    Board* board_;
    Setting setting_;
    int level_;
};