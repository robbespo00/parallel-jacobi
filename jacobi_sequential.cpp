#include <iostream>
#include <vector>
#include <tuple>
#include "utimer.cpp"
#include "utility.h"
#include "jacobi_sequential.h"
using namespace std;


/*!
 * The following function is called from sequential_jacobi and it is called only if the tolerance input in
 * sequential_jacobi is disabled (smaller than 0). Even if it is redundant I adopted this choice in order to avoid
 * at each step the comparison
 * @param matrix [vector<vector<float>>] := matrix A of the linear system (Ax=b)
 * @param knownTerm [vector<float>] := vector b of the linear system (Ax=b)
 * @param K [int] := maximum number of iterations of the Jacobi's Algorithm allowed
 * @param ff_time [long] := value passed by reference in which it will be stored the computation time of the sequential
 * implementation
 * @return solution [vector<float>] := solution vector that best approximates the linear system Ax=b.
 */
vector<float> seq_jacobi(vector<vector<float>> matrix, vector<float> knownTerm, int K, long &seq_time){

    int n = knownTerm.size();

    if(K <= 0){
        K = n;
        cout << "K set to n because it was <= 0" << endl;
    }

    vector<float> curr_variables(n, 0.0);
    vector<float> prev_variables(n, 0.0);
    float sum;

    {
        utimer seq = utimer("Sequential Jacobi", &seq_time);
        for(int k=0; k < K; k++) {
            for (int i = 0; i < n; i++) {
                sum = 0;
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        sum += matrix[i][j] * prev_variables[j];
                    }
                }
                curr_variables[i] = (knownTerm[i] - sum) / matrix[i][i];
            }
            prev_variables = curr_variables;
        }
    }

    return curr_variables;
}


/*!
 * The following function computes the sequential version of the Jacobi's Algorithm.
 * @param matrix [vector<vector<float>>] := matrix A of the linear system (Ax=b)
 * @param knownTerm [vector<float>] := vector b of the linear system (Ax=b)
 * @param K [int] := maximum number of iterations of the Jacobi's Algorithm
 * @param tolerance [double] := tolerance used to stop earlier the algorithm and it uses the following
 * stopping criteria ||(current - previous)|| / ||current||
 * @param seq_time [long] := value passed by reference in which it will be stored the computation time of the sequential
 * implementation
 * @return solution [vector<float>] := solution vector that best approximates the linear system Ax=b.
 */
vector<float> sequential_jacobi(vector<vector<float>> matrix, vector<float> knownTerm, int K,
                               double tolerance, long &seq_time){

    if (tolerance < 0){ // it avoids to check the if statement when the tolerance is not used
        return seq_jacobi(matrix, knownTerm, K, seq_time);
    }

    int n = knownTerm.size();

    if(K <= 0){
        K = n;
        cout << "K set to n because it was <= 0" << endl;
    }

    vector<float> curr_variables(n, 0.0);
    vector<float> prev_variables(n, 0.0);
    float sum;
    long double similarity;

    {
        utimer seq = utimer("Sequential Jacobi", &seq_time);
        for(int k=0; k < K; k++) {
            for (int i = 0; i < n; i++) {
                sum = 0;
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        sum += matrix[i][j] * prev_variables[j];
                    }
                }
                curr_variables[i] = (knownTerm[i] - sum) / matrix[i][i];
            }
            similarity = stopping_criteria(curr_variables, prev_variables);
            if (similarity <= tolerance) {
                cout << k <<")Sequential Jacobi interrupted because " << similarity << " (similarity) <= " <<
                     tolerance << " (tolerance)" << endl;
                break;
            }
            prev_variables = curr_variables;
        }
    }

    return curr_variables;
}


