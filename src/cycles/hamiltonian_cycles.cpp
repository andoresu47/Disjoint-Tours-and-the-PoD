/**
 * @file hamiltonian_cycles.cpp
 * @brief Implementation of Hamiltonian cycle utilities used in disjointness
 *        and cost analysis for the Price of Diversity study.
 *
 * Each function declared in hamiltonian_cycles.h is implemented here.
 * Comments focus on algorithmic details, proof-related context, and edge cases.
 */

#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <hamiltonian_cycles.h>


/**
 * Implementation note:
 * A Hamiltonian cycle in the circle with uniformly spaced points has all segments
 * of either even or odd depth. To classify a cycle, it suffices to test the depth
 * of the first segment (1, 2). The "depth" is computed as:
 *
 *   (# times vertex 1 is covered) + (# times vertex 2 is covered)
 *   + 1 if the edge (1, 2) itself appears.
 *
 * Some cycles can be realized with equal cost as either even- or odd-depth
 * depending on orientation of edges of length ceil(n/2). By convention, these are
 * treated as odd-depth cycles.
 */
bool isOddDepthCycle(const std::vector<int>& cycle){
    int n = cycle.size();
    assert(cycle.at(0) == 1);

    int depth{0};
    int diff{0};
    for(int i = 0; i < n - 1; i++){
        diff = std::abs(cycle.at(i) - cycle.at(i + 1));
        if (diff > n - diff) {
            if(i > 0) depth++;                                  // 1 is covered when the edge cycles back, and ends at a point >= 2. Note that 2 may also be covered. 
        }
        else{
            if(i == 0) depth++;                                 // 2 is covered by an edge containing 1 if it does not cycle back. 
        }                                                       // This also includes the case when (1, 2) is an edge in the cycle (but not the last one). 
    }

    int lastDiff = std::abs(cycle.at(n - 1) - 1);
    if (lastDiff < n - lastDiff) depth++;                       // 2 is covered by an edge containing 1 if it does not cycle back. Includes the case when (1, 2) is an edge. 

    return depth % 2;       // Evaluates to true if depth is odd. 
}

/**
 * Implementation note:
 * The cost of an edge (i, j) is defined as:
 *     min(|i - j|, n - |i - j|)
 * where n is the cycle length.
 * The cycle cost is the sum over all edges, including the closing edge
 * from the last vertex back to 1.
 */
int computeCostCycle(const std::vector<int>& cycle){
    assert(cycle.at(0) == 1);

    int n = cycle.size();
    int cost{0};
    int diff{0};
    // Aggregate cost of internal edges. 
    for(int i = 0; i < n - 1; i++){
        diff = std::abs(cycle.at(i) - cycle.at(i + 1));
        cost += std::min(diff, n - diff);
    }
    // Add cost of edge connecting first (1) and last (cycle[n - 1]) elements. 
    int lastDiff = std::abs(cycle.at(n - 1) - 1);

    return cost + std::min(lastDiff, n - lastDiff);
}

/**
 * Implementation note:
 * This function simply adds the costs of two cycles (computed via computeCostCycle)
 * and compares against the given threshold.
 */
bool areCyclesWithinBound(const std::vector<int>& cycle1, const std::vector<int>& cycle2, const double bound){
    int costCycle1 = computeCostCycle(cycle1);
    int costCycle2 = computeCostCycle(cycle2);
    return (costCycle1 + costCycle2 < bound);
}

/**
 * Implementation note:
 * Tests whether an undirected edge (tail, head) (or (head, tail)) appears in the given cycle.
 * Handles both the closing edge (1, cycle[n-1]) and internal edges.
 */
bool edgeExistsInCycle(int tail, int head, const std::vector<int>& cycle){
    int n = cycle.size();
    assert(cycle.at(0) == 1);

    if (((tail == 1) && (cycle.at(n - 1) == head)) || ((head == 1) && (cycle.at(n - 1) == tail))) return true;                  // Test edge (1, cycle[n - 1]).
    for (int i = 1; i < n; i++){
        if (((cycle.at(i - 1) == tail) && (cycle.at(i) == head)) || ((cycle.at(i - 1) == head) && (cycle.at(i) == tail))){      // Test internal vertices. 
            return true;
        }
    }
    return false;
}

/**
 * Implementation note:
 * Two cycles are disjoint if no edge of one cycle appears in the other.
 * This function iterates over edges of cycle1 and checks membership in cycle2.
 */
bool areDisjointCycles(const std::vector<int>& cycle1, const std::vector<int>& cycle2){
    assert(cycle1.size() == cycle2.size());
    assert(cycle1.at(0) == 1);
    assert(cycle2.at(0) == 1);

    int n = cycle1.size();

    if (edgeExistsInCycle(1, cycle1.at(n - 1), cycle2)) return false;                   // Test if edge (1, cycle1[n - 1]) is present in cycle2. 
    for (int i = 1; i < n; i++){                                                        // Test if any other (internal) edge of cycle1 is also present in cycle2. 
        if (edgeExistsInCycle(cycle1.at(i - 1), cycle1.at(i), cycle2)) return false; 
    }

    return true;
}

/**
 * Implementation note:
 * Enumerates all unique Hamiltonian cycles of size n, represented as
 * permutations of [n] beginning with 1 (canonical form).
 * Uses std::next_permutation to generate candidates, skipping symmetric reversals.
 * Tests all pairs for disjointness.
 */
bool disjointCyclesExist(const int n){
    // Create and populate the identity permutation (1, 2, ..., n)
    std::vector<int> identity(n);
    std::iota(identity.begin(), identity.end(), 1);

    // Create and populate a list of all (unique) cyclic permutations of [n] of the form (1, ...).
    // This is all that is needed since any other permutation can be rewritten with 1 as its first element.    
    std::vector<std::vector<int>> allCycles;
    do{
        // Since "next_permutation" generates permutations in lexicographical order, 
        // if the last element of the current permutation is smaller than its second element, 
        // then the reverse permutation has already been generated and the current one can be 
        // skipped over. 
        if(identity.at(n - 1) > identity.at(1)) allCycles.push_back(identity);     // Only insert unique cyclic permutations. 
    } while (std::next_permutation(identity.begin(), identity.end()) && identity.at(0) == 1);

    // Test every pair of cycles for disjointness
    int m = allCycles.size();
    for (int i = 0; i < m; i++){
        for (int j = i + 1; j < m; j++){
            std::vector<int> cycle1 = allCycles.at(i);
            std::vector<int> cycle2 = allCycles.at(j);

            if (areDisjointCycles(cycle1, cycle2)) return true;
        }
    }

    return false;
}

/**
 * Implementation note:
 * Same as disjointCyclesExist, but requires both cycles to be odd-depth
 * and the total cost to be below the given threshold.
 */
bool disjointCyclesExistWithinBound(const int n, const double bound){
    // Create and populate the identity permutation (1, 2, ..., n)
    std::vector<int> identity(n);
    std::iota(identity.begin(), identity.end(), 1);

    // Create and populate a list of all (unique) cyclic permutations of [n] of the form (1, ...).
    // This is all that is needed since any other permutation can be rewritten with 1 as its first element.    
    std::vector<std::vector<int>> allCycles;
    do{
        // Since "next_permutation" generates permutations in lexicographical order, 
        // if the last element of the current permutation is smaller than its second element, 
        // then the reverse permutation has already been generated and the current one can be 
        // skipped over. 
        if(identity.at(n - 1) > identity.at(1)) allCycles.push_back(identity);     // Only insert unique cyclic permutations. 
    } while (std::next_permutation(identity.begin(), identity.end()) && identity.at(0) == 1);

    // Test every pair of cycles for disjointness
    int m = allCycles.size();
    for (int i = 0; i < m; i++){
        for (int j = i + 1; j < m; j++){
            std::vector<int> cycle1 = allCycles.at(i);
            std::vector<int> cycle2 = allCycles.at(j);

            if ((isOddDepthCycle(cycle1) && isOddDepthCycle(cycle2))
                && areDisjointCycles(cycle1, cycle2) 
                && areCyclesWithinBound(cycle1, cycle2, bound)){
                    return true;
                }
        }
    }

    return false;
}
