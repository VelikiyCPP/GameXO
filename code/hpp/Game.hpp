#pragma once

#include "AIPlayer.hpp"
#include "Board.hpp"
#include "MenuItem.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "OutputInformation.hpp"
#include "SaveProcess.hpp"
#include "Setting.hpp"

extern OutputInformation outputInformation;

class Game {
public:
    Game();

    Game(const Game&) = delete;
    Game(Game&&) noexcept = delete;
    
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) noexcept = delete;

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
    std::thread timer{&SaveProcess::timerTime, &saveProcess_};

    AIPlayer AIPlayer_;
    SaveProcess saveProcess_{"game_data.txt", outputInformation};
    Board board_;
    Menu menu_, menuAi_, menuSetting_;
    Player player_;
    Setting setting_;

    bool gameDeath_;
    bool startAiGame_;
};