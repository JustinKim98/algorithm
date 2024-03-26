#include <iostream>
#include <limits>
#include <unordered_map>
#define INF 1 << 30

int visited;
int numCities;
int startingPoint;
std::unordered_map<long, int> cache;
int map[17][17];

long createKey(int position, int visited) {
  return (static_cast<long>(visited) << 32) | static_cast<long>(position);
}

bool isVisited(int position, int visited) {
  if ((1 << position) & visited)
    return true;
  return false;
}

int tsp(int position, int visited) {
  auto key = createKey(position, visited);
  if (cache.find(key) != cache.end())
    return cache[key];

  visited |= (1 << position);

  if (visited == ((1 << numCities) - 1)) {
    if (map[position][0] > 0) {
      cache[key] = map[position][0];
      return cache[key];
    }
    return INF;
  }

  int minLength = INF;
  bool isEnd = true;
  for (int i = 0; i < numCities; ++i) {
    if (map[position][i] > 0 && !isVisited(i, visited)) {
      isEnd = false;
      minLength = std::min(tsp(i, visited) + map[position][i], minLength);
    }
  }

  cache[key] = minLength;
  return minLength;
}

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  std::cin >> numCities;
  for (int i = 0; i < numCities; ++i)
    for (int j = 0; j < numCities; ++j) {
      std::cin >> map[i][j];
    }

  std::cout << tsp(0, 0) << "\n";

  return 0;
}