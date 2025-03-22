#ifndef RANDOM_SEARCH_SOLVER_H
#define RANDOM_SEARCH_SOLjsonER_H

#include "Solver.h"

class RandomSearchSolver : public Solver {
    private:
        float max_time;
    public:
        RandomSearchSolver();
        ~RandomSearchSolver() {};
        int* solve();
        void set_max_time(float max_time);
};

#endif