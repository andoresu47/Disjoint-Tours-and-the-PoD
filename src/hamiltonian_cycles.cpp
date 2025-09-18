#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <hamiltonian_cycles.h>


/**
 * Answers whether the given cycle is odd-depth, meaning that all its segments have exclusively odd depth. 
 * Since the segments of a Hamiltonian cycle in the circle with uniformly spaced points have exclusively even or odd depth, 
 * we only test the depth of the first segment (1, 2). 
 * 
 * The depth of the first segment is equal to: #times 1 is covered + #times 2 is covered + 1 (if edge (1, 2) exists)
 * 
 * Note: There are some cases when a cycle can be odd-depth or even-depth (with the same cost) depending on whether we draw 
 * an edge of length ~n/2 in clockwise or anti-clockwise direction. This function treats those cases as odd-depth cycles.
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
    if (lastDiff < n - lastDiff) depth++;                           // 2 is covered by an edge containing 1 if it does not cycle back. Includes the case when (1, 2) is an edge. 

    return depth % 2;       // Evaluates to true if depth is odd. 
}

/**
 * Computes the cost of a Hamiltonian cycle of length n in the circle with uniformly spaced points. 
 * The cost of an edge (i, j) is given by min(abs(i - j), n - abs(i - j)) where i and j are integer labels in [n]. 
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
 * Answers whether the total cost of two cycles is strictly less than a given bound. 
 */
bool areCyclesWithinBound(const std::vector<int>& cycle1, const std::vector<int>& cycle2, const double bound){
    int costCycle1 = computeCostCycle(cycle1);
    int costCycle2 = computeCostCycle(cycle2);
    return (costCycle1 + costCycle2 < bound);
}

/**
 * Checks whether an edge, represented by its head and tail vertices, is contained in a cycle. 
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
 * Checks whether two cycles (in canonical form) are disjoint by testing if any edge of the first cycle is present in the second. 
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
 * Checks whether there exist two disjoint Hamiltonian cycles of length n in the circle with uniformly spaced points.
 * A cycle is represented by a permutation of the integers [n] of the form (1, ...).   
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
 * Checks whether there exist two odd-depth disjoint Hamiltonian cycles of length n in the circle with uniformly spaced points with total cost below a given bound.
 * A cycle is represented by a permutation of the integers [n] of the form (1, ...).   
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
