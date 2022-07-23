#include <vector>
#include <ff/ff.hpp>
#include <ff/parallel_for.hpp>
#include "utimer.cpp"
#include "utility.h"
#include "jacobi_ff.h"


/*!
 * The following function is called from fast_flow_jacobi and it is called only if the tolerance input in
 * fast_flow_jacobi is disabled (smaller than 0). Even if it is redundant I adopted this choice in order to avoid
 * at each step the comparison
 * @param matrix [vector<vector<float>>] := matrix A of the linear system (Ax=b)
 * @param knownTerm [vector<float>] := vector b of the linear system (Ax=b)
 * @param K [int] := maximum number of iterations of the Jacobi's Algorithm allowed
 * @param num_threads [int] := number of threads used to parallelize
 * @param ff_time [long] := value passed by reference in which it will be stored the computation time of the FastFlow
 * implementation
 * @return solution [vector<float>] := solution vector that best approximates the linear system Ax=b.
 */
vector<float> ff_jacobi(vector<vector<float>> matrix, const vector<float> knownTerm, int K, int num_threads,
                        long &ff_time){

    int n = knownTerm.size();
    vector<float> curr_variables(n, 0.0);
    vector<float> prev_variables(n, 0.0);
    ff::ParallelFor pf(num_threads);
    int chunk = n/num_threads;

    string timer = "FASTFLOW " + to_string(num_threads) + " threads ";
    {
        utimer ff = utimer(timer, &ff_time);
        for (int k = 0; k < K; k++) {
            pf.parallel_for(0, n, 1, chunk, [&](ulong i){
                float sum = 0;
                for(int j = 0; j < n; j++){
                    if(i != j){
                        sum += matrix[i][j] * prev_variables[j];
                    }
                }
                curr_variables[i] = (knownTerm[i] - sum) / matrix[i][i];
            }, num_threads);
            {
                utimer copy = utimer("Copy time");
                prev_variables = curr_variables;
            }
        }
    }
    return curr_variables;
}

/*!
 * The following function compute the Jacobi's Algorithm using the FastFlow implementation which uses the ParallelFor
 * class in order to parallelize in the best way the code. The inputs are:
 * @param matrix [vector<vector<float>>] := matrix A of the linear system (Ax=b)
 * @param knownTerm [vector<float>] := vector b of the linear system (Ax=b)
 * @param K [int] := maximum number of iterations of the Jacobi's Algorithm allowed
 * @param num_threads [int] := number of threads used to parallelize
 * @param tolerance [double] := tolerance used to stop earlier the algorithm and it uses the following
 * stopping criteria ||(current - previous)|| / ||current||
 * @param ff_time [long] := value passed by reference in which it will be stored the computation time of the FastFlow
 * implementation
 * @return solution [vector<float>] := solution vector that best approximates the linear system Ax=b.
 */
vector<float> fast_flow_jacobi(vector<vector<float>> matrix, const vector<float> knownTerm, int K, int num_threads,
                             double tolerance, long &ff_time){

    if(tolerance < 0){ // it avoids to check the if statement when the tolerance is not used
        return ff_jacobi(matrix, knownTerm, K, num_threads, ff_time);
    }


    int n = knownTerm.size();
    vector<float> curr_variables(n, 0.0);
    vector<float> prev_variables(n, 0.0);
    ff::ParallelFor pf(num_threads);
    long double similarity;
    int chunk = n / num_threads;

    string timer = "FASTFLOW " + to_string(num_threads) + " threads ";
    {
        utimer seq = utimer(timer, &ff_time);
        for (int k = 0; k < K; k++) {
            pf.parallel_for(0, n, 1, chunk, [&](ulong i){
                float sum = 0;
                for(int j = 0; j < n; j++){
                    if(i != j){
                        sum += matrix[i][j] * prev_variables[j];
                    }
                }
                curr_variables[i] = (knownTerm[i] - sum) / matrix[i][i];
            }, num_threads);
            similarity = stopping_criteria(curr_variables, prev_variables);
            if (similarity <= tolerance){
                cout << k <<")FastFlow Jacobi interrupted because " << similarity << " (similarity) <= " <<
                tolerance << " (tolerance)" << endl;
                break;
            }
            prev_variables = curr_variables;
        }
    }
    return curr_variables;
}
