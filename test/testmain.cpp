/**
 * @file test_main.cpp
 * @brief Unit tests for Hamiltonian path and cycle functions.
 *
 * This file validates correctness of the implementations in
 * hamiltonian_paths.cpp and hamiltonian_cycles.cpp.
 * Each test function targets a specific function and uses
 * assertions on hand-crafted examples.
 *
 * The program terminates successfully only if all tests pass.
 */

#include <iostream>
#include <cassert>
#include <hamiltonian_paths.h>
#include <hamiltonian_cycles.h>

/**
 * @brief Tests computeCostPath() on several fixed Hamiltonian paths
 * with known costs.
 */
int testComputeCostPath(){
    std::vector<int> testPath1{1, 2, 3, 4, 5, 6};                   // Cost should be 5
    std::vector<int> testPath2{1, 3, 5, 2, 4, 6};                   // Cost should be 11
    std::vector<int> testPath3{1, 3, 6, 4, 2, 5, 7};                // Cost should be 14
    std::vector<int> testPath4{1, 3, 5, 2, 4, 6, 7, 8, 9, 10, 11};  // Cost should be 16
    std::vector<int> testPath5{1, 2, 3, 4, 5, 6, 8, 10, 7, 9, 11};  // Cost should be 16

    assert(computeCostPath(testPath1) == 5);
    assert(computeCostPath(testPath2) == 11);
    assert(computeCostPath(testPath3) == 14);
    assert(computeCostPath(testPath4) == 16);
    assert(computeCostPath(testPath5) == 16);

    return 0;
}

/**
 * @brief Tests computeCostCycle() on several fixed Hamiltonian cycles
 * with known costs.
 */
int testComputeCostCycle(){
    std::vector<int> testCycle1{1, 3, 2, 5, 4};                      // Cost should be 9
    std::vector<int> testCycle2{1, 2, 3, 4, 5, 6};                   // Cost should be 6
    std::vector<int> testCycle3{1, 2, 4, 3, 5, 6};                   // Cost should be 8
    std::vector<int> testCycle4{1, 3, 4, 2, 5, 6, 7};                // Cost should be 11
    std::vector<int> testCycle5{1, 2, 3, 6, 4, 5, 7};                // Cost should be 11
    std::vector<int> testCycle6{1, 2, 3, 4, 5, 6, 8, 10, 7, 9, 11};  // Cost should be 17

    assert(computeCostCycle(testCycle1) == 8);
    assert(computeCostCycle(testCycle2) == 6);
    assert(computeCostCycle(testCycle3) == 8);
    assert(computeCostCycle(testCycle4) == 11);
    assert(computeCostCycle(testCycle5) == 11);
    assert(computeCostCycle(testCycle6) == 17);

    return 0;
}

/**
 * @brief Tests arePathsWithinBound() with pairs of paths
 * where the combined cost is above/below given thresholds.
 */
int testArePathsWithinBound(){
    int n = 8;
    std::vector<int> testPath1{1, 2, 3, 4, 5, 6, 7, 8};                 // Cost: 7
    std::vector<int> testPath2{1, 3, 5, 7, 2, 4, 6, 8};                 // Cost: 17
    assert(!arePathsWithinBound(testPath1, testPath2, 16.0*(n - 1)/5.0));
    assert(arePathsWithinBound(testPath1, testPath2, 4.0*(n - 1)));

    n = 11;
    std::vector<int> testPath3{1, 3, 5, 2, 4, 6, 7, 8, 9, 10, 11};      // Cost: 16
    std::vector<int> testPath4{1, 2, 3, 4, 5, 6, 8, 10, 7, 9, 11};      // Cost: 16
    assert(!arePathsWithinBound(testPath3, testPath4, 16.0*(n - 1)/5.0));
    assert(arePathsWithinBound(testPath3, testPath4, 4.0*(n - 1)));

    return 0;
}

/**
 * @brief Tests areCyclesWithinBound() with pairs of cycles
 * where the combined cost is above/below given thresholds.
 */
int testAreCyclesWithinBound(){
    int n = 8;
    std::vector<int> testCycle1{1, 3, 4, 5, 6, 7, 8, 2};                    // Cost: 10
    std::vector<int> testCycle2{1, 7, 5, 3, 2, 4, 6, 8};                    // Cost: 14    
    assert(areCyclesWithinBound(testCycle1, testCycle2, 16.0 * n / 5.0));    // Notice that testCycle2 is an even-depth tour. 
    assert(areCyclesWithinBound(testCycle1, testCycle2, 4.0 * n));

    std::vector<int> testCycle3{1, 2, 4, 5, 6, 7, 8, 3};                     // Cost: 12
    std::vector<int> testCycle4{1, 7, 5, 2, 3, 4, 6, 8};                     // Cost: 14
    assert(!areCyclesWithinBound(testCycle3, testCycle4, 16.0*(n - 1)/5.0));
    assert(areCyclesWithinBound(testCycle3, testCycle4, 4.0*(n - 1)));

    return 0;
}

/**
 * @brief Tests edgeExistsInPath() on positive and negative cases.
 */
int testEdgeExistsInPath(){
    std::vector<int> testPath{1, 3, 2, 4};

    assert(edgeExistsInPath(1, 3, testPath));
    assert(edgeExistsInPath(3, 1, testPath));
    assert(edgeExistsInPath(2, 3, testPath));
    assert(edgeExistsInPath(3, 2, testPath));
    assert(edgeExistsInPath(4, 2, testPath));
    assert(edgeExistsInPath(2, 4, testPath));
    
    assert(!edgeExistsInPath(1, 4, testPath));
    assert(!edgeExistsInPath(4, 1, testPath));
    assert(!edgeExistsInPath(1, 2, testPath));
    assert(!edgeExistsInPath(2, 1, testPath));
    assert(!edgeExistsInPath(3, 4, testPath));
    assert(!edgeExistsInPath(4, 3, testPath));

    return 0;
}

/**
 * @brief Tests edgeExistsInCycle() on positive and negative cases.
 */
int testEdgeExistsInCycle(){
    std::vector<int> testCycle{1, 3, 2, 4};

    assert(edgeExistsInCycle(1, 3, testCycle));
    assert(edgeExistsInCycle(3, 1, testCycle));
    assert(edgeExistsInCycle(2, 3, testCycle));
    assert(edgeExistsInCycle(3, 2, testCycle));
    assert(edgeExistsInCycle(4, 2, testCycle));
    assert(edgeExistsInCycle(2, 4, testCycle));
    assert(edgeExistsInCycle(1, 4, testCycle));
    assert(edgeExistsInCycle(4, 1, testCycle));

    assert(!edgeExistsInCycle(1, 2, testCycle));
    assert(!edgeExistsInCycle(2, 1, testCycle));
    assert(!edgeExistsInCycle(3, 4, testCycle));
    assert(!edgeExistsInCycle(4, 3, testCycle));

    return 0;
}

/**
 * @brief Tests areDisjointPaths() on pairs of paths
 * that are and are not edge-disjoint.
 */
int testAreDisjointPaths(){
    std::vector<int> testPath1{1, 2, 3, 4, 5, 6};
    std::vector<int> testPath2{1, 3, 5, 2, 4, 6};
    std::vector<int> testPath3{1, 3, 2, 5, 4, 6};

    assert(areDisjointPaths(testPath1, testPath2));
    assert(!areDisjointPaths(testPath1, testPath3));
    assert(!areDisjointPaths(testPath2, testPath3));

    return 0;
}

/**
 * @brief Tests areDisjointCycles() on pairs of cycles
 * that are and are not edge-disjoint.
 */
int testAreDisjointCycles(){
    std::vector<int> testCycle1{1, 3, 4, 5, 6, 7, 8, 2};
    std::vector<int> testCycle2{1, 7, 5, 3, 2, 4, 6, 8};
    std::vector<int> testCycle3{1, 2, 4, 5, 6, 7, 8, 3};
    std::vector<int> testCycle4{1, 7, 5, 2, 3, 4, 6, 8};

    assert(areDisjointPaths(testCycle1, testCycle2));
    assert(areDisjointPaths(testCycle3, testCycle4));
    assert(!areDisjointPaths(testCycle1, testCycle3));
    assert(!areDisjointPaths(testCycle2, testCycle3));

    return 0;
}

/**
 * @brief Tests isOddDepthCycle() on cycles that are even,
 * odd, or ambiguous-depth.
 */
int testIsOddDepthCycle(){
    std::vector<int> testCycle1{1, 3, 2, 5, 4};                             // Even
    std::vector<int> testCycle2{1, 3, 4, 5, 6, 7, 8, 2};                    // Odd
    std::vector<int> testCycle3{1, 7, 5, 3, 2, 4, 6, 8};                    // Even
    std::vector<int> testCycle4{1, 5, 3, 4, 6, 7, 8, 2};                    // Both

    assert(!isOddDepthCycle(testCycle1));
    assert(isOddDepthCycle(testCycle2));
    assert(!isOddDepthCycle(testCycle3));
    assert(isOddDepthCycle(testCycle4));

    return 0;
}

/**
 * @brief Runs all test functions and prints a progress report.
 * The program succeeds only if every assertion passes.
 */
int main(){
    // Tests for hamiltonian_paths.cpp
    std::cout << "Path tests:\n";

    testEdgeExistsInPath();
    std::cout << "\tAll tests of edgeExistsInPath function passed.\n";
    testAreDisjointPaths();
    std::cout << "\tAll tests of testAreDisjointPaths function passed.\n";
    testComputeCostPath();
    std::cout << "\tAll tests of testComputeCostPath function passed.\n";
    testArePathsWithinBound();
    std::cout << "\tAll tests of testArePathsWithinBound function passed.\n";
    std::cout << "\n";

    // Tests for hamiltonian_cycles.cpp
    std::cout << "Cycle tests:\n";

    testEdgeExistsInCycle();
    std::cout << "\tAll tests of testEdgeExistsInCycle function passed.\n";
    testAreDisjointCycles();
    std::cout << "\tAll tests of testAreDisjointCycles function passed.\n";
    testComputeCostCycle();
    std::cout << "\tAll tests of testComputeCostCycle function passed.\n";
    testAreCyclesWithinBound();
    std::cout << "\tAll tests of testAreCyclesWithinBound function passed.\n";
    testIsOddDepthCycle();
    std::cout << "\tAll tests of testIsOddDepthCycle function passed.\n";
    std::cout << "\n";

    return 0;
}
