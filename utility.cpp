#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <numeric>
#include <fstream>
#include "utility.h"
using namespace std;


/*!
 * The following function allows the generation of a diagonal dominant matrix with the following parameters:
 * @param n [int] := dimension of the matrix
 * @param min_matrix [float] := minimum value of the matrix
 * @param max_matrix [float] := maximum value of the matrix
 * @param seed [int] := seed to generate the random values
 * @return matrix [vector<vector<float>>]:= matrix of dimension n with values in the range [min_matrix, max_matrix]
 * except for the elements on the diagonal which are higher than the maximum value because they are computed as the
 * sum of the elements of  the corresponding row multiplied by 2.
 */
vector<vector<float>> generate_matrix(int n, float min_matrix, float max_matrix, int seed){

    int columns = n;
    int rows = n;
    float sum;
    vector<vector<float>> matrix(rows, vector<float>(columns));

    // srand((unsigned int)time(NULL)); it can be substituted with the seed in order to have each time different numbers
    srand(seed);

    for(int i=0; i < n; i++){
        sum=0;
        for(int j=0; j < n; j++){
            matrix[i][j] = min_matrix + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max_matrix-min_matrix)));
            sum += matrix[i][j];
        }
        matrix[i][i] = sum * 2; // it allows to have a diagonal dominant matrix
    }
    return matrix;
}


/*!
 * The following function allows the generation of a vector with the following parameters:
 * @param n [int] := dimension of the matrix
 * @param min_vector [float] := minimum value of the matrix
 * @param max_vector [float] := maximum value of the matrix
 * @param seed [int] := seed to generate the random values
 * @return vector [vector<float>] := vector of dimension n with values in the range [min_matrix, max_matrix].
 */
vector<float> generate_vector(int n, float min_vector, float max_vector, int seed){

    vector<float> vector(n);

    // srand((unsigned int)time(NULL)); it can be substituted with the seed in order to have each time different numbers
    srand(seed);
    for(int i=0; i < n; i++){
        vector[i] = min_vector + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max_vector-min_vector)));
    }
    return vector;
}


/*!
 * The following function prints all the elements of the matrix given as input.
 * @param matrix [vector<vector<float>>] := matrix to print
 */
void print_matrix(vector<vector<float>> matrix){

    int n = matrix.size();

    cout << "Printing the matrix: " << endl;
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "END" << endl;
}


/*!
 * The following function prints all the elements of the vector given as input.
 * @param vector [vector<float>] := vector to print
 */
void print_vector(vector<float> vector){

    int n = vector.size();

    cout << "Printing the vector: " << endl;
    for(int i = 0; i < n; i++){
        cout << vector[i] << endl;
    }
    cout << "END" << endl;
}


/*!
 * The following function computes the norm of the difference of two vectors given as input divided by the norm of the
 * first input vector.
 * @param current [vector<float>] := solution vector computed at the current iteration
 * @param previous [vector<float>] := solution vector computed at the previous iteration
 * @return epsilon [double] := the results that comes out computing  ||(current - previous)|| / ||current||.
 */
long double stopping_criteria(vector<float> current, vector<float> previous){

    int n = current.size();
    long double denominator = sqrt(inner_product(current.begin(), current.end(), current.begin(), 0.0L));

    for(int i = 0; i < n; i++){
        current[i] -= previous[i];
    }
    long double numerator = sqrt(inner_product(current.begin(), current.end(), current.begin(), 0.0L));

    return  numerator/denominator;
}


/*!
 * The following function computes the Euclidean distance between two vectors.
 * @param v1 [vector<float>] := first vector for the Euclidean distance
 * @param v2 [vector<float>] := second vector for the Euclidean distance
 * @return euclidean_distance [double] := Euclidean distance of the vectors v1 and v2.
 */
float compute_euclidean_distance(vector<float> current, vector<float> previous){

    float distance = 0;
    int n = current.size();

    if(n == 0 || n != previous.size()){
        throw std::invalid_argument("The size of the vector is 0 or the size of the two vectors is different");
    }

    for(int i = 0; i < n; i++){
        distance += pow(current[i] - previous[i], 2);
    }

    return sqrt(distance);
}


/*!
 * The following functions reads a matrix from a file
 * @param n [int] := size of the matrix to read
 * @param filename [string] := filename where the matrix is stored
 * @return matrix [vector<vector<float>>] := matrix read from the file
 */
vector<vector<float>> read_matrix(int n, string filename){

    vector<vector<float>> matrix(n, vector<float>(n));
    float number;

    ifstream input_file;
    input_file.open(filename, std::ios::in);

    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return matrix;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            input_file >> matrix[i][j];
        }
    }
    cout << endl;
    input_file.close();

    return matrix;
}


/*!
 * The following functions reads a vector from a file
 * @param n [int] := size of the vector to read
 * @param filename [string] := filename where the vector is stored
 * @return vector [vector<float>] := vector read from the file
 */
vector<float> read_vector(int n, string filename){

    vector<float> vector(n);
    float number;

    ifstream input_file;
    input_file.open(filename, std::ios::in);

    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        exit(1);
    }

    for(int i = 0; i < n; i++){
        input_file >> vector[i];
    }
    cout << endl;
    input_file.close();

    return vector;
}


/*!
 * The following function writes on a file the performance obtained executing the algorithm in parallel with a certain
 * number of threads
 * @param filename [string] := filename where the data must be saved
 * @param avg_time [long double] := time spent to compute the algorithm in parallel
 * @param num_threads [int] := number of threads used to compute the algorithm
 */
void write_to_file(string filename, long double avg_time, int num_threads){

    ofstream output_file;

    output_file.open(filename, std::ios::app);
    if(!output_file.is_open()){
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        exit(0);
    }
    output_file << num_threads << "\t" << avg_time << endl;
    output_file.close();
}


/*!
 * The following function prints the speedup obtained either with the native threads implementation either
 * with the FastFlow implementation
 * @param seq_time [long] := time spent by the sequential version
 * @param thr_time [long] := time spent by the native threads implementation
 * @param ff_time [long] := time spent by FastFlow implementation
 */
void print_speedup(long seq_time, long thr_time, long ff_time){

    float speedup_thr = (float) seq_time / (float) thr_time;
    float speedup_ff = (float) seq_time / (float) ff_time;

    cout << "SPEEDUP (SEQUENTIAL / THREADS) = " << speedup_thr << endl;
    cout << "SPEEDUP (SEQUENTIAL / FASTFLOW) = " << speedup_ff << endl;

}


/*!
 * the following function prints the scalability obtained either with the native threads implementation either
 * with the FastFlow implementation
 * @param thr1_time [long] := time spent by the native threads implementation with 1 thread
 * @param thr_time [long] := time spent by the native threads implementation with num_threads threads
 * @param ff1_time [long] := time spent by FastFlow implementation with 1 thread
 * @param ff_time [long] := time spent by the FastFlow implementation with num_threads threads
 * @param num_threads [int] := number of threads used to obtain thr_time and ff_time
 */
void print_scalability(long thr1_time, long thr_time, long ff1_time, long ff_time, int num_threads){

    float scalability_thr = (float) thr1_time / (float) thr_time;
    float scalability_ff = (float) ff1_time / (float) ff_time;

    cout << "SCALABILITY (1 THREAD / " << num_threads << " THREADS) = " << scalability_thr << endl;
    cout << "SCALABILITY (1 THREAD_FF / " << num_threads << " THREADS_FF) = " << scalability_ff << endl;
}