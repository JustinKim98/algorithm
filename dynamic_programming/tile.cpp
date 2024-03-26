#include <iostream>

int dp[31];
// 0 : flat
// 1 : top out
// 2 : bottom out
// 3 : top & middle out
// 4 : middle & bottom out

int main() {
  int size;
  std::cin >> size;
  dp[0] = 0;
  for (int i = 0; i <= size; ++i)
    dp[i] = 0;

  dp[2] = 3;
  for (int i = 4; i <= size; i += 2) {
    dp[i] += dp[i - 2] * 3 + 2;
    for (int j = i - 4; j > 0; j -= 2) {
      dp[i] += dp[j] * 2;
    }
  }
  std::cout << dp[size] << "\n";
  return 0;
}
