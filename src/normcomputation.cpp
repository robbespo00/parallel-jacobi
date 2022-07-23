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

    ofstream output_file;
    output_file.open("normcomputation.txt", std::ios::app);
    output_file << avg_time << "\t" << "norm" << endl;

    avg_time = 0;
    for(int i = 0; i < TRIALS; i++){
        vector<float> vector = sequential_jacobi(matrix, knownTerm, iterations, 0, time);
        avg_time += time;
    }
    avg_time /= TRIALS;
    cout << "SEQUENTIAL AVG_TIME: " << avg_time << endl;

    output_file << avg_time << "\t" << "no" << endl;

    output_file.close();
    return 0;
}