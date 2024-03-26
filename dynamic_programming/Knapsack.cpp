#include <iostream>
#include <vector>

int numItems;
int maxWeight;

int itemWeight[100];
int itemValue[100];
int maxValue[100];
int cache[100000][100];

int knapsack(int weight, int idx) {
  if (weight >= maxWeight)
    return 0;

  if (idx >= numItems)
    return 0;

  if (cache[weight][idx] >= 0)
    return cache[weight][idx];

  int val0 = -1;
  if (weight + itemWeight[idx] <= maxWeight)
    val0 = itemValue[idx] + knapsack(weight + itemWeight[idx], idx + 1);
  int val1 = knapsack(weight, idx + 1);

  int maxVal = std::max(val0, val1);
  cache[weight][idx] = maxVal;
  return maxVal;
}

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  std::cin >> numItems >> maxWeight;

  for (int i = 0; i < numItems; ++i) {
    std::cin >> itemWeight[i] >> itemValue[i];
  }

  for (int i = 0; i < 100000; ++i)
    for (int j = 0; j < 100; ++j)
      cache[i][j] = -1;

  int value = knapsack(0, 0);
  std::cout << value << "\n";
}
