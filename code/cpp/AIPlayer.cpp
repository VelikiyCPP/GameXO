#include "../hpp/AIPlayer.hpp"

AIPlayer::AIPlayer(Board& board) : board_(&board), level_(1) {}

std::pair<std::size_t, std::size_t> AIPlayer::selectMoveAi(const int level) {
    switch (level) {
    case 1:
        return easyModel();
    case 2:
        return mediumModel();
    case 3:
        return mediumModel();
    }

    return { 0, 0 };
}

void AIPlayer::setLevel(const int level) noexcept {
    level_ = level;
}

int AIPlayer::getLevel() const noexcept {
    return level_;
}

std::pair<std::size_t, std::size_t> AIPlayer::easyModel()noexcept {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::size_t> dist(0, Board::boardSize_ - 1);

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

std::pair<std::size_t, std::size_t> AIPlayer::mediumModel() noexcept {
    std::pair<std::size_t, std::size_t> bestMove;
    int bestScore = std::numeric_limits<int>::min();

    // Устанавливаем таймаут для поиска хода
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = start + std::chrono::seconds(board_->getSizeMap() - 1); // Увеличиваем таймаут до 10 секунд

    while (std::chrono::steady_clock::now() < end) {
        for (std::size_t row = 0; row < board_->getSizeMap(); ++row) {
            for (std::size_t col = 0; col < board_->getSizeMap(); ++col) {
                if (board_->isValidMove(row, col)) {
                    Board newBoard = *board_;
                    newBoard.makeMove(row, col, setting_.symbol());
                    int score = minimax(newBoard, 0, false, 6, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()); // Ограничиваем глубину рекурсии до 6, используем альфа-бета отсечение
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = std::make_pair(row, col);
                    }
                }
            }
        }
    }

    // Если средний ИИ не смог найти ход за 10 секунд, вызываем простой ИИ
    if (bestScore == std::numeric_limits<int>::min()) {
        return easyModel();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<std::time_t>(rand() % 1800)));

    return bestMove;
}

int AIPlayer::minimax(Board& board, int depth, bool isMaximizing, int maxDepth, int alpha, int beta) noexcept {
    if (depth == maxDepth || board.isWinner(setting_.symbol(), level_) || board.isWinner(setting_.getSelectSymbolForAi(), 0) || board.isTie()) {
        if (board.isWinner(setting_.symbol(), level_)) {
            return 10 - depth; // Возвращаем положительный счет, если ИИ выиграл
        }
        if (board.isWinner(setting_.getSelectSymbolForAi(), 0)) {
            return depth - 10; // Возвращаем отрицательный счет, если ИИ проиграл
        }
        if (board.isTie()) {
            return 0; // Возвращаем 0 в случае ничьей
        }
        // Здесь можно добавить эвристическую оценку позиции
        return 0;
    }

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (std::size_t row = 0; row < board.getSizeMap(); ++row) {
            for (std::size_t col = 0; col < board.getSizeMap(); ++col) {
                if (board.isValidMove(row, col)) {
                    Board newBoard = board;
                    newBoard.makeMove(row, col, setting_.symbol());
                    int score = minimax(newBoard, depth + 1, false, maxDepth, alpha, beta);
                    if (score > 0) { // Если есть ход, ведущий к победе, возвращаем его
                        return score;
                    }
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, score);
                    if (beta <= alpha) {
                        break; // Отсекаем ветвь, если она не может дать лучший результат
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (std::size_t row = 0; row < board.getSizeMap(); ++row) {
            for (std::size_t col = 0; col < board.getSizeMap(); ++col) {
                if (board.isValidMove(row, col)) {
                    Board newBoard = board;
                    newBoard.makeMove(row, col, setting_.getSelectSymbolForAi());
                    int score = minimax(newBoard, depth + 1, true, maxDepth, alpha, beta);
                    if (score < 0) { // Если есть ход, предотвращающий поражение, возвращаем его
                        return score;
                    }
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, score);
                    if (beta <= alpha) {
                        break; // Отсекаем ветвь, если она не может дать лучший результат
                    }
                }
            }
        }
        return bestScore;
    }
}