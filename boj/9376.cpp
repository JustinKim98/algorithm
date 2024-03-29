#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

int row, col;

std::vector<std::pair<int, int>> indices = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

char map[102][102];
bool visited[102][102];
int cost0[102][102];
int cost1[102][102];
int cost2[102][102];

struct Point
{
    Point(std::pair<int, int> indices, int cost) : Indices(indices), Cost(cost) {}

    bool operator<(const Point &rhs) const
    {
        return Cost < rhs.Cost;
    }

    bool operator>(const Point &rhs) const
    {
        return Cost > rhs.Cost;
    }

    std::pair<int, int> Indices;
    int Cost;
};

std::priority_queue<Point, std::vector<Point>, std::greater<>> minHeap;

bool inRange(int rowIdx, int colIdx)
{
    return rowIdx >= 0 && rowIdx <= row + 1 && colIdx >= 0 && colIdx <= col + 1;
}

void dijkstra(std::pair<int, int> begin, int costArr[102][102])
{
    minHeap.emplace(begin, 0);
    costArr[std::get<0>(begin)][std::get<1>(begin)] = 0;

    while (!minHeap.empty())
    {
        Point minNode = minHeap.top();
        minHeap.pop();
        auto [rowIdx, colIdx] = minNode.Indices;
        auto curCost = costArr[rowIdx][colIdx];
        for (auto [i, j] : indices)
        {
            if (!inRange(rowIdx + i, colIdx + j))
                continue;

            if (visited[rowIdx + i][colIdx + j])
                continue;

            auto mapVal = map[rowIdx + i][colIdx + j];
            if (mapVal == '*')
                continue;

            auto &costVal = costArr[rowIdx + i][colIdx + j];
            if ((mapVal == '.' || mapVal == '$') && costVal > curCost)
                costVal = curCost;
            if (mapVal == '#' && costVal > curCost + 1)
                costVal = curCost + 1;

            visited[rowIdx + i][colIdx + j] = true;
            minHeap.emplace(std::make_pair(rowIdx + i, colIdx + j), costVal);
        }
    }
}

void clear()
{
    for (int rowIdx = 0; rowIdx < row + 2; ++rowIdx)
    {
        for (int colIdx = 0; colIdx < col + 2; ++colIdx)
        {
            visited[rowIdx][colIdx] = false;
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    int numCases;
    std::cin >> numCases;

    std::vector<int> results(numCases);

    for (int caseIdx = 0; caseIdx < numCases; ++caseIdx)
    {
        std::cin >> row >> col;
        std::vector<std::pair<int, int>> prisoner;
        std::vector<std::pair<int, int>> doors;
        prisoner.reserve(2);

        for (int rowIdx = 0; rowIdx < row + 2; ++rowIdx)
        {
            for (int colIdx = 0; colIdx < col + 2; ++colIdx)
            {
                cost0[rowIdx][colIdx] = std::numeric_limits<int>::max();
                cost1[rowIdx][colIdx] = std::numeric_limits<int>::max();
                cost2[rowIdx][colIdx] = std::numeric_limits<int>::max();
                visited[rowIdx][colIdx] = false;
                if (rowIdx == 0 || colIdx == 0 || rowIdx == row + 1 || colIdx == col + 1)
                {
                    map[rowIdx][colIdx] = '.';
                }
                else
                {

                    char val;
                    std::cin >> val;
                    map[rowIdx][colIdx] = val;
                    if (val == '$')
                        prisoner.emplace_back(std::make_pair(rowIdx, colIdx));
                }
            }
        }

        dijkstra(std::make_pair(0, 0), cost0);
        clear();
        dijkstra(prisoner[0], cost1);
        clear();
        dijkstra(prisoner[1], cost2);
        clear();

        int min = std::numeric_limits<int>::max();
        for (int rowIdx = 0; rowIdx < row + 2; ++rowIdx)
        {
            for (int colIdx = 0; colIdx < col + 2; ++colIdx)
            {
                int curCost;
                auto costSum = cost0[rowIdx][colIdx] + cost1[rowIdx][colIdx] + cost2[rowIdx][colIdx];
                cost0[rowIdx][colIdx] = std::numeric_limits<int>::max();
                cost1[rowIdx][colIdx] = std::numeric_limits<int>::max();
                cost2[rowIdx][colIdx] = std::numeric_limits<int>::max();

                if (map[rowIdx][colIdx] == '#')
                    curCost = costSum - 2;
                else
                    curCost = costSum;

                if (curCost < min)
                    min = curCost;
            }
        }

        results[caseIdx] = min;
    }

    for (auto res : results)
    {
        std::cout << res << "\n";
    }

    return 0;
}
