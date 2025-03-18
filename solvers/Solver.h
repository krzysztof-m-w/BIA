#ifndef SOLVER_H
#define SOLVER_H

#include "../utils/ProblemInstance.h"

class Solver{
    private:
       ProblemInstance* problem_instance;
    public:
        Solver();
        virtual int* solve() = 0;
        virtual ~Solver();
        void set_problem_instance(ProblemInstance* problem_instance);
        float measure_solve_time();       
};

#endif