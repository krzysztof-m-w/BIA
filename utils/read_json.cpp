#include "read_json.h"
#include <fstream>
#include <iostream>

nlohmann::json read_json(const std::string& file_path, const std::vector<std::string>& expected_keys) {
    std::cout << "Reading file: " + file_path << std::endl;
    nlohmann::json json;
    try {
        std::ifstream config_file(file_path);
        if (!config_file.is_open()) {
            throw std::runtime_error("Could not open configuration file.");
        }

        config_file >> json;
        for (const auto& key : expected_keys) {
            if (!json.contains(key)) {
                throw std::runtime_error("Configuration file does not contain a '" + key + "' field.");
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error reading configuration: " << e.what() << std::endl;
    }
    return json;
}
