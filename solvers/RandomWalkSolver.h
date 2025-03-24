#ifndef RANDOMWALKSOLVER_H
#define RANDOMWALKSOLVER_H

#include "Solver.h"

class RandomWalkSolver : public Solver {
    private:
        float max_time;
        bool global_configuration;
    public:
        RandomWalkSolver();
        ~RandomWalkSolver(){};
        void solve(int* const solution_ptr) override;
        void set_max_time(float max_time);
        std::string get_name() const override;
        void read_configuration(const std::string& file_path, const std::string& problem_name) override;
};

#endif