#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include "ProblemInstance.h"
#include "DataLoader.h"

void DataLoader::load_file_names(const std::string& data_dir)
{
    std::vector<std::string> file_list;

    for (const auto& entry : std::filesystem::directory_iterator("data/" + data_dir))
    {
        if (entry.is_regular_file())
        {
            
            std::string path = entry.path().string();
            std::string stem = entry.path().stem().string();
            std::string extension = entry.path().extension().string();

            if (extension == ".dat" || extension == ".sln")
            {
                auto it = std::find_if(file_list.begin(), file_list.end(), [&stem](const std::string& file) {
                    return std::filesystem::path(file).stem().string() == stem;
                });
                
                if (it != file_list.end())
                {
                    if(extension == ".dat")
                        path_pairs[stem] = std::make_tuple(path, *it);
                    else
                        path_pairs[stem] = std::make_tuple(*it, path);
                }
            }
            
            file_list.push_back(entry.path().string());
            this->example_names.push_back(stem);
        }
    }
};

ProblemInstance DataLoader::_load_problem_instance(std::string file_name)
{
    std::string file_path1 = std::get<0>(path_pairs[file_name]);
    std::string file_path2 = std::get<1>(path_pairs[file_name]);
    
    // load the first file
    std::ifstream file1(file_path1);
    int n;
    file1 >> n;
    int** matrix1 = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix1[i] = new int[n];
    }
    int** matrix2 = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix2[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file1 >> matrix1[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file1 >> matrix2[i][j];
        }
    }
    file1.close();

    // load the second file
    std::ifstream file2(file_path2);
    int n2;
    int optimal_cost;
    int* optimal_solution = new int[n];
    file2 >> n2;
    if(n != n2) {
        std::cerr << "Error: n != n2" << std::endl;
        exit(1);
    }
    file2 >> optimal_cost;
    for (int i = 0; i < n; ++i) {
        file2 >> optimal_solution[i];
    }

    // if the optimal solution is 1-indexed, convert it to 0-indexed
    if(*std::max_element(optimal_solution, optimal_solution + n) == n){
        for (int i = 0; i < n; ++i) {
            optimal_solution[i]--;
        }
    }
    file2.close();
    return ProblemInstance(n, file_name, matrix1, matrix2, optimal_solution, optimal_cost);
}

void DataLoader::load_problem_instance(int n)
{
    auto example = example_names[n];
    this->problem_instances.push_back(_load_problem_instance(example));

}

void DataLoader::load_problem_instance(std::string file_name)
{
    problem_instances.push_back(_load_problem_instance(file_name));
}
    

DataLoader::DataLoader()
{
}

DataLoader::DataLoader(const std::string& data_dir)
{
    this->data_dir = data_dir;
    this->path_pairs = std::unordered_map<std::string, std::tuple<std::string, std::string>>();
    this->problem_instances = std::vector<ProblemInstance>();
    this->example_names = std::vector<std::string>();

    load_file_names(data_dir);
}

DataLoader::~DataLoader()
{
}
