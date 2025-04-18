#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <iostream>
#include <vector>
#include <tuple>

class ProblemInstance
{
private:
    int** matrix1;
    int** matrix2;
    int neighborhood_2opt_size;
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
    int** get_matrix1();
    int** get_matrix2();
    void get_random_solution(int* solution_ptr);
    int get_neighborhood_2opt_size();
    void apply_move_2opt(int* solution, int i, int j);
};

#endif
