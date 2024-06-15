#include "OutputInformation.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>

namespace OI {
    void OutputInformation::messageFromGame(const OI::typeMessage messageType, const std::string& message, const std::time_t time) const noexcept {

        std::string injectText;

        switch (messageType) {
        case OI::typeMessage::ERROR:
            injectText = "\033[1;31m[ERROR]:   "; // красный цвет
            break;
        case OI::typeMessage::INFO:
            injectText = "\033[1;35m[INFO]:    "; // синий цвет
            break;
        case OI::typeMessage::WARNING:
            injectText = "\033[1;33m[WARNING]: "; // желтый цвет
            break;
        case OI::typeMessage::SUCCESS:
            injectText = "\033[1;32m[SUCCESS]: "; // зеленый цвет
            break;
        case OI::typeMessage::DEBUG:
            injectText = "\033[1;97m[DEBUG]:   "; // светло-белый цвет
            break;
        case OI::typeMessage::SYSTEM:
            injectText = "\033[3;94m[SYSTEM]:   "; // светло-белый цвет
            break;
        default:
            injectText = "\033[1;91m[UNKOWN]:  "; // светло-красный цвет
            break;
        }

        std::cout << injectText << "\033[0m" << message << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    void OutputInformation::messageFromGame(const nlohmann::json& messageJson) const noexcept {
        if (messageJson.find("type") != messageJson.end() &&
            messageJson["type"] != "ERROR") {
            return;
        }

        std::string injectText;

        OI::typeMessage messageType;
        if (messageJson.find("type") != messageJson.end()) {
            if (messageJson["type"] == "ERROR") {
                messageType = OI::typeMessage::ERROR;
            }
            else if (messageJson["type"] == "INFO") {
                messageType = OI::typeMessage::INFO;
            }
            else if (messageJson["type"] == "WARNING") {
                messageType = OI::typeMessage::WARNING;
            }
            else if (messageJson["type"] == "SUCCESS") {
                messageType = OI::typeMessage::SUCCESS;
            }
            else if (messageJson["type"] == "DEBUG") {
                messageType = OI::typeMessage::DEBUG;
            }
            else if (messageJson["type"] == "SYSTEM") {
                messageType = OI::typeMessage::SYSTEM;
            }
            else {
                messageType = OI::typeMessage::UNKNOWN;
            }
        }
        else {
            messageType = OI::typeMessage::UNKNOWN;
        }

        switch (messageType) {
        case OI::typeMessage::ERROR:
            injectText = "\033[1;31m[ERROR]:   "; // красный цвет
            break;
        case OI::typeMessage::INFO:
            injectText = "\033[1;35m[INFO]:    "; // синий цвет
            break;
        case OI::typeMessage::WARNING:
            injectText = "\033[1;33m[WARNING]: "; // желтый цвет
            break;
        case OI::typeMessage::SUCCESS:
            injectText = "\033[1;32m[SUCCESS]: "; // зеленый цвет
            break;
        case OI::typeMessage::DEBUG:
            injectText = "\033[1;97m[DEBUG]:   "; // светло-белый цвет
            break;
        case OI::typeMessage::SYSTEM:
            injectText = "\033[3;94m[SYSTEM]:   "; // светло-белый цвет
            break;
        default:
            injectText = "\033[1;91m[UNKOWN]:  "; // светло-красный цвет
            break;
        }

        std::string messageText;
        if (messageJson.find("text") != messageJson.end()) {
            messageText = messageJson["text"];
        }
        else {
            messageText = "Unknown message";
        }

        std::cout << injectText << "\033[0m" << messageText << "\n";    
        
        if (messageJson.find("time") != messageJson.end()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<std::time_t>(messageJson["time"])));
        }
    }

}