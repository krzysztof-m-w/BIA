#ifndef GREEDY_SEARCH_SOLVER_H
#define GREEDY_SEARCH_SOLVER_H

#include "Solver.h"
#include <memory>


class GreedySearchSolver : public Solver {
    private:
        std::unique_ptr<int[]> ininitialSolution;
        int step_counter;
    public:
        GreedySearchSolver();
        ~GreedySearchSolver();
        void solve(int* const solution_ptr) override;
        void set_problem_instance(ProblemInstance* problem_instance) override;
        void reset();
        std::string get_name() const override;
        int get_step_counter() override;
};

#endif