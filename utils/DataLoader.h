#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include "ProblemInstance.h"


class DataLoader
{
    private:
        std::string data_dir;
        std::unordered_map<std::string, std::tuple<std::string, std::string>> path_pairs;
        ProblemInstance _load_problem_instance(std::string file_names);
        void load_file_names(const std::string& data_dir);
        
    public:
        DataLoader(/* args */);
        DataLoader(const std::string& data_dir);
        ~DataLoader();

        void load_problem_instance(int n);
        void load_problem_instance(std::string file_name);

        std::unordered_map<std::string, std::tuple<std::string, std::string>> get_path_pairs() { return path_pairs; };
        std::vector<std::string> example_names;
        std::vector<ProblemInstance> problem_instances;

};

#endif