
#include <iostream>
#include <limits>
#include <vector>

int dp[501][501]; // idx size, start idx
int sum[501];

int main() {

  int numCases;
  std::cin >> numCases;

  for (int i = 0; i < numCases; ++i) {
    int numPages;
    std::cin >> numPages;
    std::vector<int> pages(numPages);

    for (int i = 0; i < numPages; ++i) {
      std::cin >> pages[i];
    }

    sum[0] = 0;
    for (int i = 1; i <= numPages; ++i) {
      sum[i] = pages[i - 1] + sum[i - 1];
    }

    for (int i = 1; i <= numPages; ++i) {
      for (int j = 1; i + j <= numPages; ++j) {
        dp[j][i + j] = std::numeric_limits<int>::max();
        for (int mid = 0; mid < i; ++mid) {
          dp[j][i + j] =
              std::min(dp[j][i + j], dp[j][j + mid] + dp[j + mid + 1][j + i] +
                                         sum[i + j] - sum[j - 1]);
        }
      }
    }

    std::cout << dp[1][numPages] << std::endl;
  }
}