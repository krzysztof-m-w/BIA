#ifndef SIMULATEDANNEALINGSOLVER_H
#define SIMULATEDANNEALINGSOLVER_H

#include "GreedySearchSolver.h"

class SimulatedAnnealingSolver : public GreedySearchSolver
{
private:
    float temperature;
    void adjust_initial_temperature(int *best_solution, int best_cost);
    bool accept_solution(int delta, float temperature);
    int cooling_step = 10;
    float cooling_factor = 0.95f;
    int max_no_improvement = 1000;
public:
    SimulatedAnnealingSolver(/* args */);
    ~SimulatedAnnealingSolver();
    void solve(int* const solution_ptr) override;
};
#endif