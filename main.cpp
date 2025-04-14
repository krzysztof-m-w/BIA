#include <iostream>
#include <vector>

#include "solvers/HeuristicSolver.h"
#include "solvers/RandomWalkSolver.h"
#include "solvers/RandomSearchSolver.h"
#include "solvers/SteepestSearchSolver.h"
#include "solvers/GreedySearchSolver.h"
#include "solvers/SimulatedAnnealingSolver.h"
#include "solvers/TabuSearchSolver.h"
#include "evaluation/SolverEvaluator.h"

#include "utils/read_json.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <problem_name> <solver_names>" << std::endl;
        return 1;
    }

    std::string problem_name = argv[1];
    std::vector<std::string> solver_names;
    for(int i = 2; i < argc; ++i) {
        solver_names.push_back(argv[i]);
    }

    DataLoader dl = DataLoader("qap/qapdatsol");
    std::vector<Solver*> solvers;

    if(std::find(solver_names.begin(), solver_names.end(), "GreedySearchSolver") != solver_names.end()) {
        solvers.push_back(new GreedySearchSolver());
    }
    if(std::find(solver_names.begin(), solver_names.end(), "SteepestSearchSolver") != solver_names.end()) {
        solvers.push_back(new SteepestSearchSolver());
    }
    if(std::find(solver_names.begin(), solver_names.end(), "HeuristicSolver") != solver_names.end()) {
        solvers.push_back(new HeuristicSolver());
    }
    if(std::find(solver_names.begin(), solver_names.end(), "RandomSearchSolver") != solver_names.end()) {
        solvers.push_back(new RandomSearchSolver());
    }
    if(std::find(solver_names.begin(), solver_names.end(), "RandomWalkSolver") != solver_names.end()) {
        solvers.push_back(new RandomWalkSolver());
    }
    if(std::find(solver_names.begin(), solver_names.end(), "SimulatedAnnealingSolver") != solver_names.end()) {
        solvers.push_back(new SimulatedAnnealingSolver());
    }
    if(std::find(solver_names.begin(), solver_names.end(), "TabuSearchSolver") != solver_names.end()) {
        solvers.push_back(new TabuSearchSolver());
    }

    SolverEvaluator evaluator1 = SolverEvaluator(
        &dl,
        solvers,
        {problem_name}
    );

    evaluator1.evaluate_solvers();



    return 0;
}

