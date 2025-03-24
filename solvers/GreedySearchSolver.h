#ifndef GREEDY_SEARCH_SOLVER_H
#define GREEDY_SEARCH_SOLVER_H

#include "Solver.h"

class GreedySearchSolver : public Solver {
    private:
        int* ininitialSolution;
    public:
        GreedySearchSolver();
        ~GreedySearchSolver();
        void solve(int* const solution_ptr) override;
        void set_problem_instance(ProblemInstance* problem_instance);
        void reset();
        std::string get_name() const override;
};

#endif