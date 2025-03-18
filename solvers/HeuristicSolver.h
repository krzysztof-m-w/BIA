#ifndef HEURISTICSOLVER_H
#define HEURISTICSOLVER_H

#include "Solver.h"

class HeuristicSolver : public Solver{
    public:
        HeuristicSolver();
        int* solve() override;
        ~HeuristicSolver();
};


#endif