#ifndef STEEPEST_SEARCH_SOLVER_H
#define STEEPEST_SEARCH_SOLVER_H

#include "Solver.h"

class SteepestSearchSolver : public Solver {
    protected:
        int step_counter;
    private:
        int* ininitialSolution;
    public:
        SteepestSearchSolver();
        ~SteepestSearchSolver();
        void solve(int* const solution_ptr) override;
        void set_problem_instance(ProblemInstance* problem_instance) override;
        void reset();
        std::string get_name() const override;
        int get_step_counter() override;
        void set_solve_info(const int* const solution) override;
};
        

#endif