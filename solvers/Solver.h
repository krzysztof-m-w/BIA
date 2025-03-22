#ifndef SOLVER_H
#define SOLVER_H

#include "../utils/ProblemInstance.h"

class Solver{
    protected:
        ProblemInstance* problem_instance;
        int iterations_counter;
    public:
        virtual int* solve() = 0;
        Solver();
        virtual ~Solver();
        void set_problem_instance(ProblemInstance* problem_instance);
        float measure_solve_time();
        int get_iterations_counter();       
};

#endif