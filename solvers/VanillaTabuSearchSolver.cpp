#include "VanillaTabuSearchSolver.h"
#include "../utils/utils.h"

VanillaTabuSearchSolver::VanillaTabuSearchSolver()
{
}

VanillaTabuSearchSolver::~VanillaTabuSearchSolver()
{
}

std::vector<std::tuple<int, int>> VanillaTabuSearchSolver::get_candidate_list(int *const currentSolution, int candidateListSize)
{
    return std::vector<std::tuple<int, int>>(this->problem_instance->get_neighborhood_iterator(), this->problem_instance->get_neighborhood_end());
}

std::string VanillaTabuSearchSolver::get_name() const
{
    return "VanillaTabuSearchSolver";
}
