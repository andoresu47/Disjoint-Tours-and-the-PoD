#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <hamiltonian_paths.h>

/**
 * Computes the cost of a Hamiltonian (s, t)-path of length n in the line with uniformly spaced points. 
 * The cost of an edge (i, j) is given by abs(i - j), where i and j are integer labels in [n]. 
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
 * Answers whether the total cost of two paths is strictly less than a given bound. 
 */
bool arePathsWithinBound(const std::vector<int>& path1, const std::vector<int>& path2, const double bound){
    int costPath1 = computeCostPath(path1);
    int costPath2 = computeCostPath(path2);
    return (costPath1 + costPath2 < bound);
}

/**
 * Checks whether an edge, represented by its head and tail vertices, is contained in a path. 
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
 * Checks whether two cycles are disjoint by testing if any edge of the first path is present in the second. 
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
 * Checks whether there exist two disjoint Hamiltonian (s, t)-paths of length n in the line with uniformly spaced points.
 * An (s, t)-path is represented by a permutation of the integers [n] with s = 1 and t = n.  
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
 * Checks whether there exist two disjoint Hamiltonian (s, t)-paths of length n in the line with uniformly spaced points with total cost below a given bound. 
 * An (s, t)-path is represented by a permutation of the integers [n] with s = 1 and t = n.  
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
