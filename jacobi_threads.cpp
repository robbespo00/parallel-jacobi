#include "jacobi_threads.h"
#include <vector>
#include <thread>
#include <barrier>
#include "utility.h"
#include "utimer.cpp"
#include <iostream>
using namespace std;


/*!
 * The following function is called from threads_jacobi and it is called only if the tolerance input in
 * threads_jacobi is disabled (smaller than 0). Even if it is redundant I adopted this choice in order to avoid
 * at each step the comparison
 * @param matrix [vector<vector<float>>] := matrix A of the linear system (Ax=b)
 * @param knownTerm [vector<float>] := vector b of the linear system (Ax=b)
 * @param K [int] := maximum number of iterations of the Jacobi's Algorithm allowed
 * @param num_threads [int] := number of threads used to parallelize
 * @param ff_time [long] := value passed by reference in which it will be stored the computation time of the native
 * threads implementation
 * @return solution [vector<float>] := solution vector that best approximates the linear system Ax=b.
 */
vector<float> thr_jacobi(vector<vector<float>> matrix, vector<float> knownTerm, int K, int num_threads, long &thr_time){

    int n = knownTerm.size();
    vector<float> curr_variables(n, 0.0);
    vector<float> prev_variables(n, 0.0);
    vector<thread> threads(num_threads);
    int chunk = n / num_threads;
    int iterations = K;

    auto on_completion = [&]() noexcept { // function called by the barrier each time the threads synchronize
        iterations--;
        prev_variables = curr_variables;
    };

    std::barrier ba(num_threads, on_completion);

    auto body = [&](int tid) { // function executed by a single thread

        int start = tid * chunk;
        int end = (tid != num_threads - 1 ? start + chunk : n) - 1;
        while (iterations > 0) {
            for (int i = start; i <= end; i++) {
                float sum = 0;
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        sum += matrix[i][j] * prev_variables[j];
                    }
                }
                curr_variables[i] = (knownTerm[i] - sum) / matrix[i][i];
            }
            ba.arrive_and_wait();
        }
    };

    string timer = "PARALLEL " + to_string(num_threads) + " threads ";
    {
        utimer thr = utimer(timer, &thr_time);
        for (int i = 0; i < num_threads; i++) {
            threads[i] = thread(body, i);
        }
        for (int i = 0; i < num_threads; i++) {
            threads[i].join();
        }
    }
    return curr_variables;
}


/*!
 * The following function computes the parallel version of the Jacobi's Algorithm using the native threads
 * implementation.
 * @param matrix [vector<vector<float>>] := matrix A of the linear system (Ax=b)
 * @param knownTerm [vector<float>] := vector b of the linear system (Ax=b)
 * @param K [int] := maximum number of iterations of the Jacobi's Algorithm allowed
 * @param num_threads [int] := number of threads used to parallelize
 * @param tolerance [double] := tolerance used to stop earlier the algorithm and it uses the following
 * stopping criteria ||(current - previous)|| / ||current||
 * @param thr_time [long] := value passed by reference in which it will be stored the computation time of the native
 * threads implementation
 * @return solution [vector<float>] := solution vector that best approximates the linear system Ax=b.
 */
vector<float> threads_jacobi(vector<vector<float>> matrix, vector<float> knownTerm, int K, int num_threads,
                            double tolerance, long &thr_time){

    if (tolerance < 0){ // it avoids to check the if statement when the tolerance is not used
        return thr_jacobi(matrix, knownTerm, K, num_threads, thr_time);
    }

    int n = knownTerm.size();
    vector<float> curr_variables(n, 0.0);
    vector<float> prev_variables(n, 0.0);
    vector<thread> threads(num_threads);
    int chunk = n / num_threads;
    int iterations = K;
    long double similarity;

    auto on_completion = [&]() noexcept { // function called by the barrier each time the threads synchronize
        iterations--;
        similarity = stopping_criteria(curr_variables, prev_variables);
        if (similarity <= tolerance) {
            cout << (K-iterations-1) <<")Parallel Jacobi interrupted because " << similarity << " (similarity) <= " <<
                 tolerance << " (tolerance)" << endl;
            iterations = 0;
        }
        prev_variables = curr_variables;
    };

    std::barrier ba(num_threads, on_completion);

    auto body = [&](int tid) { // function executed by a single thread

        int start = tid * chunk;
        int end = (tid != num_threads - 1 ? start + chunk : n) - 1;
        while (iterations > 0) {
            for (int i = start; i <= end; i++) {
                float sum = 0;
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        sum += matrix[i][j] * prev_variables[j];
                    }
                }
                curr_variables[i] = (knownTerm[i] - sum) / matrix[i][i];
            }
            ba.arrive_and_wait();
        }
    };

    string timer = "PARALLEL " + to_string(num_threads) + " threads ";
    {
        utimer seq = utimer(timer, &thr_time);
        for (int i = 0; i < num_threads; i++) {
            threads[i] = thread(body, i);
        }
        for (int i = 0; i < num_threads; i++) {
            threads[i].join();
        }
    }

    return curr_variables;
}
