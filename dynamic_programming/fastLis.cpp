#include <algorithm>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

#define INF 1000000001
#define MOD 1000000007

long smallestLastValue[1000001];

/// first idx : length of the lis, second idx : prefix sum
std::vector<std::vector<std::uint64_t>> prefixSumVector(1000001);
/// first idx : length of the lis, second idx : element
std::vector<std::vector<long>> number(1000001);

int arrLength = 0;

void increasingSequence(const std::vector<long> &sequence) {
  for (std::size_t i = 0; i < sequence.size(); ++i) {
    auto largestLength = std::lower_bound(
        smallestLastValue, smallestLastValue + arrLength + 1, sequence[i]);

    *largestLength = sequence[i];

    if (largestLength == smallestLastValue + arrLength + 1) {
      arrLength += 1;
      prefixSumVector[arrLength].push_back(0);
      number[arrLength].push_back(-INF);
    }

    auto currentLength = static_cast<long>(largestLength - smallestLastValue);

    number[currentLength].emplace_back(-sequence[i]);

    /// This calculates lower bound
    auto prevSumPos =
        std::upper_bound(number[currentLength - 1].begin(),
                         number[currentLength - 1].end(), -sequence[i]) -
        number[currentLength - 1].begin();

    auto curBackVal = prefixSumVector[currentLength].back();
    auto backVal = prefixSumVector[currentLength - 1].back();
    auto foundVal = prefixSumVector[currentLength - 1][prevSumPos - 1];

    prefixSumVector[currentLength].emplace_back(
        (backVal - foundVal + curBackVal + MOD) % MOD);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int length;
  std::cin >> length;
  std::vector<long> sequence(length);
  smallestLastValue[0] = -INF;
  prefixSumVector[0] = {0, 1};
  number[0] = {-INF};
  for (int i = 0; i < length; ++i) {
    std::cin >> sequence[i];
  }

  increasingSequence(sequence);
  auto lisCnt = prefixSumVector[arrLength].back();

  std::cout << arrLength << " " << lisCnt << "\n";

  return 0;
}