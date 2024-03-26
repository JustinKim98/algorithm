#include <cmath>
#include <iostream>
#include <vector>

bool square[1000][1000];
int cache[1000][1000];
int n, m;

int largestSquare(int nIdx, int mIdx) {
  if (nIdx >= n || mIdx >= m)
    return 0;

  if (cache[nIdx][mIdx] >= 0)
    return cache[nIdx][mIdx];

  if (!square[nIdx][mIdx])
    return 0;

  int max0 = largestSquare(nIdx, mIdx + 1);
  if (max0 == 0)
    return 1;
  int max1 = largestSquare(nIdx + 1, mIdx + 1);
  if (max1 == 0)
    return 1;
  int max2 = largestSquare(nIdx + 1, mIdx);
  int largest = std::min(std::min(max0, max1), max2) + 1;
  cache[nIdx][mIdx] = largest;
  return largest;
}

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  for (int i = 0; i < 1000; ++i)
    for (int j = 0; j < 1000; ++j)
      cache[i][j] = -1;

  std::cin >> n >> m;
  for (int nIdx = 0; nIdx < n; ++nIdx) {
    char input[1001];
    std::cin >> input;
    for (int mIdx = 0; mIdx < m; ++mIdx)
      square[nIdx][mIdx] = input[mIdx] == '1' ? true : false;
  }

  int maximum = 0;
  for (int nIdx = 0; nIdx < n; ++nIdx) {
    for (int mIdx = 0; mIdx < m; ++mIdx) {
      if (square[nIdx][mIdx]) {
        auto max = largestSquare(nIdx, mIdx);
        if (maximum < max)
          maximum = max;
      }
    }
  }
  std::cout << std::pow(maximum, 2) << "\n";
}