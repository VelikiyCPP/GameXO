#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

#include "OutputInformation.hpp"

void OutputInformation::messageFromGame(const typeMessage messageType, const std::string& message, const std::time_t time) const noexcept {

    std::string injectText;

    switch (messageType) {
    case typeMessage::ERROR:
        injectText = "\033[1;31m[ERROR]:   "; // красный цвет
        break;
    case typeMessage::INFO:
        injectText = "\033[1;35m[INFO]:    "; // синий цвет
        break;
    case typeMessage::WARNING:
        injectText = "\033[1;33m[WARNING]: "; // желтый цвет
        break;
    case typeMessage::SUCCESS:
        injectText = "\033[1;32m[SUCCESS]: "; // зеленый цвет
        break;
    case typeMessage::DEBUG:
        injectText = "\033[1;97m[DEBUG]:   "; // светло-белый цвет
        break;
    case typeMessage::SYSTEM:
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
    typeMessage messageType;
    if (messageJson.find("type") != messageJson.end()) {
        if (messageJson["type"] == "ERROR") {
            messageType = typeMessage::ERROR;
        }
        else if (messageJson["type"] == "INFO") {
            messageType = typeMessage::INFO;
        }
        else if (messageJson["type"] == "WARNING") {
            messageType = typeMessage::WARNING;
        }
        else if (messageJson["type"] == "SUCCESS") {
            messageType = typeMessage::SUCCESS;
        }
        else if (messageJson["type"] == "DEBUG") {
            messageType = typeMessage::DEBUG;
        }
        else if (messageJson["type"] == "SYSTEM") {
            messageType = typeMessage::SYSTEM;
        }
        else {
            messageType = typeMessage::UNKNOWN;
        }
    }
    else {
        messageType = typeMessage::UNKNOWN;
    }


    std::string injectText;

    switch (messageType) {
    case typeMessage::ERROR:
        injectText = "\033[1;31m[ERROR]:   "; // красный цвет
        break;
    case typeMessage::INFO:
        injectText = "\033[1;35m[INFO]:    "; // синий цвет
        break;
    case typeMessage::WARNING:
        injectText = "\033[1;33m[WARNING]: "; // желтый цвет
        break;
    case typeMessage::SUCCESS:
        injectText = "\033[1;32m[SUCCESS]: "; // зеленый цвет
        break;
    case typeMessage::DEBUG:
        injectText = "\033[1;97m[DEBUG]:   "; // светло-белый цвет
        break;
    case typeMessage::SYSTEM:
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

void OutputInformation::loadMessages(const std::string& language) {
    language_ = language;

    try {
        std::ifstream file("Data/language.json");

        if (!file.is_open()) {
            throw std::exception("Json file not found, 'Data/language.json'");
        }

        nlohmann::json messagesJson = nlohmann::json::parse(file);
        messages_ = messagesJson["messages"];
    }
    catch (const std::ifstream::failure& e) {
        std::cerr << "Error opening file: " << e.what() << std::endl;
        throw std::exception("Throw from OutputInformation");
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        throw std::exception("Throw from OutputInformation");
    }
}

void OutputInformation::messageJson(const std::string& key, const std::time_t time, const typeMessage type) noexcept {
    nlohmann::json messageJson;
    nlohmann::json messages = messages_[language_];

    if (messages.find(key) != messages.end()) {
        messageJson = messages[key];
    }
    else {
        messageJson["text"] = key;
    }

    if (time != 0) {
        messageJson["time"] = time;
    }

    messageFromGame(messageJson);
}

void OutputInformation::setLanguage(const std::string& newLanguage) noexcept
{
    language_ = newLanguage;
}

std::string OutputInformation::getTextFromJson(const std::string& key) {
    nlohmann::json messages = messages_[language_];
    if (messages.find(key) != messages.end()) {
        if (messages[key].find("text") != messages[key].end()) {
            return messages[key]["text"];
        }
    }
    return "Unknown message: " + key;
}