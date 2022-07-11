#include <vector>
using namespace std;


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
vector<float> sequential_jacobi(vector<vector<float>> matrix, vector<float> knownTerm, int K, double tolerance,
                                long &seq_time);

