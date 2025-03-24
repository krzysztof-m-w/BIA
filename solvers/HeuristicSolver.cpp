#include "HeuristicSolver.h"
#include "../utils/utils.h"
#include <memory>

HeuristicSolver::HeuristicSolver() : Solver() {};
HeuristicSolver::~HeuristicSolver(){};

void HeuristicSolver::solve(int* const solution_ptr){
    std::unique_ptr<int[]> sums1 = std::make_unique<int[]>(problem_instance->n);
    std::unique_ptr<int[]> sums2 = std::make_unique<int[]>(problem_instance->n);

    int** matrix1 = problem_instance->get_matrix1();
    int** matrix2 = problem_instance->get_matrix2();

    std::unique_ptr<int[]> solution = std::make_unique<int[]>(problem_instance->n);

    for(int i = 0; i < problem_instance->n; i++){
        sums1[i] = 0;
        sums2[i] = 0;
    }

    for(int i = 0; i < problem_instance->n; i++){
        for(int j = 0; j < problem_instance->n; j++){
            sums1[i] += matrix1[i][j];
            sums2[i] += matrix2[i][j];
        }
    }

    std::vector<int> indices_order1 = argsort(sums1.get(), problem_instance->n);
    std::vector<int> indices_order2 = argsort(sums2.get(), problem_instance->n);

    for(int i = 0; i < problem_instance->n; i++){
        solution[indices_order1[i]] = indices_order2[this->problem_instance->n - i - 1];
    }
    std::copy(solution.get(), solution.get() + problem_instance->n, solution_ptr);
}
    
    