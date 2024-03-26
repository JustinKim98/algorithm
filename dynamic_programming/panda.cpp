#include <deque>
#include <iostream>
#include <utility>
#include <vector>

int n;
int forest[500][500];
int cache[500][500];
int degree[500][500];

int getInDegree(std::pair<int, int> pos) {
  int i = std::get<0>(pos);
  int j = std::get<1>(pos);
  int curNodeVal = forest[i][j];

  int numDegree = 0;
  if (i - 1 >= 0 && forest[i - 1][j] < curNodeVal)
    numDegree += 1;

  if (i + 1 < n && forest[i + 1][j] < curNodeVal)
    numDegree += 1;

  if (j - 1 >= 0 && forest[i][j - 1] < curNodeVal)
    numDegree += 1;

  if (j + 1 < n && forest[i][j + 1] < curNodeVal)
    numDegree += 1;

  return numDegree;
}

std::vector<std::pair<int, int>> getOutNodes(std::pair<int, int> pos) {
  std::vector<std::pair<int, int>> outNodes;
  outNodes.reserve(4);

  int i = std::get<0>(pos);
  int j = std::get<1>(pos);
  int curNodeVal = forest[i][j];

  if (i - 1 >= 0 && forest[i - 1][j] > curNodeVal)
    outNodes.emplace_back(std::make_pair(i - 1, j));

  if (i + 1 < n && forest[i + 1][j] > curNodeVal)
    outNodes.emplace_back(std::make_pair(i + 1, j));

  if (j - 1 >= 0 && forest[i][j - 1] > curNodeVal)
    outNodes.emplace_back(std::make_pair(i, j - 1));

  if (j + 1 < n && forest[i][j + 1] > curNodeVal)
    outNodes.emplace_back(std::make_pair(i, j + 1));

  return outNodes;
}

void bfs() {
  std::deque<std::pair<int, int>> queue;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      if (degree[i][j] == 0) {
        queue.emplace_back(std::make_pair(i, j));
        cache[i][j] = 1;
      }
    }

  while (!queue.empty()) {
    auto curPos = queue.front();
    queue.pop_front();
    auto outNodes = getOutNodes(curPos);
    int curX = std::get<0>(curPos);
    int curY = std::get<1>(curPos);

    for (auto nextPos : outNodes) {
      int nextX = std::get<0>(nextPos);
      int nextY = std::get<1>(nextPos);
      int nextVal = cache[curX][curY] + 1;
      if (cache[nextX][nextY] < nextVal)
        cache[nextX][nextY] = nextVal;

      if (--degree[nextX][nextY] == 0)
        queue.emplace_back(std::make_pair(nextX, nextY));
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> forest[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      degree[i][j] = getInDegree(std::make_pair(i, j));
    }
  }

  bfs();

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      ans = std::max(ans, cache[i][j]);
    }
  }
  std::cout << ans << "\n";
}