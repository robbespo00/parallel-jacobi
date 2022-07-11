#include <iostream>
#include <vector>
#include <fstream>
#include "jacobi_sequential.h"
#include "utility.h"

using namespace std;

#define TRIALS 5
#define MIN_MATRIX 0
#define MAX_MATRIX 20
#define MIN_VECTOR 0
#define MAX_VECTOR 20
#define SEED 14

int main(){

    int size = 5000;
    int iterations = 100;

    vector<vector<float>> matrix = generate_matrix(size, MIN_MATRIX, MAX_MATRIX, SEED);
    vector<float> knownTerm = generate_vector(size, MIN_VECTOR, MAX_VECTOR, SEED);
    long time;
    long double avg_time = 0;

    for(int i = 0; i < TRIALS; i++){
        vector<float> vector = sequential_jacobi(matrix, knownTerm, iterations, -1, time);
        avg_time += time;
    }
    avg_time /= TRIALS;
    cout << "SEQUENTIAL AVG_TIME: " << avg_time << endl;

    return 0;
}