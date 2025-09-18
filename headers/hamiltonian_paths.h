#include <vector>

int computeCostPath(const std::vector<int>& path);
bool arePathsWithinBound(const std::vector<int>& path1, const std::vector<int>& path2, const double bound);
bool edgeExistsInPath(int tail, int head, const std::vector<int>& path);
bool areDisjointPaths(const std::vector<int>& path1, const std::vector<int>& path2);
bool disjointPathsExist(const int n);
bool disjointPathsExistWithinBound(const int n, const double bound);
