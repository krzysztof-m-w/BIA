#ifndef HEURISTICSOLVER_H
#define HEURISTICSOLVER_H

#include "Solver.h"

class HeuristicSolver : public Solver{
    public:
        HeuristicSolver();
        void solve(int* const solution_ptr) override;
        ~HeuristicSolver();
        std::string get_name() const override;
};


#endif