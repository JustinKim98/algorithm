#include <iostream>
#include <limits>

int N;
bool type[200000];

int main() {
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  std::cin >> N;
  std::string str;
  std::cin >> str;
  for (int i = 0; i < N; ++i) {
    if (str[i] == 's')
      type[i] = true;
    else
      type[i] = false;
  }

  int end = N / 2;
  int start = 0;
  int diff = 0;

  for (int i = 0; i < end; ++i) {
    if (type[i])
      diff += 1;
    else
      diff -= 1;
  }

  if (diff == 0) {
    std::cout << 1 << "\n";
    std::cout << end << "\n";
    return 0;
  }

  while (end < N) {
    if (type[start] && !type[end])
      diff -= 2;

    if (!type[start] && type[end])
      diff += 2;

    start++;
    end++;

    if (diff == 0)
      break;
  }

  //   if (end == N) {
  //     std::cout << 1 << "\n";
  //     std::cout << start << "\n";
  //   }
  std::cout << 2 << "\n";
  std::cout << start << " " << end << "\n";
  return 0;
}