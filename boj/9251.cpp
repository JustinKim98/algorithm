#include <iostream>
#include <deque>

int length[1001][1001];

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    std::string strA, strB;
    std::cin >> strA >> strB;

    length[0][0] = 0;
    length[0][1] = 0;
    length[1][0] = 0;

    for (int i = 1; i <= strA.size(); ++i)
    {
        for (int j = 1; j <= strB.size(); ++j)
        {
            if (strA[i - 1] == strB[j - 1])
            {
                length[i][j] = length[i - 1][j - 1] + 1;
            }
            else
            {
                length[i][j] = std::max(length[i - 1][j], length[i][j - 1]);
            }
        }
    }

    const auto lcs = length[strA.size()][strB.size()];
    std::cout << lcs << "\n";

    if (lcs == 0)
        return 0;

    char str[1001];
    int i = strA.size(), j = strB.size();
    str[lcs] = '\0';
    int curIdx = lcs - 1;

    while (curIdx >= 0)
    {
        if (length[i][j] == length[i - 1][j])
        {
            i -= 1;
        }
        else if (length[i][j] == length[i][j - 1])
        {
            j -= 1;
        }
        else if (length[i - 1][j - 1] + 1 == length[i][j])
        {
            str[curIdx] = strA[i - 1];
            i -= 1;
            j -= 1;
            curIdx -= 1;
        }
    }

    std::cout << str << "\n";

    return 0;
}
