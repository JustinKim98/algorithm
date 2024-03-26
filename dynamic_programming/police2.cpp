#include <iostream>
#include <utility>
#include <vector>

int n;
int dp[1001][1001];
int history[1001][1001];
int minDist[1001];
std::vector<std::pair<int, int>> cases;

int getDist(std::pair<int, int> curLoc, std::pair<int, int> nextLoc) {
  auto x0 = std::get<0>(curLoc);
  auto y0 = std::get<1>(curLoc);
  auto x1 = std::get<0>(nextLoc);
  auto y1 = std::get<1>(nextLoc);

  return std::abs(x0 - x1) + std::abs(y0 - y1);
}

int police(int i, int j) {
  if (dp[i][j] > 0)
    return dp[i][j];
  int nextIdx = std::max(i, j) + 1;

  if (nextIdx == cases.size())
    return 0;

  int case0 = police(nextIdx, j) + getDist(cases[i], cases[nextIdx]);
  int case1 = police(i, nextIdx) + getDist(cases[j], cases[nextIdx]);

  dp[i][j] = std::min(case0, case1);
  if (case0 < case1) {
    dp[i][j] = case0;
    history[i][j] = 1;
  } else {
    dp[i][j] = case1;
    history[i][j] = 2;
  }
  return dp[i][j];
}

int main() {
  std::cin >> n;
  int numCases;
  std::cin >> numCases;
  cases = std::vector<std::pair<int, int>>(numCases + 2);
  cases.at(0) = std::make_pair(1, 1);
  cases.at(1) = std::make_pair(n, n);
  for (int i = 2; i < numCases + 2; ++i) {
    int x, y;
    std::cin >> x >> y;
    cases.at(i) = std::make_pair(x, y);
  }

  int minDist = police(0, 1);
  std::cout << minDist << "\n";

  int i = 0, j = 1;
  while (std::max(i, j) < cases.size() - 1) {
    int move = history[i][j];
    std::cout << move << "\n";
    if (move == 1)
      i = std::max(i, j) + 1;
    else
      j = std::max(i, j) + 1;
  }
}