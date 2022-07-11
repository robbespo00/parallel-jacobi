#include <vector>
using namespace std;

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
vector<float> fast_flow_jacobi(vector<vector<float>> matrix, vector<float> knownTerm, int K, int num_threads,
                             double tolerance, long &ff_time);
