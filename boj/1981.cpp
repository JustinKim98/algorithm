#include <iostream>
#include <queue>
#include <limits>
#include <tuple>

int array[100][100];
int maxVal[100][100][200];

int size;

std::vector<std::pair<int, int>> offsets = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

bool isValidIdx(int i, int j)
{
    return i >= 0 && i < size && j >= 0 && j < size;
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> size;

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            int number;
            std::cin >> number;
            array[i][j] = number;
            for (int k = 0; k < 200; ++k)
            {
                maxVal[i][j][k] = std::numeric_limits<int>::max();
            }
        }

    std::queue<std::tuple<int, int, int, int>> queue;
    queue.emplace(0, 0, array[0][0], array[0][0]);
    maxVal[0][0][array[0][0]] = array[0][0];
    int minDiff = std::numeric_limits<int>::max();
    while (!queue.empty())
    {
        auto [curRow, curCol, curMin, curMax] = queue.front();
        queue.pop();

        if (curRow == size - 1 && curCol == size - 1)
        {
            if (minDiff > curMax - curMin)
                minDiff = curMax - curMin;
        }

        for (auto [i, j] : offsets)
        {
            auto nextRow = curRow + i, nextCol = curCol + j;

            if (isValidIdx(nextRow, nextCol))
            {
                if (maxVal[nextRow][nextCol][curMin] > curMax)
                {
                    maxVal[nextRow][nextCol][curMin] = curMax;
                    auto val = array[nextRow][nextCol];
                    auto nextMin = std::min(val, curMin);
                    auto nextMax = std::max(val, curMax);

                    // std::cout << "curRow : " << curRow << " curCol : " << curCol << std::endl;
                    // std::cout << "curMin : " << curMin << " curMax : " << curMax << std::endl;

                    queue.emplace(nextRow, nextCol, nextMin, nextMax);
                }
            }
        }
    }

    std::cout << minDiff << std::endl;

    return 0;
}
