#include <vector>
using namespace std;


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
                            double tolerance, long &thr_time);


