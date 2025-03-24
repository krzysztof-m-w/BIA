#include <iostream>
#include <vector>

#include "solvers/HeuristicSolver.h"
#include "solvers/RandomWalkSolver.h"
#include "solvers/RandomSearchSolver.h"
#include "solvers/SteepestSearchSolver.h"
#include "solvers/GreedySearchSolver.h"
#include "evaluation/SolverEvaluator.h"

#include "utils/read_json.h"

std::vector<std::string> problem_names = {"bur26a"};

int main() {
    DataLoader dl = DataLoader("qap/qapdatsol");
    Solver* greedySearchSolver = new GreedySearchSolver();
    Solver* steepestSearchSolver = new SteepestSearchSolver();
    Solver* heuristicSolver = new HeuristicSolver();

    Solver* randomWalkSolver = new RandomWalkSolver();
    Solver* randomSearchSolver = new RandomSearchSolver();

    SolverEvaluator evaluator1 = SolverEvaluator(
        &dl,
        {greedySearchSolver, steepestSearchSolver, heuristicSolver, randomSearchSolver, randomWalkSolver},
        problem_names
    );

    evaluator1.evaluate_solvers();


    return 0;
}

