#include "Game.hpp"

namespace GameXO {
    
    OI::OutputInformation GameXO::outputInformation;

    Game::Game() : AIPlayer_(board_) {
        system("title Game X/O");
        srand(static_cast<unsigned int>(time(0)));

        std::locale::global(std::locale("ru_RU.UTF-8"));
        std::cout.imbue(std::locale());

        loadMessages();
        messageJson("game_created", 0);
        loadAllMenu();
    }

    void Game::loadAllMenu() {
        menu_.push_back(MenuItem(getTextFromJson("local_start_game_ai") + "                                  ", 1, nullptr));
        menu_.push_back(MenuItem(getTextFromJson("setting") + "                                              ", 2, nullptr));
        menu_.push_back(MenuItem(getTextFromJson("exit") + "                                                 ", 3, nullptr));

        menuAi_.push_back(MenuItem(getTextFromJson("easy_ai") + "                              ", 1, nullptr));
        menuAi_.push_back(MenuItem(getTextFromJson("middle_ai") + "                            ", 2, nullptr));
        menuAi_.push_back(MenuItem(getTextFromJson("exit") + "                                 ", 3, nullptr));

        menuSetting_.push_back(MenuItem(getTextFromJson("coins_count") + " - ", 0, &setting_.coin()));
        menuSetting_.push_back(MenuItem(getTextFromJson("choose_symbol") + " - ", 1, nullptr, std::to_string(setting_.symbol())));
        menuSetting_.push_back(MenuItem(getTextFromJson("turn_limit") + " - ", 2, &setting_.limitMove()));
        menuSetting_.push_back(MenuItem(getTextFromJson("board_size") + " - ", 3, &setting_.boardSize()));
        menuSetting_.push_back(MenuItem(getTextFromJson("cheats_mod") + " - ", 4, &setting_.cheatMode()));
        menuSetting_.push_back(MenuItem(getTextFromJson("language") + " - ", 5, nullptr, setting_.getLanguage() == "ru" ? "русский" : "english"));
        menuSetting_.push_back(MenuItem(getTextFromJson("exit") + " ;)", 6, nullptr));
    }

    void Game::updateAllMenu() {
        menu_.clear();
        menuAi_.clear();
        menuSetting_.clear();
        loadAllMenu();
    }

    const VisualMenu::Menu& Game::getMenu() const noexcept {
        return menu_;
    }

    void Game::start() noexcept {
        messageJson("Game start", 200);
        while (!gameDeath_) {
            menu_.showAllMenu();
            switch (player_.userInput()) {
            case 1:
                messageJson("local_ai_menu", 500);
                startLocalGame();
                break;
            case 2:
                settingMenu();
                break;
            case 3:
                exit();
                break;
            default:
                messageJson("numbers_of_one_to_three", 0);
            }

            clear();
        }
    }

    void Game::startLocalGame() {
        AIPlayer_.setLevel(0);
        startAiGame_ = true;

        clear();
        messageJson("start_local_game", 200);

        while (AIPlayer_.getLevel() == 0 && startAiGame_ == true) {
            menuAi_.showAllMenu();
            switch (player_.userInput()) {
            case 1:
                AIPlayer_.setLevel(1);
                break;
            case 2:
                messageJson("no created", 500);
                AIPlayer_.setLevel(1);
                break;
            case 3:
                startAiGame_ = false;
                break;
            default:
                messageJson("numbers_of_one_to_three", 0);
            }
        }

        if (startAiGame_) {
            std::string text;
            std::pair<std::size_t, std::size_t> placeValue;
            bool move = setting_.symbol() == 'X' ? true : false;

            messageJson("start_local_game", 500);

            while (startAiGame_) {
                board_.printBoard();
                if (move) {
                    placeValue.first = player_.userInput("Your move(0-9): ");

                    if (!(placeValue.first >= 1 && placeValue.first <= 9)) {
                        GameXO::outputInformation.messageFromGame(OI::typeMessage::WARNING, "Wrong input. Try again");
                        continue;
                    }

                    --placeValue.first;
                    placeValue = { placeValue.first / 3, placeValue.first % 3 };

                    board_.makeMove(placeValue.first, placeValue.second,
                        setting_.symbol());
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

                menuSetting_[1].setDopText(setting_.symbol() == 'R' ? "X/O" : std::to_string(setting_.symbol()));
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                setting_.changeLanguage();
                menuSetting_[5].setDopText(setting_.getLanguage());
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
        messageJson("exit_game", 500);
        gameDeath_ = true;
    }

    void Game::clear() noexcept {
        std::cout << "\033[2J\033[1;1H"; // clear
    }

    Game::~Game() {
        messageJson("game_abandoned", 2000);
    }

    void Game::loadMessages() {
        try {
            std::ifstream file("Data/language.json");
            nlohmann::json messagesJson = nlohmann::json::parse(file);
            messages_ = messagesJson["messages"];
        }
        catch (const std::ifstream::failure& e) {
            std::cerr << "Error opening file: " << e.what() << std::endl;
        }
        catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Key 'essages' not found in JSON object" << std::endl;
        }
    }

    void Game::messageJson(const std::string& key, const std::time_t time, const OI::typeMessage type) noexcept {
        nlohmann::json messageJson;
        nlohmann::json messages = messages_[setting_.getLanguage()];

        if (messages.find(key) != messages.end()) {
            messageJson = messages[key];
        }
        else {
            messageJson["text"] = key;
        }

        if (time != 0) {
            messageJson["time"] = time;
        }

        outputInformation.messageFromGame(messageJson);
    }

    std::string Game::getTextFromJson(const std::string& key) {
        nlohmann::json messages = messages_[setting_.getLanguage()];
        if (messages.find(key) != messages.end()) {
            if (messages[key].find("text") != messages[key].end()) {
                return messages[key]["text"];
            }
        }
        return "Unknown message: " + key;
    }
}