#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "utility.h"
#include "jacobi_sequential.h"
#include "jacobi_threads.h"
#include "jacobi_ff.h"
using namespace std;


#define TRIALS 5 // number of trials to do such that then it is performed the average of the computation times.
#define MIN_MATRIX 0 // minimum value of the matrix
#define MAX_MATRIX 20 // maximum value of the matrix
#define MIN_VECTOR 0 // minimum value of the vector
#define MAX_VECTOR 20 // maximum value of the vector
#define SEED 14 // seed to generate random numbers


int main(int argc, char *argv[]) {

    // Check on the input values
    if(argc < 6){
        cerr << "The parameters must be 6 or 7" << endl;
        cerr << "Parameters: [MODE] [SIZE] [ITERATIONS] [TOLERANCE] [OUTPUT_FILENAME] [NUM_THREADS]" << endl;
        exit(-1);
    }
    string mode = argv[1];

    if(mode != "seq" && mode != "thr" && mode != "ff"){
        cerr << "The MODE parameter is wrong. It must be one of the following: - seq \n - thr \n - ff " << endl;
        exit(-2);
    }
    if(argc == 7 && mode == "seq"){
        cerr << "You passed too many arguments for sequential mode!" << endl;
        cerr << "Parameters: [MODE] [SIZE] [ITERATIONS] [TOLERANCE] [OUTPUT_FILENAME] [NUM_THREADS]" << endl;
        exit(-3);
    }
    if(argc == 6 && mode == "thr"){
        cerr << "You passed few arguments for threads mode!" << endl;
        cerr << "Parameters: [MODE] [SIZE] [ITERATIONS] [TOLERANCE] [OUTPUT_FILENAME] [NUM_THREADS]" << endl;
        exit(-4);
    }


    int size = atoi(argv[2]);
    if(size < 1){
        cerr << "The size of the linear system must be >= 1!" << endl;
        exit(-5);
    }
    int iterations = atoi(argv[3]);
    if(iterations < 1){
        cerr << "The number of iterations must be >= 1!" << endl;
        exit(-6);
    }
    double tolerance = atof(argv[4]);
    string output_filename = argv[5];
    int num_threads;




    cout << "\t \t ---JACOBI METHOD--- \t \t" << endl;
    cout << "MODE: " << mode << endl;
    cout << "SIZE: " << size << endl;
    cout << "ITERATIONS: " << iterations << endl;
    if(tolerance < 0){
        cout << "TOLERANCE: DISABLED" << endl;
    }
    else{
        cout << "TOLERANCE: " << tolerance << endl;
    }
    if(mode != "seq"){
        num_threads = atoi(argv[6]);
        if(num_threads < 1){
            cerr << "The number of threads must be >= 1!" << endl;
            exit(-7);
        }
        cout << "NUMBER OF THREADS: " << num_threads << endl;
    }
    cout << endl;


    vector<vector<float>> matrix = generate_matrix(size, MIN_MATRIX, MAX_MATRIX, SEED);
    vector<float> knownTerm = generate_vector(size, MIN_VECTOR, MAX_VECTOR, SEED);
    long time;
    long double avg_time = 0;


    if(mode == "seq"){
        for(int i = 0; i < TRIALS; i++){
            vector<float> var = sequential_jacobi(matrix, knownTerm, iterations, tolerance, time);
            avg_time += time;
        }
        avg_time /= TRIALS;
        cout << "SEQUENTIAL AVG_TIME: " << avg_time << " with " << TRIALS << " trials" << endl;
    }
    else if(mode == "thr"){
        for(int i = 0; i < TRIALS; i++){
            vector<float> var = threads_jacobi(matrix, knownTerm, iterations, num_threads, tolerance, time);
            avg_time += time;
        }
        avg_time /= TRIALS;
        cout << "THREADS AVG_TIME: " << avg_time << " with " << TRIALS << " trials" << endl;
    }
    else if(mode == "ff"){
        for(int i = 0; i < TRIALS; i++){
            vector<float> var = fast_flow_jacobi(matrix, knownTerm, iterations, num_threads, tolerance, time);
            avg_time += time;
        }
        avg_time /= TRIALS;
        cout << "FAST FLOW AVG_TIME: " << avg_time << " with " << TRIALS << " trials" << endl;
    }


    ofstream output_file;
    string filename = output_filename + to_string(size) + mode + ".csv";
    output_file.open(filename, std::ios::app);
    if(!output_file.is_open()){
        cerr << "Could not open the file '" << filename << "'" << endl;
        exit(-8);
    }
    if(mode != "seq"){
        output_file << num_threads << "\t" << avg_time << endl;
    }
    else{
        output_file << avg_time << endl;
    }

    output_file.close();

    return 0;
}
