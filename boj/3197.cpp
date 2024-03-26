#include <queue>
#include <iostream>

char map[1500][1500];
bool swanVisited[1500][1500];
bool waterVisited[1500][1500];

std::deque<std::pair<int, int>> swanQueue;
std::deque<std::pair<int, int>> swanTempQueue;

std::deque<std::pair<int, int>> waterQueue;
std::deque<std::pair<int, int>> waterTempQueue;

int R, C;

bool swanBFS()
{
    while (!swanQueue.empty())
    {
        auto [rIdx, cIdx] = swanQueue.front();
        swanQueue.pop_front();

        if (rIdx - 1 >= 0 && !swanVisited[rIdx - 1][cIdx])
        {
            auto state = map[rIdx - 1][cIdx];
            if (state == '.')
                swanQueue.emplace_back(std::make_pair(rIdx - 1, cIdx));

            if (state == 'X')
                swanTempQueue.emplace_back(std::make_pair(rIdx - 1, cIdx));
            if (state == 'L')
            {
                return true;
            }
            swanVisited[rIdx - 1][cIdx] = true;
        }

        if (rIdx + 1 < R && !swanVisited[rIdx + 1][cIdx])
        {
            auto state = map[rIdx + 1][cIdx];
            if (state == '.')
                swanQueue.emplace_back(std::make_pair(rIdx + 1, cIdx));

            if (state == 'X')
                swanTempQueue.emplace_back(std::make_pair(rIdx + 1, cIdx));
            if (state == 'L')
            {
                return true;
            }
            swanVisited[rIdx + 1][cIdx] = true;
        }

        if (cIdx - 1 >= 0 && !swanVisited[rIdx][cIdx - 1])
        {
            auto state = map[rIdx][cIdx - 1];
            if (state == '.')
                swanQueue.emplace_back(std::make_pair(rIdx, cIdx - 1));

            if (state == 'X')
                swanTempQueue.emplace_back(std::make_pair(rIdx, cIdx - 1));
            if (state == 'L')
            {
                return true;
            }
            swanVisited[rIdx][cIdx - 1] = true;
        }

        if (cIdx + 1 < C && !swanVisited[rIdx][cIdx + 1])
        {
            auto state = map[rIdx][cIdx + 1];
            if (state == '.')
                swanQueue.emplace_back(std::make_pair(rIdx, cIdx + 1));

            if (state == 'X')
                swanTempQueue.emplace_back(std::make_pair(rIdx, cIdx + 1));
            if (state == 'L')
            {
                return true;
            }
            swanVisited[rIdx][cIdx + 1] = true;
        }
    }
    return false;
}

void waterBFS()
{
    while (!waterQueue.empty())
    {
        auto [rIdx, cIdx] = waterQueue.front();
        waterQueue.pop_front();

        if (rIdx - 1 >= 0 && !waterVisited[rIdx - 1][cIdx])
        {
            auto state = map[rIdx - 1][cIdx];

            if (state == 'X')
            {
                waterTempQueue.emplace_back(std::make_pair(rIdx - 1, cIdx));
                map[rIdx - 1][cIdx] = '.';
                waterVisited[rIdx - 1][cIdx] = true;
            }
        }

        if (rIdx + 1 < R && !waterVisited[rIdx + 1][cIdx])
        {
            auto state = map[rIdx + 1][cIdx];

            if (state == 'X')
            {
                waterTempQueue.emplace_back(std::make_pair(rIdx + 1, cIdx));
                map[rIdx + 1][cIdx] = '.';
                waterVisited[rIdx + 1][cIdx] = true;
            }
        }

        if (cIdx - 1 >= 0 && !waterVisited[rIdx][cIdx - 1])
        {
            auto state = map[rIdx][cIdx - 1];

            if (state == 'X')
            {
                waterTempQueue.emplace_back(std::make_pair(rIdx, cIdx - 1));
                map[rIdx][cIdx - 1] = '.';
                waterVisited[rIdx][cIdx - 1] = true;
            }
        }

        if (cIdx + 1 < C && !waterVisited[rIdx][cIdx + 1])
        {
            auto state = map[rIdx][cIdx + 1];

            if (state == 'X')
            {
                waterTempQueue.emplace_back(std::make_pair(rIdx, cIdx + 1));
                map[rIdx][cIdx + 1] = '.';
                waterVisited[rIdx][cIdx + 1] = true;
            }
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    std::cin >> R >> C;

    bool insertedSwan = false;
    for (int rIdx = 0; rIdx < R; ++rIdx)
    {
        for (int cIdx = 0; cIdx < C; ++cIdx)
        {
            waterVisited[rIdx][cIdx] = false;
            swanVisited[rIdx][cIdx] = false;
            std::cin >> map[rIdx][cIdx];

            if (map[rIdx][cIdx] == 'L')
            {
                if (!insertedSwan)
                {
                    swanQueue.emplace_back(std::make_pair(rIdx, cIdx));
                    swanVisited[rIdx][cIdx] = true;
                }
                waterQueue.emplace_back(std::make_pair(rIdx, cIdx));
                waterVisited[rIdx][cIdx] = true;
                insertedSwan = true;
            }
            if (map[rIdx][cIdx] == '.')
            {
                waterQueue.emplace_back(std::make_pair(rIdx, cIdx));
                waterVisited[rIdx][cIdx] = true;
            }
        }
    }

    bool foundSwan = false;
    int day = 0;

    while (!foundSwan)
    {
        foundSwan = swanBFS();
        if (foundSwan)
            break;
        waterBFS();
        swanQueue = swanTempQueue;
        waterQueue = waterTempQueue;
        swanTempQueue.clear();
        waterTempQueue.clear();
        day += 1;
    }

    std::cout << day << "\n";
    return 0;
}