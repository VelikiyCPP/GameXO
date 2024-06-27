#include "../hpp/Player.hpp"
#include "../hpp/OutputInformation.hpp"

std::size_t Player::userInput(std::string messageBeforeCin) noexcept {
    std::size_t userInputValue;

    std::cout << messageBeforeCin;
    std::cin >> userInputValue;
    while (std::cin.fail() || userInputValue < 1 || userInputValue > 9) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        OutputInformation().messageFromGame(typeMessage::INFO, "1 ~ 3");

        std::cout << messageBeforeCin;
        std::cin >> userInputValue;
    }

    return userInputValue;
}