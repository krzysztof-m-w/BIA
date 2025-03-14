#include <string>
#include <vector>
#include "ProblemInstance.h"
#include "random.h"

ProblemInstance::ProblemInstance(/* args */)
{
}

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

    this->neighborhood_2opt = std::vector<std::tuple<int, int>>();
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            this->neighborhood_2opt.push_back(std::make_tuple(i, j));
        }
    }

}

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
}

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

int ProblemInstance::compute_cost_delta(int* solution, int a, int b, int old_cost)
{
    int delta = 0;
    int fa = solution[a]; 
    int fb = solution[b]; 

    for (int i = 0; i < this->n; i++)
    {
        if (i != a && i != b) {
            delta -= this->matrix1[a][i] * this->matrix2[fa][solution[i]];
            delta -= this->matrix1[i][a] * this->matrix2[solution[i]][fa];
            delta -= this->matrix1[b][i] * this->matrix2[fb][solution[i]];
            delta -= this->matrix1[i][b] * this->matrix2[solution[i]][fb];

            delta += this->matrix1[a][i] * this->matrix2[fb][solution[i]];
            delta += this->matrix1[i][a] * this->matrix2[solution[i]][fb];
            delta += this->matrix1[b][i] * this->matrix2[fa][solution[i]];
            delta += this->matrix1[i][b] * this->matrix2[solution[i]][fa];
        }
    }

    // Also account for self-connections
    delta -= this->matrix1[a][b] * this->matrix2[fa][fb];
    delta -= this->matrix1[b][a] * this->matrix2[fb][fa];

    delta += this->matrix1[a][b] * this->matrix2[fb][fa];
    delta += this->matrix1[b][a] * this->matrix2[fa][fb];

    return old_cost + delta;
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