#include "config.h"

Config::Config(const std::string& filename) : filename(filename) {}

bool Config::loadConfig() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open config file: " << filename << std::endl;
        return false;
    }

    try {
        nlohmann::json j;
        file >> j; 
        configData = j.get<Configs>(); 
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

Configs& Config::getConfig() {
    return configData;
}
