#include "../hpp/AIPlayer.hpp"

AIPlayer::AIPlayer(Board& board) : board_(&board), level_(1) {}

std::pair<std::size_t, std::size_t> AIPlayer::selectMoveAi(const int level) {
    switch (level) {
    case 1:
        return selectMoveRandomAi();
    }

    return { 0, 0 };
}

void AIPlayer::setLevel(const int level) noexcept {
    level_ = level;
}

int AIPlayer::getLevel() const noexcept {
    return level_;
}

std::pair<std::size_t, std::size_t> AIPlayer::selectMoveRandomAi() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::size_t> dist(0, 2);

    std::size_t row;
    std::size_t col;

    do {
        row = dist(mt);
        col = dist(mt);
    } while (!board_->isValidMove(row, col));

    std::this_thread::sleep_for(
        std::chrono::milliseconds(static_cast<std::time_t>(rand() % 1800)));

    return std::make_pair(row, col);
}