#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>

#include "../hpp/Board.hpp"

Board::Board() {
    board_.resize(boardSizeMax_); board_.shrink_to_fit();

    for (std::size_t i = 0; i < boardSizeMax_; ++i) {
        board_[i].resize(boardSizeMax_); board_[i].shrink_to_fit();
        for (std::size_t j = 0; j < boardSizeMax_; ++j) {
            board_[i][j] = HealthByte(boardSize_ + 1, '-');
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
    for (std::size_t i = 0; i < boardSize_; ++i) {
        for (std::size_t j = 0; j < boardSize_; ++j) {
            if(j == 0){
                std::cout << std::setw(2) << std::setfill(' ') << "\033[1;36m" << (j + 1 + boardSize_ * i) << '\t' << "\033[2;32m";
            }

            if (board_[i][j].byte_ == 'X') {
                std::cout << (board_[i][j].health_ > 1 ? "\033[1;31m" : "\033[1;97m")
                    << " " << board_[i][j].byte_ << " \033[0m";
            }
            else if (board_[i][j].byte_ == 'O') {
                std::cout << (board_[i][j].health_ > 1 ? "\033[1;32m" : "\033[1;97m")
                    << " " << board_[i][j].byte_ << " \033[0m";
            }
            else {
                std::cout << " " << '.' << " ";
            }

            if(j == boardSize_ - 1){
                std::cout << "   \t\033[1;36m" << (j + 1) * (i + 1) << "\033[0m";
            }
        }
        std::cout << "\n\n";
    }
    std::cout << '\n';
}
void Board::resetBoard() noexcept {
    for (auto& rows : board_) {
        for (auto& element : rows) {
            element.byte_ = '-';
            element.health_ = boardSize_ + 1;
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
                board_[i][j].health_ = boardSize_ + 1;
            }
        }
    }
}

void Board::removeCurrentSymbol(const char byte) noexcept {
    for (std::size_t i{}; i < boardSizeMax_; ++i){
        for (std::size_t j{}; j < boardSizeMax_; ++j){
            board_[i][j].health_ = boardSize_;
            if(board_[i][j].byte_ == byte && board_[i][j].health_ < 1001){
                board_[i][j].byte_ = '-';
                board_[i][j].health_ = boardSize_ + 1;
            }
        }
    }
}

std::size_t Board::incrementNewSize()noexcept {
    if(++boardSize_ == 6){
        boardSize_ = 3;
    }
    resetBoard();
    return boardSize_;
}

char Board::getCell(const int x, const int y)const noexcept {
    return board_[x][y].byte_;
}

std::size_t Board::getSizeMap()const noexcept {
    return boardSize_;
}

bool  Board::isWinner(const char symbol, const std::size_t levelAI) noexcept {    
    
    for (std::size_t row = 0; row < boardSize_; ++row) {
        if (std::all_of(board_[row].begin(), board_[row].begin() + boardSize_, [symbol](const auto& cell) { return cell.byte_ == symbol; })) {
            for (std::size_t i = 0; i < boardSize_; ++i) {
                for (std::size_t j = 0; j < boardSize_; ++j) {
                    if (i != row) {
                        board_[i][j].byte_ = '-';
                    }
                }
            }
            return true;
        }
    }

    // Проверка столбцов
    if(levelAI != 3){
        for (std::size_t col = 0; col < boardSize_; ++col) {
            if (std::all_of(board_.begin(), board_.begin() + boardSize_, [col, symbol](const auto& row) { return row[col].byte_ == symbol; })) {
                for (std::size_t i = 0; i < boardSize_; ++i) {
                    for (std::size_t j = 0; j < boardSize_; ++j) {
                        if (j != col) {
                            board_[i][j].byte_ = '-';
                        }
                    }
                }
                return true;
            }
        }
    }

    // Проверка главной диагонали
    bool mainDiagonal = true;
    for (std::size_t i = 0; i < boardSize_; ++i) {
        if (board_[i][i].byte_ != symbol) {
            mainDiagonal = false;
            break;
        }
    }
    if (mainDiagonal) {
        for (std::size_t i = 0; i < boardSize_; ++i) {
            for (std::size_t j = 0; j < boardSize_; ++j) {
                if (i != j) {
                    board_[i][j].byte_ = '-';
                }
            }
        }
        return true;
    }

    // Проверка побочной диагонали
    bool antiDiagonal = true;
    for (std::size_t i = 0; i < boardSize_; ++i) {
        if (board_[i][boardSize_ - 1 - i].byte_ != symbol) {
            antiDiagonal = false;
            break;
        }
    }
    if (antiDiagonal) {
        for (std::size_t i = 0; i < boardSize_; ++i) {
            for (std::size_t j = 0; j < boardSize_; ++j) {
                if (board_[i][boardSize_ - 1 - i].byte_ == symbol) {
                    continue;
                }
                board_[i][j].byte_ = '-';
            }
        }
        return true;
    }

    return false;

}

bool Board::isTie() noexcept {
    int countSymbol{};
    for(const auto& row : board_){
        for(const auto& element : row){
            if(element.byte_ == '-'){
                continue;
            }
            ++countSymbol;
        }
    }

    if(countSymbol == boardSize_ * boardSize_){
        return true;
    }

    return false;
}

bool        Board::isValidMove(const std::size_t row, const std::size_t col) noexcept {
    return row < boardSize_ && row >= 0 && col < boardSize_ && col >= 0 && board_[row][col].byte_ == '-';
}
bool        Board::isFree(const std::size_t y, const std::size_t x) const noexcept {
    if (board_[y][x].byte_ == '-') {
        return true;
    }

    return false;
}

void Board::undoMove(const int x, const int y)noexcept {
    board_[y][x].byte_ = '-';
    board_[y][x].health_ = boardSize_ + 1;
}