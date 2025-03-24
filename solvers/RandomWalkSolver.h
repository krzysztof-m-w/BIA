#ifndef RANDOMWALKSOLVER_H
#define RANDOMWALKSOLVER_H

#include "Solver.h"

class RandomWalkSolver : public Solver {
    private:
        float max_time;
    public:
        RandomWalkSolver();
        ~RandomWalkSolver(){};
        void solve(int* const solution_ptr) override;
        void set_max_time(float max_time);
        std::string get_name() const override;
};

#endif