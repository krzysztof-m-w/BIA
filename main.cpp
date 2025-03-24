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

    SolverEvaluator evaluator = SolverEvaluator(&dl, {solver}, problem_names);

    evaluator.evaluate_solvers();

    return 0;
}

