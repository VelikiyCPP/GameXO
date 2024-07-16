#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <thread>


#include "OutputInformation.hpp"

class SaveProcess
{
public:
    SaveProcess(const std::string& nameFile, OutputInformation& outputInformation) : filename_(nameFile), outputInformation_(&outputInformation) { loadData(); };
    SaveProcess() = default;

    void loadData();

    void setLoadWayFile(std::string& nameFile);

    void outputGameData();
    void updateGameData(int hardAI, int victoryTieDefeat);

    void timerTime();

    ~SaveProcess(){
        off__ = true;
        updateTime();
    }
private:
    struct GameData {
        //                   easy      medium      hard
        int time{};
        int stats  [3][3]{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    } gameData_;

    std::string filename_;
    bool off__{false};

    OutputInformation *outputInformation_;

    void updateTime() {
        std::ofstream modificationFile(filename_, std::ios::trunc);

        if(!modificationFile.is_open()){
            throw std::runtime_error(outputInformation_->getTextFromJson("file_cannot_be_opened"));
        }

        modificationFile << std::to_string(gameData_.time) << "\n";
        for(int x = 0; x < 3; ++x){
            for(int j = 0; j < 3; ++j){
                modificationFile << std::to_string(gameData_.stats[x][j]) << "\n"; // Записываем статистики
            }
        }

        modificationFile.close();
    }
};