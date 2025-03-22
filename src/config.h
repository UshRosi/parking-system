#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <nlohmann/json.hpp>

// Struct to store configuration data
struct Configs {
    int max_capacity;
    std::string server_ip;
    int server_port;
};

// Define JSON serialization for Configs structure
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Configs, max_capacity, server_ip, server_port)

// Class to handle loading configuration from JSON file
class Config {
public:
    explicit Config(const std::string& filename);

    bool loadConfig();
    Configs& getConfig();

private:
    std::string filename;
    Configs configData;
};

#endif // CONFIG_LOADER_H
