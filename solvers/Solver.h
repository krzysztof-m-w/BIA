#ifndef SOLVER_H
#define SOLVER_H

#include "../utils/ProblemInstance.h"

class Solver {
    protected:
        ProblemInstance* problem_instance;
        int iterations_counter;
    public:
        virtual void solve(int* const solution_ptr) = 0;
        Solver();
        virtual ~Solver();
        virtual void set_problem_instance(ProblemInstance* problem_instance);
        int get_iterations_counter();
        virtual void reset();
        virtual std::string get_name() const = 0;
        virtual void read_configuration(const std::string& file_path, const std::string& problem_name);
};

#endif