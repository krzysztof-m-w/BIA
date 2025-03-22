#include <iostream>
#include <vector>
#include "utils/random.h"
#include "utils/time_measure.h"
#include "utils/DataLoader.h"
#include "solvers/HeuristicSolver.h"
#include "solvers/RandomWalkSolver.h"
#include "solvers/RandomSearchSolver.h"
#include "solvers/SteepestSearchSolver.h"
#include "solvers/GreedySearchSolver.h"
#include "evaluation/SolverEvaluator.h"

std::vector<std::string> problem_names = {"bur26a"};

int main() {
    DataLoader dl = DataLoader("qap/qapdatsol");
    Solver* solver = new GreedySearchSolver();

    for(auto problem_name : problem_names){
        dl.load_problem_instance(problem_name);
    }

    for(auto& pi : dl.problem_instances){
        solver->set_problem_instance(&pi);
        int* solution = solver->solve();
        std::cout << pi.name << " " << pi.compute_cost_quadratic(solution) << std::endl;
    }

    return 0;
}

