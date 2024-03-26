#include <deque>
#include <iostream>
#include <vector>
int numBuildings;
int buildings[501];
int cache[501];
int degree[501];
std::vector<std::vector<int>> dependences;

void bfs() {
  std::deque<int> queue;
  for (int i = 1; i <= numBuildings; ++i) {
    if (degree[i] == 0) {
      cache[i] = buildings[i];
      queue.emplace_back(i);
    }
  }

  while (!queue.empty()) {
    auto curBuilding = queue.front();
    queue.pop_front();

    for (auto nextBuilding : dependences[curBuilding]) {
      auto nextCost = cache[curBuilding] + buildings[nextBuilding];
      if (cache[nextBuilding] < nextCost)
        cache[nextBuilding] = nextCost;

      if (--degree[nextBuilding] == 0)
        queue.emplace_back(nextBuilding);
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  std::cin >> numBuildings;
  dependences = std::vector<std::vector<int>>(numBuildings + 1);
  for (int i = 1; i <= numBuildings; ++i) {
    dependences[i].reserve(500);
  }

  for (int i = 1; i <= numBuildings; ++i) {
    degree[i] = 0;
    cache[i] = 0;
    int cost;
    std::cin >> cost;
    buildings[i] = cost;
    int lastIdx;
    std::cin >> lastIdx;
    while (lastIdx >= 0) {
      degree[i] += 1;
      dependences[lastIdx].emplace_back(i);
      std::cin >> lastIdx;
    }
  }

  bfs();

  for (int i = 1; i <= numBuildings; ++i)
    std::cout << cache[i] << "\n";

  return 0;
}