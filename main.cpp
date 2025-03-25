#include <iostream>
#include <vector>

#include "solvers/HeuristicSolver.h"
#include "solvers/RandomWalkSolver.h"
#include "solvers/RandomSearchSolver.h"
#include "solvers/SteepestSearchSolver.h"
#include "solvers/GreedySearchSolver.h"
#include "evaluation/SolverEvaluator.h"

#include "utils/read_json.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <problem_name>" << std::endl;
        return 1;
    }

    std::string problem_name = argv[1];


    DataLoader dl = DataLoader("qap/qapdatsol");
    Solver* greedySearchSolver = new GreedySearchSolver();
    Solver* steepestSearchSolver = new SteepestSearchSolver();
    Solver* heuristicSolver = new HeuristicSolver();

    Solver* randomWalkSolver = new RandomWalkSolver();
    Solver* randomSearchSolver = new RandomSearchSolver();

    SolverEvaluator evaluator1 = SolverEvaluator(
        &dl,
        {greedySearchSolver, steepestSearchSolver, heuristicSolver, randomSearchSolver, randomWalkSolver},
        {problem_name}
    );

    evaluator1.evaluate_solvers();



    return 0;
}

