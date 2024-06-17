#include "Game.hpp"

OutputInformation outputInformation;

Game::Game() : AIPlayer_(board_) {
    system("title Game X/O");
    srand(static_cast<unsigned int>(time(0)));

    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    outputInformation.loadMessages(setting_.getLanguage());
    outputInformation.messageJson("game_created", 0);
    loadAllMenu();
}

void Game::loadAllMenu() {
    menu_.push_back(MenuItem("1. " + getJsonText("local_start_game_ai")));
    menu_.push_back(MenuItem("2. " + getJsonText("setting")));
    menu_.push_back(MenuItem("3. " + getJsonText("exit")));

    menuAi_.push_back(MenuItem("1. " + getJsonText("easy_ai")));
    menuAi_.push_back(MenuItem("2. " + getJsonText("middle_ai")));
    menuAi_.push_back(MenuItem("3. " + getJsonText("exit")));

    menuSetting_.push_back(MenuItem("1. " + getJsonText("coins_count") + " - ", setting_.coin()));
    menuSetting_.push_back(MenuItem("2. " + getJsonText("choose_symbol") + " - ", setting_.symbol()));
    menuSetting_.push_back(MenuItem("3. " + getJsonText("turn_limit") + " - ", setting_.limitMove()));
    menuSetting_.push_back(MenuItem("4. " + getJsonText("board_size") + " - ", setting_.boardSize()));
    menuSetting_.push_back(MenuItem("5. " + getJsonText("cheats_mod") + " - ", setting_.cheatMode()));
    menuSetting_.push_back(MenuItem("6. " + getJsonText("language") + " - ", setting_.getLanguage() == "ru" ? "русский" : "english"));
    menuSetting_.push_back(MenuItem("7. " + getJsonText("exit")));
}

void Game::updateAllMenu() {
    menu_.clear();
    menuAi_.clear();
    menuSetting_.clear();
    loadAllMenu();
}

const Menu& Game::getMenu() const noexcept {
    return menu_;
}

void Game::start() noexcept {
    outputInformation.messageJson("Game start", 200);
    while (!gameDeath_) {
        menu_.showAllMenu();
        switch (player_.userInput()) {
        case 1:
            outputInformation.messageJson("local_ai_menu", 500);
            startLocalGame();
            break;
        case 2:
            settingMenu();
            break;
        case 3:
            exit();
            break;
        default:
            outputInformation.messageJson("numbers_of_one_to_three", 0);
        }

        clear();
    }
}

void Game::startLocalGame() {
    AIPlayer_.setLevel(0);
    startAiGame_ = true;

    clear();
    outputInformation.messageJson("start_local_game", 200);

    while (AIPlayer_.getLevel() == 0 && startAiGame_ == true) {
        menuAi_.showAllMenu();
        switch (player_.userInput()) {
        case 1:
            AIPlayer_.setLevel(1);
            break;
        case 2:
            outputInformation.messageJson("no created", 500);
            AIPlayer_.setLevel(1);
            break;
        case 3:
            startAiGame_ = false;
            break;
        default:
            outputInformation.messageJson("numbers_of_one_to_three", 0);
        }
    }

    if (startAiGame_) {
        std::string text;
        std::pair<std::size_t, std::size_t> placeValue;
        bool move = setting_.symbol() == 'X' ? true : false;

        outputInformation.messageJson("start_local_game", 500);
        setting_.loadRandomSelectSymbol();

        while (startAiGame_) {
            board_.printBoard();
            if (move) {
                placeValue.first = player_.userInput("Your move(0-9): ");

                if (!(placeValue.first >= 1 && placeValue.first <= 9)) {
                    outputInformation.messageFromGame(typeMessage::WARNING, "Wrong input. Try again", 0);
                    continue;
                }

                --placeValue.first;
                placeValue = { placeValue.first / 3, placeValue.first % 3 };

                board_.makeMove(placeValue.first, placeValue.second, setting_.symbol());
                board_.minusAllHealthByte(setting_.symbol());

                if (board_.isWinner(setting_.symbol())) {
                    clear();
                    board_.printBoard();
                    std::cout << "\033[1;32m" << "You win!" << "\033[0m" << std::endl;
                    break;
                }

            }
            else {
                placeValue = AIPlayer_.selectMoveAi(AIPlayer_.getLevel());

                board_.makeMove(placeValue.first, placeValue.second, setting_.getSelectSymbolForAi());
                board_.minusAllHealthByte(setting_.getSelectSymbolForAi());

                if (board_.isWinner(setting_.getSelectSymbolForAi())) {
                    board_.printBoard();
                    std::cout << "\033[1;31m" << "AI winers" << "\033[0m" << std::endl;
                    break;
                }
            }

            move = !move;
            clear();
        }
    }
}

void Game::settingMenu() {
    bool isActiveSettingMenu = true;
    while (isActiveSettingMenu) {
        clear();
        menuSetting_.showAllMenu();
        switch (player_.userInput()) {
        case 1:
            if (setting_.symbol() == 'X') {
                setting_.symbol() = 'O';
            }
            else if (setting_.symbol() == 'O') {
                setting_.symbol() = 'R';
            }
            else {
                setting_.symbol() = 'X';
            }

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            
            setting_.changeLanguage();
            outputInformation.setLanguage(setting_.getLanguage());
            updateAllMenu();
            break;
        case 6:
            isActiveSettingMenu = false;
            break;
        }
    }
}

void Game::sleep(std::time_t time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void Game::exit() noexcept {
    outputInformation.messageJson("exit_game", 500);
    gameDeath_ = true;
}

void Game::clear() noexcept {
    std::cout << "\033[2J\033[1;1H"; // clear
}

std::string Game::getJsonText(const std::string& key) {
    return outputInformation.getTextFromJson(key);
}

Game::~Game() {
    outputInformation.messageJson("game_abandoned", 2000);
}