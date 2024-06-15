#include "Player.hpp"
#include "OutputInformation.hpp" // Include the OutputInformation header file

std::size_t Player::userInput(std::string messageBeforeCin) noexcept {
    std::size_t userInputValue;

    std::cout << messageBeforeCin;
    std::cin >> userInputValue;
    while (std::cin.fail() || userInputValue < 1 || userInputValue > 9) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        OI::OutputInformation diac(false); // Create an instance of OutputInformation
        diac.messageFromGame(OI::typeMessage::WARNING,
            "Wrong input. Try again");

        std::cout << messageBeforeCin;
        std::cin >> userInputValue;
    }

    return userInputValue;
}