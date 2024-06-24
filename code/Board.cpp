#include <iostream>
#include <algorithm>

#include "Board.hpp"

Board::Board() {
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            board_[i][j].byte_ = '-';
        }
    }
}


bool Board::makeMove(const std::size_t row, const std::size_t col, const char symbol) noexcept {
    if (isValidMove(row, col)) {
        board_[row][col].byte_ = symbol;
        return true;
    }
    return false;
}

void Board::printBoard() const noexcept {
    for (std::size_t i = 0; i < board_.size(); ++i) {
        for (std::size_t j = 0; j < board_.size(); ++j) {
            if (board_[i][j].byte_ == 'X') {
                std::cout << (board_[i][j].health_ > 1 ? "\033[1;31m" : "\033[1;97m")
                    << " " << board_[i][j].byte_ << " \033[0m";
            }
            else if (board_[i][j].byte_ == 'O') {
                std::cout << (board_[i][j].health_ > 1 ? "\033[1;32m" : "\033[1;97m")
                    << " " << board_[i][j].byte_ << " \033[0m";
            }
            else {
                std::cout << " " << i * board_.size() + j + 1 << " ";
            }
        }
        std::cout << '\n';
    }
}
void Board::resetBoard() noexcept {
    for (auto& rows : board_) {
        for (auto& cell : rows) {
            cell.byte_ = '-';
            cell.health_ = 4;
        }
    }
}
void Board::minusAllHealthByte(const char byte) noexcept {
    for (std::size_t i = 0; i < board_.size(); ++i) {
        for (std::size_t j = 0; j < board_.size(); ++j) {
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

void Board::removeCurrentSymbol(const char byte) noexcept {
    for (std::size_t i{}; i < board_.size(); ++i){
        for (std::size_t j{}; j < board_.size(); ++j){
            board_[i][j].health_ = board_.size();
            if(board_[i][j].byte_ == byte){
                board_[i][j].byte_ = '-';
                board_[i][j].health_ = 4;
            }
        }
    }
}

bool Board::isWinner(const char symbol) noexcept {
    for (const auto& row : board_) {
        if (std::all_of(row.begin(), row.end(), [&](const auto& cell) { return cell.byte_ == symbol; })) {
            return true;
        }
    }   

    for (std::size_t column = 0; column < 3; ++column) {
        if (std::all_of(board_.begin(), board_.end(), [&](const auto& row) { return row[column].byte_ == symbol; })) {
            return true;
        }
    }

    if ((board_[0][0].byte_ == symbol && board_[1][1].byte_ == symbol && board_[2][2].byte_ == symbol) ||
        (board_[0][2].byte_ == symbol && board_[1][1].byte_ == symbol && board_[2][0].byte_ == symbol)) {
        return true;
    }

    return false;
}
bool Board::isValidMove(const std::size_t row, const std::size_t col) noexcept {
    return row < 3 && row >= 0 && col < 3 && col >= 0 && board_[row][col].byte_ == '-';
}
bool Board::isFree(const std::size_t y, const std::size_t x) const noexcept {
    if (board_[y][x].byte_ == '-') {
        return true;
    }

    return false;
}