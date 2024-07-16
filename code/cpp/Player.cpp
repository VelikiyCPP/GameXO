#include "../hpp/Player.hpp"
#include "../hpp/OutputInformation.hpp"
#include "../hpp/Board.hpp"

std::size_t Player::userInput(std::string messageBeforeCin) noexcept {
    const short int maxNumber = (Board::boardSize_ * Board::boardSize_);
    std::string text = "1 ~ " + static_cast<char>(48 + maxNumber); 
    std::size_t userInputValue;

    std::cout << messageBeforeCin;
    std::cin >> userInputValue;
    while (std::cin.fail() || userInputValue < 1 || userInputValue > maxNumber) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << messageBeforeCin;
        std::cin >> userInputValue;
    }

    return userInputValue;
}