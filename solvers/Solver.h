#ifndef SOLVER_H
#define SOLVER_H

#include "../utils/ProblemInstance.h"
#include "../include/json.hpp"
#include <list>

class Solver {
    protected:
        ProblemInstance* problem_instance;
        int iterations_counter;
        std::list<nlohmann::json> solution_info;
    public:
        virtual void solve(int* const solution_ptr) = 0;
        Solver();
        virtual ~Solver();
        virtual void set_problem_instance(ProblemInstance* problem_instance);
        int get_iterations_counter();
        virtual void reset();
        virtual std::string get_name() const = 0;
        virtual void read_configuration(const std::string& file_path, const std::string& problem_name);
        virtual int get_step_counter();
        virtual void set_solve_info(const int* const solution);
        std::list<nlohmann::json> get_solution_info();
        void add_cost_to_solve_info();
        void add_time_to_solve_info(int start, int end, float avg_time);
};

#endif