#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>
#define INF 1 << 30

int numCities;
int numConnections;
int startingPoint;
std::unordered_map<long, int> cache;
int map[19][19];
int choice[19][1 << 20];

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
      choice[position][visited] = 0;
      return cache[key];
    }
    return INF;
  }

  int minLength = INF;
  int chosenPath = 0;
  for (int i = 0; i < numCities; ++i) {
    if (map[position][i] > 0 && !isVisited(i, visited)) {
      auto maxLength = std::max(tsp(i, visited), map[position][i]);
      if (maxLength < minLength) {
        minLength = maxLength;
        chosenPath = i;
      }
    }
  }

  choice[position][visited] = chosenPath;

  cache[key] = minLength;
  return minLength;
}

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  std::cin >> numCities >> numConnections;

  for (int i = 0; i < 19; ++i)
    for (int j = 0; j < 19; ++j) {
      map[i][j] = 0;
    }

  for (int i = 0; i < numConnections; ++i) {
    int u, v, c;
    std::cin >> u >> v >> c;
    map[u - 1][v - 1] = c;
  }

  auto ans = tsp(0, 0);
  if (ans == INF)
    std::cout << -1 << "\n";
  else {
    std::cout << ans << "\n";

    int visited = 0;
    int position = 0;
    while (visited != ((1 << numCities) - 1)) {
      std::cout << position + 1 << " ";
      visited |= (1 << position);
      position = choice[position][visited];
    }
    std::cout << "\n";
  }

  return 0;
}
