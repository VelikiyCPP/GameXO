#include "../hpp/Game.hpp"

#include <chrono>
#include <fstream>
#include <thread>

OutputInformation outputInformation;

Game::Game() : AIPlayer_(board_) {
    #if defined(_WIN32) || defined(_WIN64)
        #ifdef NDEBUG
            system("title Game X/O");
        #endif
    #endif

    clear();

    srand(static_cast<unsigned int>(time(0)));

    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());

    timer.detach();

    outputInformation.loadMessages(setting_.getLanguage());

    loadAllMenu();
}

void Game::loadAllMenu() {
    
    menu_.push_back(MenuItem("1. " + getJsonText("local_start_game_ai")));
    menu_.push_back(MenuItem("2. " + getJsonText("setting")));
    menu_.push_back(MenuItem("3. " + getJsonText("load_history")));
    menu_.push_back(MenuItem("4. " + getJsonText("exit")));

    menuAi_.push_back(MenuItem("1. " + getJsonText("easy_level")));
    menuAi_.push_back(MenuItem("2. " + getJsonText("middle_level")));
    menuAi_.push_back(MenuItem("3. " + getJsonText("hard_level"))); //
    menuAi_.push_back(MenuItem("4. " + getJsonText("exit")));

    menuSetting_.push_back(MenuItem("1. " + getJsonText("choose_symbol") + " - ", (setting_.supportSelectSymbol() != 'R' ? std::string(1, setting_.symbol()) : "X/O")));
    menuSetting_.push_back(MenuItem("2. " + getJsonText("turn_limit") + " - ", (setting_.getSelectLimit() < 100 ? std::to_string(setting_.getSelectLimit()) : "none")));
    menuSetting_.push_back(MenuItem("3. " + getJsonText("board_size") + " - ", setting_.boardSize()));
    menuSetting_.push_back(MenuItem("4. " + getJsonText("language") + " - ", setting_.getLanguage() == "ru" ? "русский" : "english"));
    menuSetting_.push_back(MenuItem("5. " + getJsonText(setting_.getMode())));
    menuSetting_.push_back(MenuItem("6. " + getJsonText("exit")));
}

void Game::updateAllMenu() {
    menu_.clear();
    menuAi_.clear();
    menuSetting_.clear();
    loadAllMenu();
}

void Game::start() noexcept {
    while (!gameDeath_) {
        menu_.showAllMenu();
        switch (player_.userInput()) {
        case 1:
            startLocalGame();
            break;
        case 2:
            settingMenu();
            break;
        case 3:
            saveProcess_.loadData();
            clear();
            saveProcess_.outputGameData();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ENTER]: ";
            std::cin.get();
            break;
        case 4:
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

    while (AIPlayer_.getLevel() == 0 && startAiGame_ == true) {
        menuAi_.showAllMenu();
        switch (player_.userInput()) {
        case 1: AIPlayer_.setLevel(1); break;
        case 2: AIPlayer_.setLevel(2); break;
        case 3: AIPlayer_.setLevel(3); break;
        case 4: startAiGame_ = false; break;
        default: outputInformation.messageJson("numbers_of_one_to_three", 0);
        }
    }

    if (startAiGame_) {
        setting_.limitCount() = setting_.getSelectLimit();

        if (setting_.supportSelectSymbol() == 'R') {
            setting_.loadRandomSelectSymbol();
        }

        std::string text;
        std::pair<std::size_t, std::size_t> placeValue;
        bool move = setting_.symbol() == 'X' ? true : false;

        auto standartAlgorithmWinner = [&](const int& value){
            clear();
            board_.removeCurrentSymbol(value == 1 ? setting_.getSelectSymbolForAi() : setting_.symbol());
            board_.printBoard();
            board_.resetBoard();
        
            saveProcess_.updateGameData(AIPlayer_.getLevel(), value);

            outputInformation.messageJson(value == 1 ? "you_win" : "ai_win", 0);
        };

        const bool isSurvivalMode = setting_.getMode() == "survival_mode";

        clear();

        while (startAiGame_) {
            if(board_.isTie()){
                clear();

                board_.resetBoard();
                board_.printBoard();

                outputInformation.messageJson("tie", 0);

                saveProcess_.updateGameData(AIPlayer_.getLevel(), 2);
                sleep(1500);
                break;
            } else {
                board_.printBoard();
            }

            if (move) {
                if(AIPlayer_.getLevel() == 3){outputInformation.messageJson("info_hard_mode", 0);}
                if(isSurvivalMode){
                    board_.minusAllHealthByte(setting_.symbol());
                    if(setting_.getSelectLimit() < 100){
                        std::cout << "limit: " << setting_.limitCount() << std::endl;
                    }
                }

                placeValue.first = player_.userInput("Your move(number): ");

                --placeValue.first;
                placeValue = { placeValue.first / board_.boardSize_, placeValue.first % board_.boardSize_ };

                if (!board_.makeMove(placeValue.first, placeValue.second, setting_.symbol())) {
                    clear();
                    outputInformation.messageJson("false_input_information", 0);
                    continue;
                }
                
                if (board_.isWinner(setting_.symbol(), AIPlayer_.getLevel())) {
                    standartAlgorithmWinner(1);
                    break;
                }

                if(isSurvivalMode){
                    if(--setting_.limitCount() == 0){
                        clear();

                        board_.printBoard();
                        board_.resetBoard();

                        outputInformation.messageJson("limit_end", 0);
                        break;
                    }
                }
            }
            else {
                placeValue = AIPlayer_.selectMoveAi(AIPlayer_.getLevel());

                board_.makeMove(placeValue.first, placeValue.second, setting_.getSelectSymbolForAi());
                
                if(setting_.getMode() == "survival_mode"){
                    board_.minusAllHealthByte(setting_.getSelectSymbolForAi());
                }

                if (board_.isWinner(setting_.getSelectSymbolForAi(), 0)) {
                    standartAlgorithmWinner(3);
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
            break;
        case 2:
            setting_.setNewLimit();
            break;
        case 3:
            setting_.boardSize() = board_.incrementNewSize();
            break;
        case 4:
            setting_.changeLanguage();
            outputInformation.setLanguage(setting_.getLanguage());
            break;
        case 5:
            setting_.newMode();
            break;
        case 6:
            isActiveSettingMenu = false;
            break;
        default:
            outputInformation.messageJson("false_input_information", 0);
        }
        updateAllMenu();
    }
}

const Menu& Game::getMenu() const noexcept {
    return menu_;
}

void Game::sleep(std::time_t time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void Game::exit() noexcept {
    outputInformation.messageJson("exit_game", 500);
    gameDeath_ = true;
}

void Game::clear() noexcept {
    std::cout << "\033[2J\033[1;1H";
}

std::string Game::getJsonText(const std::string& key) {
    return outputInformation.getTextFromJson(key);
}

Game::~Game() {
    saveProcess_.~SaveProcess();
    outputInformation.messageJson("game_abandoned", 2000);
}