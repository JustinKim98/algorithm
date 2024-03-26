#include <iostream>
#include <vector>

bool cache[2001][2001];

int main() {
  int n, numQuestions;
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);
  std::cin >> n;
  std::vector<int> numbers(n);
  for (int i = 0; i < n; ++i)
    std::cin >> numbers.at(i);

  std::cin >> numQuestions;
  std::vector<std::pair<int, int>> questions(numQuestions);

  for (int i = 0; i < numQuestions; ++i) {
    int start, end;
    std::cin >> start >> end;
    questions.at(i) = std::make_pair(start, end);
  }

  for (int i = 0; i < 2000; ++i)
    cache[1][i] = true;

  for (int length = 2; length <= n; ++length) {
    for (int startIdx = 0; startIdx < n - 1; ++startIdx) {
      if (startIdx + length - 1 < n) {

        if (length == 2) {
          cache[length][startIdx] =
              numbers.at(startIdx) == numbers.at(startIdx + length - 1);
        } else
          cache[length][startIdx] =
              numbers.at(startIdx) == numbers.at(startIdx + length - 1) &&
              cache[length - 2][startIdx + 1];
      }
    }
  }

  for (const auto &[start, end] : questions) {
    // std::cout << start << "|" << end << std::endl;
    if (cache[end - start + 1][start - 1])
      std::cout << 1 << "\n";
    else
      std::cout << 0 << "\n";
  }
}