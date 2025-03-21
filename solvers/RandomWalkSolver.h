#ifndef RANDOMWALKSOLVER_H
#define RANDOMWALKSOLVER_H

#include "Solver.h"

class RandomWalkSolver : public Solver {
    private:
        int iterations_counter;
        float max_time;
    public:
        RandomWalkSolver();
        ~RandomWalkSolver();
        int* solve();
        void set_max_time(float max_time);
        int get_iterations_counter();
};

#endif