/**
 * @file hamiltonian_paths.h
 * @brief Declarations for functions on Hamiltonian (s, t)-paths in the line with uniformly spaced points.
 *
 * These functions provide cost calculations, disjointness tests, and existence checks for Hamiltonian 
 * (s, t)-paths under cost bounds.
 */

#include <vector>

/**
 * @brief Computes the total cost of a Hamiltonian (s, t)-path.
 * @param path A path represented as a permutation of [n] with endpoints 1 and n.
 * @return The total cost of the path.
 */
int computeCostPath(const std::vector<int>& path);

/**
 * @brief Checks if the combined cost of two paths is below a bound.
 * @param path1 First Hamiltonian path.
 * @param path2 Second Hamiltonian path.
 * @param bound Cost threshold.
 * @return true if the sum of the costs is strictly less than the bound, false otherwise.
 */
bool arePathsWithinBound(const std::vector<int>& path1,
                         const std::vector<int>& path2,
                         const double bound);

/**
 * @brief Tests whether a given (undirected) edge is present in a path.
 * @param tail Tail vertex of the edge.
 * @param head Head vertex of the edge.
 * @param path A Hamiltonian path.
 * @return true if the edge (tail, head) (or (head, tail)) exists in the path, false otherwise.
 */
bool edgeExistsInPath(int tail, int head, const std::vector<int>& path);

/**
 * @brief Checks whether two Hamiltonian paths are edge-disjoint.
 * @param path1 First Hamiltonian path.
 * @param path2 Second Hamiltonian path.
 * @return true if the paths are disjoint, false otherwise.
 */
bool areDisjointPaths(const std::vector<int>& path1,
                      const std::vector<int>& path2);

/**
 * @brief Determines if there exist two edge-disjoint Hamiltonian (s, t)-paths of length n.
 * @param n Number of vertices.
 * @return true if such paths exist, false otherwise.
 */
bool disjointPathsExist(const int n);

/**
 * @brief Determines if there exist two edge-disjoint Hamiltonian (s, t)-paths of length n
 *        whose total cost is below a given bound.
 * @param n Number of vertices.
 * @param bound Cost threshold.
 * @return true if such paths exist, false otherwise.
 */
bool disjointPathsExistWithinBound(const int n, const double bound);
