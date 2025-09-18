#include <vector>

bool isOddDepthCycle(const std::vector<int>& cycle);
int computeCostCycle(const std::vector<int>& cycle);
bool areCyclesWithinBound(const std::vector<int>& cycle1, const std::vector<int>& cycle2, const double bound);
bool edgeExistsInCycle(int tail, int head, const std::vector<int>& cycle);
bool areDisjointCycles(const std::vector<int>& cycle1, const std::vector<int>& cycle2);
bool disjointCyclesExist(const int n);
bool disjointCyclesExistWithinBound(const int n, const double bound);
