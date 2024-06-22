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

    menuSetting_.push_back(MenuItem(getJsonText("coins_count") + " - ", setting_.coin()));
    menuSetting_.push_back(MenuItem("1. " + getJsonText("choose_symbol") + " - ", (setting_.supportSelectSymbol() != 'R' ? std::string(1, setting_.symbol()) : "X/O")));
    menuSetting_.push_back(MenuItem("2. " + getJsonText("turn_limit") + " - ", setting_.limitMove()));
    menuSetting_.push_back(MenuItem("3. " + getJsonText("board_size") + " - ", setting_.boardSize()));
    //menuSetting_.push_back(MenuItem("4. " + getJsonText("cheats_mod") + " - ", setting_.cheatMode()));
    menuSetting_.push_back(MenuItem("4. " + getJsonText("language") + " - ", setting_.getLanguage() == "ru" ? "ru" : "en"));
    menuSetting_.push_back(MenuItem("5. " + getJsonText("exit")));
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
        if (setting_.supportSelectSymbol() == 'R') {
            setting_.loadRandomSelectSymbol();
        }

        std::string text;
        std::pair<std::size_t, std::size_t> placeValue;
        bool move = setting_.symbol() == 'X' ? true : false;

        outputInformation.messageJson("start_local_game", 500);

        while (startAiGame_) {
            board_.printBoard();

            if (move) {
                placeValue.first = player_.userInput("Your move(0-9): ");

                --placeValue.first;
                placeValue = { placeValue.first / 3, placeValue.first % 3 };

                if (!board_.makeMove(placeValue.first, placeValue.second, setting_.symbol())) {
                    clear();
                    outputInformation.messageFromGame(typeMessage::WARNING, "Wrong input. Try again", 0);
                    continue;
                }

                board_.minusAllHealthByte(setting_.symbol());
                
                if (board_.isWinner(setting_.symbol())) {
                    clear();
                    board_.printBoard();
                    outputInformation.messageFromGame(typeMessage::INFO, "\033[1;32m You win! \033[0m", 555);
                    break;
                }

            }
            else {
                placeValue = AIPlayer_.selectMoveAi(AIPlayer_.getLevel());

                board_.makeMove(placeValue.first, placeValue.second, setting_.getSelectSymbolForAi());
                
                board_.minusAllHealthByte(setting_.getSelectSymbolForAi());

                if (board_.isWinner(setting_.getSelectSymbolForAi())) {
                    board_.printBoard();
                    outputInformation.messageFromGame(typeMessage::INFO, "\033[1;31m AI win! \033[0m", 555);
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
            if (setting_.supportSelectSymbol() == 'X') {
                setting_.symbol() = 'O';
                setting_.supportSelectSymbol() = 'O';
            }
            else if (setting_.supportSelectSymbol() == 'O') {
                setting_.supportSelectSymbol() = 'R';
            }
            else {
                setting_.symbol() = 'X';
                setting_.supportSelectSymbol() = 'X';
            }
            updateAllMenu();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            setting_.changeLanguage();
            outputInformation.setLanguage(setting_.getLanguage());
            updateAllMenu();
            break;
        case 5:
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