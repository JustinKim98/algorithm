#include <iostream>
#include <deque>

int length[101][101][101];

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    std::string strA, strB, strC;
    std::cin >> strA >> strB >> strC;

    length[0][0][0] = 0;

    for (int i = 1; i <= strA.size(); ++i)
    {
        for (int j = 1; j <= strB.size(); ++j)
        {
            for (int k = 1; k <= strC.size(); ++k)
                if (strA[i - 1] == strB[j - 1] && strB[j - 1] == strC[k - 1])
                {
                    length[i][j][k] = length[i - 1][j - 1][k - 1] + 1;
                }
                else
                {
                    length[i][j][k] = std::max(std::max(length[i - 1][j][k], length[i][j - 1][k]), length[i][j][k - 1]);
                }
        }
    }

    const auto lcs = length[strA.size()][strB.size()][strC.size()];
    std::cout << lcs << "\n";

    return 0;
}
