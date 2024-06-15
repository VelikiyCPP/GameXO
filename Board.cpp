#include "Board.hpp"

Board::Board() {
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            board_[i][j].byte_ = '-';
        }
    }
}

void Board::printBoard() const noexcept {
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            if (board_[i][j].byte_ == 'X') {
                std::cout << (board_[i][j].health_ > 1 ? "\033[1;31m" : "\033[1;97m")
                    << " " << board_[i][j].byte_ << " \033[0m";
            }
            else if (board_[i][j].byte_ == 'O') {
                std::cout << (board_[i][j].health_ > 1 ? "\033[1;32m" : "\033[1;97m")
                    << " " << board_[i][j].byte_ << " \033[0m";
            }
            else {
                std::cout << " " << i * 3 + j + 1 << " "; // выводим индекс ячейки
            }
        }
        std::cout << '\n';
    }
}

bool Board::isValidMove(const std::size_t row, const std::size_t col) noexcept {
    return row < 3 && col < 3 && board_[row][col].byte_ == '-';
}

bool Board::makeMove(const std::size_t row, const std::size_t col,
    const char symbol) noexcept {
    if (isValidMove(row, col)) {
        board_[row][col].byte_ = symbol;
        return true;
    }
    return false;
}

bool Board::isWinner(const char symbol) noexcept {
    // проверка по строкам
    for (const auto& row : board_) {
        if (row[0].byte_ == symbol && row[1].byte_ == symbol &&
            row[2].byte_ == symbol) {
            clearBoard();
            return true;
        }
    }

    // проверка по столбцам
    for (std::size_t col = 0; col < 3; ++col) {
        if (board_[0][col].byte_ == symbol && board_[1][col].byte_ == symbol &&
            board_[2][col].byte_ == symbol) {
            clearBoard();
            return true;
        }
    }

    // проверка по диагоналям
    if ((board_[0][0].byte_ == symbol && board_[1][1].byte_ == symbol &&
        board_[2][2].byte_ == symbol) ||
        (board_[0][2].byte_ == symbol && board_[1][1].byte_ == symbol &&
            board_[2][0].byte_ == symbol)) {
        clearBoard();
        return true;
    }

    return false;
}

void Board::clearBoard() {
    for (auto& row : board_) {
        for (auto& cell : row) {
            cell.byte_ = '-';
            cell.health_ = 4;
        }
    }
}

void Board::minusAllHealthByte(const char byte) noexcept {
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            if (board_[i][j].byte_ == byte && board_[i][j].health_ > 1) {
                board_[i][j].health_ -= 1;
            }
            else if (board_[i][j].byte_ == byte && board_[i][j].health_ == 1) {
                board_[i][j].byte_ = '-';
                board_[i][j].health_ = 4;
            }
        }
    }
}