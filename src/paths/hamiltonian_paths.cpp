/**
 * @file hamiltonian_paths.cpp
 * @brief Implementation of Hamiltonian path utilities used in disjointness
 *        and cost analysis for the Price of Diversity study.
 *
 * Each function declared in hamiltonian_paths.h is implemented here.
 * Comments focus on algorithmic details, proof-related context, and edge cases.
 */

#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <hamiltonian_paths.h>

/**
 * Implementation note:
 * The cost of an edge (i, j) in the line is simply |i - j|,
 * where i and j are integer labels in [n].
 * The total path cost is the sum of costs of all edges.
 */
int computeCostPath(const std::vector<int>& path){
    int n = path.size();
    int cost {0};
    for(int i = 0; i < n - 1; i++){
        cost += std::abs(path.at(i) - path.at(i + 1));
    }
    return cost;
}

/**
 * Implementation note:
 * Adds the costs of two paths and compares with the given threshold.
 */
bool arePathsWithinBound(const std::vector<int>& path1, const std::vector<int>& path2, const double bound){
    int costPath1 = computeCostPath(path1);
    int costPath2 = computeCostPath(path2);
    return (costPath1 + costPath2 < bound);
}

/**
 * Implementation note:
 * Tests whether an undirected edge (tail, head) (or (head, tail)) is present in a path.
 * Only internal edges (between consecutive vertices) need to be checked.
 */
bool edgeExistsInPath(int tail, int head, const std::vector<int>& path){
    int n = path.size();
    for (int i = 1; i < n; i++){
        if (((path.at(i - 1) == tail) && (path.at(i) == head)) || ((path.at(i - 1) == head) && (path.at(i) == tail))){
            return true;
        }
    }
    return false;
}

/**
 * Implementation note:
 * Two paths are disjoint if no edge of one path is present in the other.
 * This function iterates over edges of path1 and checks membership in path2.
 */
bool areDisjointPaths(const std::vector<int>& path1, const std::vector<int>& path2){
    assert(path1.size() == path2.size());
    int n = path1.size();

    // Test if any internal edge of path1 is also present in path2
    for (int i = 1; i < n; i++){
        if (edgeExistsInPath(path1.at(i - 1), path1.at(i), path2)) return false; 
    }

    return true;
}

/**
 * Implementation note:
 * Enumerates all Hamiltonian paths of size n, represented as
 * permutations of [n] with endpoints fixed at 1 and n.
 * Uses std::next_permutation to generate candidates.
 * Tests all pairs for disjointness.
 */
bool disjointPathsExist(const int n){
    // Create and populate the identity permutation (1, 2, ..., n)
    std::vector<int> identity(n);
    std::iota(identity.begin(), identity.end(), 1);

    // Create and populate a list of all permutations of [n] with endpoints 1 and n  
    std::vector<std::vector<int>> allPaths;
    do{
        allPaths.push_back(identity);
    } while (std::next_permutation(identity.begin() + 1, identity.end() - 1));

    // Test every pair of paths for disjointness
    int m = allPaths.size();
    for (int i = 0; i < m; i++){
        for (int j = i + 1; j < m; j++){
            if (areDisjointPaths(allPaths.at(i), allPaths.at(j))) return true;
        }
    }

    return false;
}

/**
 * Implementation note:
 * Same as disjointPathsExist, but requires the total cost of the two disjoint
 * paths to be below the given threshold.
 */
bool disjointPathsExistWithinBound(const int n, const double bound){
    // Create and populate the identity permutation (1, 2, ..., n)
    std::vector<int> identity(n);
    std::iota(identity.begin(), identity.end(), 1);

    // Create and populate a list of all permutations of [n] with endpoints 1 and n  
    std::vector<std::vector<int>> allPaths;
    do{
        allPaths.push_back(identity);
    } while (std::next_permutation(identity.begin() + 1, identity.end() - 1));

    // Test every pair of paths for disjointness and for total cost within 16*(n - 1)/5
    int m = allPaths.size();
    for (int i = 0; i < m; i++){
        for (int j = i + 1; j < m; j++){
            std::vector<int> path1 = allPaths.at(i);
            std::vector<int> path2 = allPaths.at(j);

            if (areDisjointPaths(path1, path2) && arePathsWithinBound(path1, path2, bound)) return true;
        }
    }

    return false;
}
