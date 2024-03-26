#include <deque>
#include <iostream>
#include <unordered_map>
#include <vector>

int n, numCases;
std::unordered_map<unsigned long, std::pair<std::deque<int>, int>> cache;

std::pair<std::deque<int>, int>
shortestPath(const std::vector<std::pair<int, int>> &cases,
             std::pair<int, int> car0, std::pair<int, int> car1, int caseIdx) {

  if (caseIdx >= numCases)
    return std::make_pair(std::deque<int>(), 0);

  auto [iIdx, jIdx] = cases[caseIdx];
  auto [iIdxCar0, jIdxCar0] = car0;
  auto [iIdxCar1, jIdxCar1] = car1;

  unsigned long cacheIdx =
      static_cast<unsigned long>(iIdxCar0) * 1000 * 1000 * 1000 +
      static_cast<unsigned long>(jIdxCar1) * 1000 * 1000 + iIdxCar0 * 1000 +
      jIdxCar0;
  cacheIdx = cacheIdx * 1000 + caseIdx;

  if (cache.find(cacheIdx) != cache.end())
    return cache[cacheIdx];

  int distFromCar0 = std::abs(iIdx - iIdxCar0) + std::abs(jIdx - jIdxCar0);
  int distFromCar1 = std::abs(iIdx - iIdxCar1) + std::abs(jIdx - jIdxCar1);

  auto [path0, min0] =
      shortestPath(cases, std::make_pair(iIdx, jIdx), car1, caseIdx + 1);
  auto [path1, min1] =
      shortestPath(cases, car0, std::make_pair(iIdx, jIdx), caseIdx + 1);

  auto distWithCar0 = min0 + distFromCar0;
  auto distWithCar1 = min1 + distFromCar1;

  if (distWithCar0 < distWithCar1) {
    path0.push_front(1);
    cache[cacheIdx] = std::make_pair(path0, distWithCar0);
    return std::make_pair(path0, distWithCar0);
  }

  path1.push_front(2);
  cache[cacheIdx] = std::make_pair(path1, distWithCar1);
  return std::make_pair(path1, distWithCar1);
}

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  std::cin >> n >> numCases;
  std::vector<std::pair<int, int>> cases(numCases);

  for (int i = 0; i < numCases; ++i) {
    int x0, x1;
    std::cin >> x0 >> x1;
    cases[i] = std::make_pair(x0 - 1, x1 - 1);
  }

  auto [path, minDist] = shortestPath(cases, std::make_pair(0, 0),
                                      std::make_pair(n - 1, n - 1), 0);
  std::cout << minDist << "\n";
  for (auto num : path)
    std::cout << num << "\n";
  return 0;
}