#include "config.h"
#include <fstream>
#include <iostream>

Config::Config(const std::string& filename) : filename(filename) {} //TODO:  da capire questa 

bool Config::loadConfig() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open config file: " << filename << std::endl;
        return false;
    }

    try {
        nlohmann::json j;
        file >> j; // Read JSON from file
        configData = j.get<Configs>(); // Convert JSON to struct
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
