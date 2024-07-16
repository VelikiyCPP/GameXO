#include "../hpp/SaveProcess.hpp"
#include "../hpp/OutputInformation.hpp"

void SaveProcess::loadData() {
    std::ifstream file(filename_);
    
    if (file.is_open()) {
        std::string line;

        if (!std::getline(file, line)) {
            throw std::runtime_error(outputInformation_->getTextFromJson("file_contains_invalid_data"));
        }

        int saveTime;
        try {
            saveTime = std::stoi(line);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error(outputInformation_->getTextFromJson("file_contains_invalid_data"));
        }

        if(gameData_.time <= saveTime){
            gameData_.time = saveTime;
        }
        
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                try {
                    if (!(file >> gameData_.stats[i][j])) {
                        throw std::runtime_error(outputInformation_->getTextFromJson("file_contains_invalid_data"));
                    }
                } catch (...) {
                    throw std::runtime_error(outputInformation_->getTextFromJson("file_contains_invalid_data"));
                }
            }
        }
        file.close();
        return;
    }

    throw std::runtime_error(outputInformation_->getTextFromJson("file_cannot_be_opened"));
}

void SaveProcess::setLoadWayFile(std::string& nameFile) {
    filename_ = nameFile;
}

void SaveProcess::outputGameData() {
    std::cout << outputInformation_->getTextFromJson("loaded_data") << std::endl;
    std::cout << outputInformation_->getTextFromJson("time_spent_in_game") << ": " << (gameData_.time / 24 / 3600) << "d  " << (gameData_.time / 3600 % 24) << "h  " << (gameData_.time / 60 % 60) << "m  " << (gameData_.time % 60) << "s  " << '\n' << std::endl;

    std::cout << "\033[1;34m" << outputInformation_->getTextFromJson("stats_easy_level") << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("wins") << ": " << "\033[1;32m" << gameData_.stats[0][0] << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("draws") << ": " << "\033[1;33m" << gameData_.stats[0][1] << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("losses") << ": " << "\033[1;31m" << gameData_.stats[0][2] << "\033[0m" << '\n' << std::endl;

    std::cout << "\033[1;34m" << outputInformation_->getTextFromJson("stats_middle_level") << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("wins") << ": " << "\033[1;32m" << gameData_.stats[1][0] << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("draws") << ": " << "\033[1;33m" << gameData_.stats[1][1]  << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("losses") << ": " << "\033[1;31m" << gameData_.stats[1][2] << "\033[0m" << '\n' << std::endl;

    std::cout << "\033[1;34m" << outputInformation_->getTextFromJson("stats_hard_level") << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("wins") << ": " << "\033[1;32m" << gameData_.stats[2][0] << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("draws") << ": " << "\033[1;33m" << gameData_.stats[2][1] << "\033[0m" << std::endl;
    std::cout << outputInformation_->getTextFromJson("losses") << ": " << "\033[1;31m" << gameData_.stats[2][2] << "\033[0m" << '\n' << std::endl;
}

void SaveProcess::updateGameData(int hardAI, int victoryTieDefeat) {
    std::ifstream file(filename_);
        
    if (!file.is_open()) {
        throw std::runtime_error(outputInformation_->getTextFromJson("file_cannot_be_opened") + filename_);
    }

    if((hardAI <= 0 || victoryTieDefeat <= 0) || (hardAI-- > 3 || victoryTieDefeat > 3)){
        throw std::runtime_error(outputInformation_->getTextFromJson("invalid_values_for_difficulty_and_wins"));
    }
    
    std::string line;
    
    {
        const std::size_t result = victoryTieDefeat + hardAI * 3;
        
        for(std::size_t i{}; i < result; ++i){
            std::getline(file, line);

            if(i == result - 1){
                ++gameData_.stats[hardAI][victoryTieDefeat - 1];

                std::ofstream modificationFile(filename_, std::ios::trunc);

                if(!modificationFile.is_open()){
                    throw std::runtime_error(outputInformation_->getTextFromJson("file_cannot_be_opened") + filename_);
                }

                modificationFile << std::to_string(gameData_.time) << "\n";
                for(int x = 0; x < 3; ++x){
                    for(int j = 0; j < 3; ++j){
                        modificationFile << std::to_string(gameData_.stats[x][j]) << "\n"; // Записываем статистики
                    }
                }

                modificationFile.close();
                file.close();

                loadData();

                break;
            }
        }

    }    
}

void SaveProcess::timerTime() {
    while(!off__){
        ++gameData_.time;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
