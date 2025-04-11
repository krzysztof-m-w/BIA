#include "../utils/DataLoader.h"
#include "../solvers/SimulatedAnnealingSolver.h"


int main(){
    DataLoader dl = DataLoader("qap/qapdatsol");
    dl.load_problem_instance("bur26a");

    SimulatedAnnealingSolver* solver = new SimulatedAnnealingSolver();
    solver->set_problem_instance(&dl.problem_instances[0]);

    solver->read_configuration("", "bur26a");

    int* solution = new int[dl.problem_instances[0].n];
    dl.problem_instances[0].get_random_solution(solution);

    solver->solve(solution);

    std::cout << dl.problem_instances[0].compute_cost_quadratic(solution) << std::endl;

    return 0;
}