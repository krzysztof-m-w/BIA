#ifndef RANDOM_SEARCH_SOLVER_H
#define RANDOM_SEARCH_SOLjsonER_H

#include "Solver.h"

class RandomSearchSolver : public Solver {
    private:
        float max_time;
        bool global_configuration;
    public:
        RandomSearchSolver();
        ~RandomSearchSolver() {};
        void solve(int* const solution_ptr) override;
        void set_max_time(float max_time);
        std::string get_name() const override;
        void read_configuration(const std::string& file_path, const std::string& problem_name) override;
};

#endif