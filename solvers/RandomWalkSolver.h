#ifndef RANDOMWALKSOLVER_H
#define RANDOMWALKSOLVER_H

#include "Solver.h"

class RandomWalkSolver : public Solver {
    private:
        float max_time;
    public:
        RandomWalkSolver();
        ~RandomWalkSolver(){};
        int* solve();
        void set_max_time(float max_time);
};

#endif