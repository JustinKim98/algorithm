#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

std::unordered_map<int, int> cache;

int minimumEffort(const std::vector<int> &codes, int idx0, int idx1) {

  if (std::max(idx0, idx1) + 1 >= static_cast<int>(codes.size()))
    return 0;

  int key = idx0 * 10000 + idx1;
  if (cache.find(key) != cache.end())
    return cache[key];

  int idxToSing = std::max(idx0, idx1) + 1;
  int min0 = minimumEffort(codes, idx0, idxToSing) +
             (idx1 < 0 ? 0 : std::abs(codes[idxToSing] - codes[idx1]));
  int min1 = minimumEffort(codes, idxToSing, idx1) +
             (idx0 < 0 ? 0 : std::abs(codes[idxToSing] - codes[idx0]));

  int minEffort = std::min(min0, min1);
  cache[key] = minEffort;
  return minEffort;
}

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  int numCodes;
  std::cin >> numCodes;
  std::vector<int> codes(numCodes);

  for (int i = 0; i < numCodes; ++i)
    std::cin >> codes[i];

  std::cout << minimumEffort(codes, -1, -1) << "\n";
  return 0;
}

// int main() {
//   int numCodes;
//   std::cin >> numCodes;
//   std::vector<int> codes(numCodes);

//   for (int i = 0; i < numCodes; ++i)
//     std::cin >> codes[i];

//   std::sort(codes.begin(), codes.end());

//   unsigned largestDiff = 0;
//   unsigned diffSum = 0;
//   for (int i = 0; i < numCodes - 1; ++i) {
//     auto diff = static_cast<unsigned>(std::abs(codes[i + 1] - codes[i]));
//     if (diff > largestDiff)
//       largestDiff = diff;

//     diffSum += diff;
//   }

//   std::cout << (diffSum - largestDiff) << "\n";

//   return 0;
// }