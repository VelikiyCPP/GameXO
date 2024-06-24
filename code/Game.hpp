#pragma once

#include <chrono>
#include <fstream>
#include <thread>


#include "AIPlayer.hpp"
#include "Board.hpp"
#include "MenuItem.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "OutputInformation.hpp"
#include "Setting.hpp"

extern OutputInformation outputInformation;

class Game {
public:
    Game();
    void loadAllMenu();
    void updateAllMenu();
    const Menu& getMenu() const noexcept;
    void start() noexcept;
    void startLocalGame();
    void settingMenu();
    void sleep(std::time_t time);
    void exit() noexcept;
    void clear() noexcept;
    std::string getJsonText(const std::string& key);
    ~Game();

private:
    Player player_;
    AIPlayer AIPlayer_;
    Menu menu_, menuAi_, menuSetting_;
    Board board_;
    Setting setting_;
    bool gameDeath_;
    bool startAiGame_;
};