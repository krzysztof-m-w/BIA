#ifndef VANILLATABUSEARCHSOLVER_H
#define VANILLATABUSEARCHSOLVER_H

#include "TabuSearchSolver.h"

class VanillaTabuSearchSolver : public TabuSearchSolver 
{
private:
    /* data */
public:
    VanillaTabuSearchSolver(/* args */);
    ~VanillaTabuSearchSolver();
    std::vector<std::tuple<int, int>> get_candidate_list(int *const currentSolution, int candidateListSize) override;
    std::string get_name() const override;
};



#endif