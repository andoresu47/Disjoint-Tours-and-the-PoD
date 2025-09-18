#include <iostream>
#include <cassert>
#include <hamiltonian_paths.h>
#include <hamiltonian_cycles.h>

int testDisjointPathsExist(){
    assert(!disjointPathsExist(3));
    assert(!disjointPathsExist(4));
    assert(!disjointPathsExist(5));

    assert(disjointPathsExist(6));
    assert(disjointPathsExist(7));
    assert(disjointPathsExist(8));

    return 0;
}

int testDisjointPathsExistWithinBound(){
    assert(!disjointPathsExistWithinBound(6, 16.0 * (6 - 1) / 5.0));
    assert(!disjointPathsExistWithinBound(7, 16.0 * (7 - 1) / 5.0));
    assert(!disjointPathsExistWithinBound(8, 16.0 * (8 - 1) / 5.0));

    assert(disjointPathsExistWithinBound(6, 4.0 * (6 - 1)));
    assert(disjointPathsExistWithinBound(7, 4.0 * (7 - 1)));
    assert(disjointPathsExistWithinBound(8, 4.0 * (8 - 1)));

    return 0;
}

int testDisjointCyclesExist(){
    assert(!disjointCyclesExist(3));
    assert(!disjointCyclesExist(4));

    assert(disjointCyclesExist(5));
    assert(disjointCyclesExist(6));
    assert(disjointCyclesExist(7));
    assert(disjointCyclesExist(8));

    return 0;
}

int testDisjointCyclesExistWithinBound(){
    assert(!disjointCyclesExistWithinBound(5, 16.0 * 5 / 5.0));
    assert(!disjointCyclesExistWithinBound(6, 16.0 * 6 / 5.0));
    assert(!disjointCyclesExistWithinBound(7, 16.0 * 7 / 5.0));
    assert(!disjointCyclesExistWithinBound(8, 16.0 * 8 / 5.0));

    // assert(disjointCyclesExistWithinBound(5, 4.0 * 5));  // There are no odd-depth disjoint tours for n = 5
    assert(disjointCyclesExistWithinBound(6, 4.0 * 6));
    assert(disjointCyclesExistWithinBound(7, 4.0 * 7));
    assert(disjointCyclesExistWithinBound(8, 4.0 * 8));

    return 0;
}

// The program should end successfully only of all tests are passed, implying that the claims are proved. 
int main() {
    // Proof of Claim 3.1
    std::cout << "Proof of Claim 3.1:\n";
    testDisjointPathsExist();
    std::cout << "\t(i) There is no pair of edge-disjoint Hamiltonian paths when n <= 5.\n";
    testDisjointPathsExistWithinBound();
    std::cout << "\t(ii) There is no pair of edge-disjoint Hamiltonian paths with total cost less than 16(n - 1)/5 when n in {6, 7, 8}.\n";
    std::cout << "\n";

    // Proof of Claim 4.1
    std::cout << "Proof of Claim 4.1:\n";
    testDisjointCyclesExist();
    std::cout << "\t(i) There is no pair of edge-disjoint Hamiltonian cycles when n <= 4.\n";
    testDisjointCyclesExistWithinBound();
    std::cout << "\t(ii) There is no pair of (odd-depth) edge-disjoint Hamiltonian cycles with total cost less than 16*n/5 when n in {5, 6, 7, 8}.\n";
    std::cout << "\n";

    return 0;
}
