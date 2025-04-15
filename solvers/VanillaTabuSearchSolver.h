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
    void solve(int *const solution_ptr);
    std::string get_name() const override;
};



#endif