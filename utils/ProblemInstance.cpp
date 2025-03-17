#include <string>
#include <vector>
#include "ProblemInstance.h"
#include "random.h"

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

int ProblemInstance::compute_cost_delta(int* solution, int a, int b, int old_cost) {
    int delta = 0;
    int fa = solution[a]; // Facility at position 'a'
    int fb = solution[b]; // Facility at position 'b'

    // Compute the change in cost caused by swapping fa and fb
    for (int i = 0; i < this->n; i++) {
        if (i != a && i != b) {
            int fi = solution[i]; // Facility at position i

            // Contributions before swap
            int before = this->matrix1[a][i] * this->matrix2[fa][fi] +
                         this->matrix1[b][i] * this->matrix2[fb][fi] +
                         this->matrix1[i][a] * this->matrix2[fi][fa] +
                         this->matrix1[i][b] * this->matrix2[fi][fb];

            // Contributions after swap
            int after = this->matrix1[a][i] * this->matrix2[fb][fi] +
                        this->matrix1[b][i] * this->matrix2[fa][fi] +
                        this->matrix1[i][a] * this->matrix2[fi][fb] +
                        this->matrix1[i][b] * this->matrix2[fi][fa];

            delta += (after - before);
        }
    }

    // Self-contribution changes
    delta += (this->matrix1[a][a] * (this->matrix2[fb][fb] - this->matrix2[fa][fa]) +
              this->matrix1[b][b] * (this->matrix2[fa][fa] - this->matrix2[fb][fb]));

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