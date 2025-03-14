#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <iostream>

class ProblemInstance
{
private:
    int** matrix1;
    int** matrix2;
    std::vector<std::tuple<int, int>> neighborhood_2opt;

public:
    int n;
    std::string name;
    int* optimal_solution;
    int optimal_cost;
    ProblemInstance(/* args */);
    ProblemInstance(int n, std::string name, int** matrix1, int** matrix2, int* optimal_solution, int optimal_cost);
    ProblemInstance(const ProblemInstance& other);
    ~ProblemInstance();

    int compute_cost_quadratic(int* solution);
    int compute_cost_delta(int* solution, int i, int j, int old_cost);
    void shuffle_neighborhood_2opt();
    std::vector<std::tuple<int, int>>::iterator get_neighborhood_iterator();
    std::vector<std::tuple<int, int>>::iterator get_neighborhood_end();
};

#endif
