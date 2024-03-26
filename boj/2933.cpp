#include <iostream>
#include <queue>
#include <set>

char mineral[101][101];
int row, col;

std::vector<std::pair<int, int>> pairs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// Makes cluster fall to the lowest point as possible
void dropCluster(const std::set<std::pair<int, int>> &cluster, int fallDistance)
{
    for (auto [rowIdx, colIdx] : cluster)
    {
        mineral[rowIdx][colIdx] = '.';
        mineral[rowIdx - fallDistance][colIdx] = 'x';
    }
}

// returns lowest part of the cluster
int getCluster(std::set<std::pair<int, int>> &visited, int rowIdx, int colIdx)
{

    if (rowIdx < 0 || rowIdx >= row || colIdx < 0 || colIdx >= col)
        return 0;

    if (mineral[rowIdx][colIdx] != 'x')
        return 0;

    std::queue<std::pair<int, int>> queue;
    queue.emplace(std::make_pair(rowIdx, colIdx));
    visited.emplace(rowIdx, colIdx);

    while (!queue.empty())
    {
        auto [curRow, curCol] = queue.front();
        if (curRow == 0)
        {
            return 0;
        }
        queue.pop();

        int fallDistance = 101;
        for (auto [i, j] : pairs)
        {
            int searchRowIdx = curRow + i;
            int searchColIdx = curCol + j;

            if (searchRowIdx < row && searchRowIdx >= 0 && searchColIdx < col && searchColIdx >= 0)
            {
                if (mineral[searchRowIdx][searchColIdx] == 'x' && visited.find(std::make_pair(searchRowIdx, searchColIdx)) == visited.end())
                {

                    // Cluster touches the floor
                    if (searchRowIdx == 0)
                    {
                        return 0;
                    }

                    queue.emplace(searchRowIdx, searchColIdx);
                    visited.emplace(searchRowIdx, searchColIdx);
                }
            }
        }
    }

    // Identify fall distance
    int fallDistance = 101;
    for (auto [curRow, curCol] : visited)
    {
        if (curRow - 1 >= 0 && mineral[curRow - 1][curCol] != 'x')
        {
            int idx = 0;
            while (curRow - idx - 1 >= 0 && mineral[curRow - idx - 1][curCol] != 'x')
            {
                idx += 1;
            }

            if (curRow - idx - 1 >= 0 && visited.find(std::make_pair(curRow - idx - 1, curCol)) != visited.end())
                continue;

            if (idx < fallDistance)
            {
                fallDistance = idx;
            }
        }
    }

    return fallDistance;
}

void shoot(bool isLeft, int level)
{
    int idx = 0;
    if (isLeft)
    {
        while (idx < col && mineral[level][idx] != 'x')
        {
            idx += 1;
        }
    }
    else
    {
        idx = col;
        while (idx >= 0 && mineral[level][idx] != 'x')
        {
            idx -= 1;
        }
    }

    if (idx < col && idx >= 0 && mineral[level][idx] == 'x')
    {
        mineral[level][idx] = '.';

        std::set<std::pair<int, int>> visited;
        if (int distance = getCluster(visited, level + 1, idx))
        {
            dropCluster(visited, distance);
            return;
        }

        visited.clear();
        if (int distance = getCluster(visited, level, idx + 1))
        {
            dropCluster(visited, distance);
            return;
        }

        visited.clear();
        if (int distance = getCluster(visited, level, idx - 1))
        {
            dropCluster(visited, distance);
            return;
        }

        visited.clear();
        if (int distance = getCluster(visited, level - 1, idx))
        {
            dropCluster(visited, distance);
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> row >> col;

    for (int i = row - 1; i >= 0; --i)
    {
        for (int j = 0; j < col; ++j)
        {
            std::cin >> mineral[i][j];
        }
    }

    int numThrow;
    std::cin >> numThrow;
    std::vector<int> throws(numThrow);
    for (int i = 0; i < numThrow; ++i)
        std::cin >> throws[i];

    bool isLeft = true;
    for (auto level : throws)
    {
        shoot(isLeft, level - 1);
        isLeft = !isLeft;
    }

    for (int i = row - 1; i >= 0; --i)
    {
        for (int j = 0; j < col; ++j)
        {
            std::cout << mineral[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}
