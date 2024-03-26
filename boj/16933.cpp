#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cmath>

int M, N, K;

std::uint32_t visited[1000][1000][11][2];
bool map[1000][1000];

std::vector<std::pair<int, int>> indices = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool inRange(int m, int n, int destructed)
{
    return m < M && m >= 0 && n < N && n >= 0 && destructed <= K;
}

void bfs()
{
    std::queue<std::tuple<int, int, int, bool>> queue;
    queue.push(std::make_tuple(0, 0, 0, true));
    visited[0][0][0][1] = 1;
    while (!queue.empty())
    {
        const auto [m, n, destructed, isDay] = queue.front();
        const auto curDist = visited[m][n][destructed][isDay];
        // std::cout << "visiting:" << m << n << destructed << " isDay : " << isDay << " dist : " << curDist << std::endl;
        queue.pop();

        for (auto [i, j] : indices)
        {
            /// Do not destruct wall
            auto nextMIdx = m + i, nextNIdx = n + j;
            if (!inRange(nextMIdx, nextNIdx, destructed))
                continue;

            auto nextDist = visited[nextMIdx][nextNIdx][destructed][!isDay];
            if (nextDist > curDist + 1 && !map[nextMIdx][nextNIdx])
            {
                visited[nextMIdx][nextNIdx][destructed][!isDay] = curDist + 1;
                queue.emplace(nextMIdx, nextNIdx, destructed, !isDay);
            }

            if (!inRange(nextMIdx, nextNIdx, destructed + 1))
                continue;

            /// Destruct wall
            if (isDay && nextDist > curDist + 1 && map[nextMIdx][nextNIdx])
            {
                visited[nextMIdx][nextNIdx][destructed + 1][!isDay] = curDist + 1;
                queue.emplace(nextMIdx, nextNIdx, destructed + 1, !isDay);
            }
        }

        if (!isDay && visited[m][n][destructed][!isDay] > curDist + 1)
        {
            visited[m][n][destructed][!isDay] = curDist + 1;
            queue.emplace(m, n, destructed, !isDay);
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    std::cin >> M >> N >> K;

    for (int m = 0; m < M; ++m)
    {
        char str[1001];
        std::cin >> str;
        for (int n = 0; n < N; ++n)
        {
            if (str[n] == '1')
                map[m][n] = 1;
            else
                map[m][n] = 0;

            for (int k = 0; k <= K; ++k)
            {
                visited[m][n][k][0] = static_cast<std::uint32_t>(-1);
                visited[m][n][k][1] = static_cast<std::uint32_t>(-1);
            }
        }
    }

    bfs();

    auto minDist = static_cast<std::uint32_t>(-1);
    for (int k = 0; k <= K; ++k)
    {
        if (minDist > visited[M - 1][N - 1][k][0])
            minDist = visited[M - 1][N - 1][k][0];
        if (minDist > visited[M - 1][N - 1][k][1])
            minDist = visited[M - 1][N - 1][k][1];
    }
    if (minDist == static_cast<std::uint32_t>(-1))
        std::cout << -1 << std::endl;
    else
        std::cout << minDist << std::endl;

    return 0;
}
