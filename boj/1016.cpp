#include <iostream>
#include <vector>

int main()
{
    std::int64_t min, max;
    std::cin >> min >> max;

    std::int64_t i = 2;
    std::vector<bool> sieve(max - min + 2, true);
    std::int64_t ans = max - min + 1;

    while (i * i <= max)
    {
        auto squared = i * i;
        auto curNum = (min / squared);
        if (curNum * squared < min)
        {
            curNum += 1;
        }

        while (curNum * squared <= max)
        {
            auto curIdx = curNum * squared - min;
            if (sieve[curIdx])
            {
                sieve[curIdx] = false;
                ans -= 1;
            }
            curNum += 1;
        }

        i += 1;
    }

    std::cout << ans << "\n";
}