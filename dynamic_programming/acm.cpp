#include <deque>
#include <iostream>
#include <vector>

int buildings[1001];
int cache[1001];
int degree[1001];
std::vector<std::vector<int>> dependences;
int numBuildings, numDependences;

void bfs() {
  std::deque<int> queue;

  for (int i = 1; i <= numBuildings; ++i) {
    if (degree[i] == 0) {
      queue.emplace_back(i);
      cache[i] = buildings[i];
    }
  }

  while (!queue.empty()) {
    auto curBuilding = queue.front();
    queue.pop_front();
    for (int nextBuilding : dependences[curBuilding]) {
      if (cache[nextBuilding] < cache[curBuilding] + buildings[nextBuilding]) {
        cache[nextBuilding] = cache[curBuilding] + buildings[nextBuilding];
      }

      if (--degree[nextBuilding] == 0)
        queue.emplace_back(nextBuilding);
    }
  }
}

int main() {
  int numTestCases;
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  std::cin >> numTestCases;

  for (int i = 0; i < numTestCases; ++i) {
    std::cin >> numBuildings >> numDependences;
    dependences =
        std::vector<std::vector<int>>(numBuildings + 1, std::vector<int>());
    for (int i = 1; i <= numBuildings; ++i) {
      int buildingCost;
      std::cin >> buildingCost;
      cache[i] = 0;
      buildings[i] = buildingCost;
      dependences[i].reserve(numBuildings);
      degree[i] = 0;
    }

    for (int i = 0; i < numDependences; ++i) {
      int from, to;
      std::cin >> from >> to;
      dependences[from].emplace_back(to);
      degree[to] += 1;
    }

    int targetBuilding;
    std::cin >> targetBuilding;
    bfs();
    std::cout << cache[targetBuilding] << "\n";
  }
}
