#include <vector>
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
vector<vector<float>> generate_matrix(int n,  float min_matrix, float max_matrix, int seed);


/*!
 * The following function allows the generation of a vector with the following parameters:
 * @param n [int] := dimension of the matrix
 * @param min_vector [float] := minimum value of the matrix
 * @param max_vector [float] := maximum value of the matrix
 * @param seed [int] := seed to generate the random values
 * @return vector [vector<float>] := vector of dimension n with values in the range [min_matrix, max_matrix].
 */
vector<float> generate_vector(int n, float min_vector, float max_vector, int seed);


/*!
 * The following function prints all the elements of the matrix given as input.
 * @param matrix [vector<vector<float>>] := matrix to print
 */
void print_matrix(vector<vector<float>> matrix);


/*!
 * The following function prints all the elements of the vector given as input.
 * @param vector [vector<float>] := vector to print
 */
void print_vector(vector<float> vector);


/*!
 * The following function computes the norm of the difference of two vectors given as input divided by the norm of the
 * first input vector.
 * @param current [vector<float>] := solution vector computed at the current iteration
 * @param previous [vector<float>] := solution vector computed at the previous iteration
 * @return epsilon [double] := the results that comes out computing  ||(current - previous)|| / ||current||.
 */
long double stopping_criteria(vector<float> current, vector<float> previous);


/*!
 * The following function computes the Euclidean distance between two vectors.
 * @param v1 [vector<float>] := first vector for the Euclidean distance
 * @param v2 [vector<float>] := second vector for the Euclidean distance
 * @return euclidean_distance [double] := Euclidean distance of the vectors v1 and v2.
 */
float compute_euclidean_distance(vector<float> v1, vector<float> v2);


/*!
 * The following functions reads a matrix from a file
 * @param n [int] := size of the matrix to read
 * @param filename [string] := filename where the matrix is stored
 * @return matrix [vector<vector<float>>] := matrix read from the file
 */
vector<vector<float>> read_matrix(int n, string filename);


/*!
 * The following functions reads a vector from a file
 * @param n [int] := size of the vector to read
 * @param filename [string] := filename where the vector is stored
 * @return vector [vector<float>] := vector read from the file
 */
vector<float> read_vector(int n, string filename);


/*!
 * The following function writes on a file the performance obtained executing the algorithm in parallel with a certain
 * number of threads
 * @param filename [string] := filename where the data must be saved
 * @param avg_time [long double] := time spent to compute the algorithm in parallel
 * @param num_threads [int] := number of threads used to compute the algorithm
 */
void write_to_file(string filename, long double avg_time, int num_threads);


/*!
 * The following function prints the speedup obtained either with the native threads implementation either
 * with the FastFlow implementation
 * @param seq_time [long] := time spent by the sequential version
 * @param thr_time [long] := time spent by the native threads implementation
 * @param ff_time [long] := time spent by FastFlow implementation
 */
void print_speedup(long seq_time, long thr_time, long ff_time);


/*!
 * the following function prints the scalability obtained either with the native threads implementation either
 * with the FastFlow implementation
 * @param thr1_time [long] := time spent by the native threads implementation with 1 thread
 * @param thr_time [long] := time spent by the native threads implementation with num_threads threads
 * @param ff1_time [long] := time spent by FastFlow implementation with 1 thread
 * @param ff_time [long] := time spent by the FastFlow implementation with num_threads threads
 * @param num_threads [int] := number of threads used to obtain thr_time and ff_time
 */
void print_scalability(long thr1_time, long thr_time, long ff1_time, long ff_time, int num_threads);