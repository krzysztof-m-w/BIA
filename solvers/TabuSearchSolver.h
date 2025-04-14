#ifndef TABUSERARCHOVER_H
#define TABUSERARCHOVER_H

#include "SteepestSearchSolver.h"

class TabuSearchSolver : public SteepestSearchSolver {
    private:
        int tabu_tenure;
        int max_no_improvement = 1000;
    public:
        TabuSearchSolver();
        ~TabuSearchSolver();
        std::vector<std::tuple<int, int>> get_candidate_list(int *const currentSolution, int candidateListSize);
        void update_tabu_list(std::vector<std::vector<int>> &tabuList);
        void solve(int *const solution_ptr) override;
};

#endif