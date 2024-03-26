// BOJ 2206
#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cmath>

using st = std::uint32_t;
int M, N, K;

st visited[1000][1000][11];
bool map[1000][1000];

inline bool inRange(int m, int n, int destructed)
{
    return m < M && m >= 0 && n < N && n >= 0 && destructed <= K;
}

void bfs()
{
    std::queue<std::tuple<st, st, st>> queue;
    queue.push(std::make_tuple(0, 0, 0));
    visited[0][0][0] = 1;
    while (!queue.empty())
    {
        const auto [m, n, destructed] = queue.front();
        const auto curDist = visited[m][n][destructed];
        // std::cout << "visiting:" << m << n << destructed << std::endl;
        queue.pop();

        /// 0, 1
        if (inRange(m + 0, n + 1, destructed) && visited[m + 0][n + 1][destructed] > curDist + 1 && !map[m + 0][n + 1])
        {
            visited[m + 0][n + 1][destructed] = curDist + 1;
            queue.push(std::make_tuple(m + 0, n + 1, destructed));
        }
        if (inRange(m + 0, n + 1, destructed + 1) && visited[m + 0][n + 1][destructed + 1] > curDist + 1 && map[m + 0][n + 1])
        {
            visited[m + 0][n + 1][destructed + 1] = curDist + 1;
            queue.push(std::make_tuple(m + 0, n + 1, destructed + 1));
        }

        /// 1, 0
        if (inRange(m + 1, n + 0, destructed) && visited[m + 1][n + 0][destructed] > curDist + 1 && !map[m + 1][n + 0])
        {
            visited[m + 1][n + 0][destructed] = curDist + 1;
            queue.push(std::make_tuple(m + 1, n + 0, destructed));
        }
        if (inRange(m + 1, n + 0, destructed + 1) && visited[m + 1][n + 0][destructed + 1] > curDist + 1 && map[m + 1][n + 0])
        {
            visited[m + 1][n + 0][destructed + 1] = curDist + 1;
            queue.push(std::make_tuple(m + 1, n + 0, destructed + 1));
        }

        if (inRange(m - 1, n + 0, destructed) && visited[m - 1][n + 0][destructed] > curDist + 1 && !map[m - 1][n + 0])
        {
            visited[m - 1][n + 0][destructed] = curDist + 1;
            queue.push(std::make_tuple(m - 1, n + 0, destructed));
        }
        if (inRange(m - 1, n + 0, destructed + 1) && visited[m - 1][n + 0][destructed + 1] > curDist + 1 && map[m - 1][n + 0])
        {
            visited[m - 1][n + 0][destructed + 1] = curDist + 1;
            queue.push(std::make_tuple(m - 1, n + 0, destructed + 1));
        }

        if (inRange(m + 0, n - 1, destructed) && visited[m + 0][n - 1][destructed] > curDist + 1 && !map[m + 0][n - 1])
        {
            visited[m + 0][n - 1][destructed] = curDist + 1;
            queue.push(std::make_tuple(m + 0, n - 1, destructed));
        }
        if (inRange(m + 0, n - 1, destructed + 1) && visited[m + 0][n - 1][destructed + 1] > curDist + 1 && map[m + 0][n - 1])
        {
            visited[m + 0][n - 1][destructed + 1] = curDist + 1;
            queue.push(std::make_tuple(m + 0, n - 1, destructed + 1));
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
                visited[m][n][k] = static_cast<st>(-1);
            }
        }
    }

    bfs();

    st minDist = static_cast<st>(-1);
    for (int k = 0; k <= K; ++k)
    {
        if (minDist > visited[M - 1][N - 1][k])
            minDist = visited[M - 1][N - 1][k];
    }
    if (minDist == static_cast<st>(-1))
        std::cout << -1 << std::endl;
    else
        std::cout << minDist << std::endl;

    return 0;
}
