#ifndef TABUSERARCHOVER_H
#define TABUSERARCHOVER_H

#include "SteepestSearchSolver.h"

class TabuSearchSolver : public SteepestSearchSolver {
    protected:
        int max_no_improvement = 2000;
        int tabu_tenure;
    public:
        TabuSearchSolver();
        ~TabuSearchSolver();
        virtual std::vector<std::tuple<int, int>> get_candidate_list(int *const currentSolution, int candidateListSize);
        void update_tabu_list(std::vector<std::vector<int>> &tabuList);
        void solve(int *const solution_ptr) override;
        std::string get_name() const override;
};

#endif