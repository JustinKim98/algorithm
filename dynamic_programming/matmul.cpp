#include <iostream>
#include <cstdint>
#include <utility>
#include <vector>

std::uint32_t dp[501][501];

inline std::uint32_t
mulCost(std::pair<std::uint32_t, std::uint32_t> l, std::pair<std::uint32_t, std::uint32_t> r)
{
    auto [m, k] = l;
    auto n = std::get<1>(r);
    return m * n * k;
}

std::pair<std::uint32_t, std::uint32_t> getConfig(std::pair<std::uint32_t, std::uint32_t> l, std::pair<std::uint32_t, std::uint32_t> r)
{
    return std::make_pair(std::get<0>(l), std::get<1>(r));
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> matrices(N + 1);
    for (int i = 0; i < N; ++i)
    {
        std::uint32_t m, n;
        std::cin >> m >> n;
        matrices[i + 1] = std::make_pair(m, n);
    }

    if (N == 1)
    {
        std::cout << 0 << std::endl;
        return 0;
    }

    for (int i = 1; i < N; ++i)
    {
        dp[i][i] = 0;
        dp[i][i + 1] = mulCost(matrices[i], matrices[i + 1]);
    }
    dp[N][N] = 0;

    for (int size = 2; size <= N; ++size)
    {
        for (int startIdx = 1; startIdx <= N - size; ++startIdx)
        {
            std::uint32_t curMin = -1;
            for (int i = 0; i < size; ++i)
            {
                curMin = std::min(curMin, dp[startIdx][startIdx + i] + dp[startIdx + i + 1][startIdx + size] +
                                              mulCost(getConfig(matrices[startIdx], matrices[startIdx + i]),
                                                      getConfig(matrices[startIdx + i + 1], matrices[startIdx + size])));
            }
            dp[startIdx][startIdx + size] = curMin;
        }
    }

    // std::cout << dp[1][2] << std::endl;
    // std::cout << dp[2][3] << std::endl;
    // std::cout << dp[1][3] << std::endl;

    std::cout << dp[1][N] << std::endl;
    return 0;
}