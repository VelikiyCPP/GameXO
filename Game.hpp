#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "AIPlayer.hpp"
#include "Board.hpp"
#include "Setting.hpp"
#include "MenuItem.hpp"
#include "Menu.hpp"
#include "OutputInformation.hpp"
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include <fstream>

namespace GameXO {
    extern OI::OutputInformation outputInformation;

    class Game {
    public:
        Game();
        void loadAllMenu();
        void updateAllMenu();
        const VisualMenu::Menu& getMenu() const noexcept;
        void start() noexcept;
        void startLocalGame();
        void settingMenu();
        void sleep(std::time_t time);
        void exit() noexcept;
        void clear() noexcept;
        ~Game();

    private:
        Player player_;
        AIPlayer AIPlayer_;
        VisualMenu::Menu menu_;
        VisualMenu::Menu menuAi_;
        VisualMenu::Menu menuSetting_;
        Board board_;
        Setting setting_;
        bool gameDeath_;
        bool startAiGame_;
        nlohmann::json messages_;

        void loadMessages();
        void messageJson(const std::string& key, const std::time_t time, const OI::typeMessage type = OI::typeMessage::UNKNOWN) noexcept;
        std::string getTextFromJson(const std::string& key);
    };
} // namespace GameXO

#endif // GAME_HPP