#include <string>
#include <vector>
#include "ProblemInstance.h"
#include "random.h"
#include <tuple>

ProblemInstance::ProblemInstance(/* args */)
{
}

// Constructor for ProblemInstance
ProblemInstance::ProblemInstance(int n, std::string name, int** matrix1, int** matrix2, int* optimal_solution, int optimal_cost)
{
    this->n = n;
    this->name = std::move(name);
    this->optimal_cost = optimal_cost;

    this->matrix1 = new int*[n];
    for (int i = 0; i < n; ++i) {
        this->matrix1[i] = new int[n];
        std::copy(matrix1[i], matrix1[i] + n, this->matrix1[i]);
    }

    this->matrix2 = new int*[n];
    for (int i = 0; i < n; ++i) {
        this->matrix2[i] = new int[n];
        std::copy(matrix2[i], matrix2[i] + n, this->matrix2[i]);
    }

    this->optimal_solution = new int[n];
    std::copy(optimal_solution, optimal_solution + n, this->optimal_solution);

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            this->neighborhood_2opt.push_back(std::make_tuple(i, j));
        }
    }

}

// Copy constructor for ProblemInstance
ProblemInstance::ProblemInstance(const ProblemInstance& other){
    this->n = other.n;
    this->name = other.name;
    this->optimal_cost = other.optimal_cost;

    this->matrix1 = new int*[n];
    for (int i = 0; i < n; ++i) {
        this->matrix1[i] = new int[n];
        std::copy(other.matrix1[i], other.matrix1[i] + n, this->matrix1[i]);
    }

    this->matrix2 = new int*[n];
    for (int i = 0; i < n; ++i) {
        this->matrix2[i] = new int[n];
        std::copy(other.matrix2[i], other.matrix2[i] + n, this->matrix2[i]);
    }

    this->optimal_solution = new int[n];
    std::copy(other.optimal_solution, other.optimal_solution + n, this->optimal_solution);

    neighborhood_2opt = other.neighborhood_2opt;
}

// Destructor for ProblemInstance
ProblemInstance::~ProblemInstance()
{
    for (int i = 0; i < n; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
    }
    delete[] matrix1;
    delete[] matrix2;
    delete[] optimal_solution;
}

int ProblemInstance::compute_cost_quadratic(int* solution)
{
    int cost = 0;
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            cost += this->matrix1[i][j] * this->matrix2[solution[i]][solution[j]];
        }
    }
    return cost;
}

int ProblemInstance::compute_cost_delta(int* permutation, int i, int j, int old_cost) {    
    int delta = 0;
    int pi_i = permutation[i];
    int pi_j = permutation[j];

    int** matrixA = this->matrix1;
    int** matrixB = this->matrix2;
    
    for (int k = 0; k < this->n; ++k) {
        if (k != i && k != j) {
            delta += (matrixA[i][k] * (matrixB[pi_j][permutation[k]] - matrixB[pi_i][permutation[k]])) +
                     (matrixA[j][k] * (matrixB[pi_i][permutation[k]] - matrixB[pi_j][permutation[k]])) +
                     (matrixA[k][i] * (matrixB[permutation[k]][pi_j] - matrixB[permutation[k]][pi_i])) +
                     (matrixA[k][j] * (matrixB[permutation[k]][pi_i] - matrixB[permutation[k]][pi_j]));
        }
    }
    delta += (matrixA[i][j] * (matrixB[pi_j][pi_i] - matrixB[pi_i][pi_j])) +
             (matrixA[j][i] * (matrixB[pi_i][pi_j] - matrixB[pi_j][pi_i]));    
    return delta;
}


void ProblemInstance::shuffle_neighborhood_2opt()
{
    shuffle(this->neighborhood_2opt);
}

std::vector<std::tuple<int, int>>::iterator ProblemInstance::get_neighborhood_iterator()
{
    return this->neighborhood_2opt.begin();
}

std::vector<std::tuple<int, int>>::iterator ProblemInstance::get_neighborhood_end()
{
    return this->neighborhood_2opt.end();
}

int** ProblemInstance::get_matrix1()
{
    return this->matrix1;
}

int** ProblemInstance::get_matrix2()
{
    return this->matrix2;
}