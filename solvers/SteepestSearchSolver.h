#ifndef STEEPEST_SEARCH_SOLVER_H
#define STEEPEST_SEARCH_SOLVER_H

#include "Solver.h"

class SteepestSearchSolver : public Solver {
    private:
        int* ininitialSolution;
        int step_counter;
    public:
        SteepestSearchSolver();
        ~SteepestSearchSolver();
        void solve(int* const solution_ptr) override;
        void set_problem_instance(ProblemInstance* problem_instance) override;
        void reset();
        std::string get_name() const override;
        int get_step_counter() override;
};
        

#endif