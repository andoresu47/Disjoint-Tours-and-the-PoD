/**
 * @file hamiltonian_cycles.h
 * @brief Declarations for functions on Hamiltonian cycles in the circle with uniformly spaced points.
 * 
 * These functions provide cost calculations, disjointness and depth tests, and existence checks for 
 * Hamiltonian cycles under cost bounds.
 */

#include <vector>

/**
 * @brief Determines whether a Hamiltonian cycle is odd-depth.
 * @param cycle A cycle represented as a permutation of [n] starting with 1.
 * @return true if the cycle is odd-depth, false otherwise.
 */
bool isOddDepthCycle(const std::vector<int>& cycle);

/**
 * @brief Computes the total cost of a Hamiltonian cycle in the circle.
 * @param cycle A cycle represented as a permutation of [n] starting with 1.
 * @return The total cost of the cycle.
 */
int computeCostCycle(const std::vector<int>& cycle);

/**
 * @brief Checks if the combined cost of two Hamiltonian cycles is below a bound.
 * @param cycle1 First Hamiltonian cycle.
 * @param cycle2 Second Hamiltonian cycle.
 * @param bound Cost threshold.
 * @return true if the sum of the cycle costs is strictly less than the bound, false otherwise.
 */
bool areCyclesWithinBound(const std::vector<int>& cycle1, const std::vector<int>& cycle2, const double bound);

/**
 * @brief Tests whether a given (undirected) edge is present in a Hamiltonian cycle.
 * @param tail Tail vertex of the edge.
 * @param head Head vertex of the edge.
 * @param cycle A Hamiltonian cycle.
 * @return true if the edge (tail, head) (or (head, tail)) exists in the cycle, false otherwise.
 */
bool edgeExistsInCycle(int tail, int head, const std::vector<int>& cycle);

/**
 * @brief Checks whether two Hamiltonian cycles are edge-disjoint.
 * @param cycle1 First Hamiltonian cycle.
 * @param cycle2 Second Hamiltonian cycle.
 * @return true if the cycles are disjoint, false otherwise.
 */
bool areDisjointCycles(const std::vector<int>& cycle1, const std::vector<int>& cycle2);

/**
 * @brief Determines if there exist two edge-disjoint Hamiltonian cycles of length n.
 * @param n Number of vertices.
 * @return true if such cycles exist, false otherwise.
 */
bool disjointCyclesExist(const int n);

/**
 * @brief Determines if there exist two odd-depth, edge-disjoint Hamiltonian cycles of length n
 *        whose total cost is below a given bound.
 * @param n Number of vertices.
 * @param bound Cost threshold.
 * @return true if such cycles exist, false otherwise.
 */
bool disjointCyclesExistWithinBound(const int n, const double bound);
