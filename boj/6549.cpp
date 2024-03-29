#include <iostream>
#include <cstdlib>
#include <deque>
#include <vector>

std::uint64_t solve(const std::vector<std::uint64_t> &fences)
{
    std::deque<std::uint64_t> stack;
    std::uint64_t maxSize = 0;
    stack.emplace_back(0);
    for (int i = 0; i < fences.size() - 1; ++i)
    {
        stack.emplace_back(i);

        while (stack.size() > 0 && fences[stack.back()] >= fences[i + 1])
        {
            // leftIdx = stack.back() - 1
            auto curMaxHeight = fences[stack.back()];
            stack.pop_back();

            if (stack.empty())
            {
                maxSize = std::max(maxSize, curMaxHeight * (i + 1));
            }
            else
                maxSize = std::max(maxSize, curMaxHeight * (i - stack.back()));
        }
    }

    return maxSize;
}

int main()
{
    std::deque<std::uint64_t> answers;
    while (true)
    {
        int numFences;
        std::cin >> numFences;
        if (numFences == 0)
            break;
        std::vector<std::uint64_t> fences(numFences + 1);
        for (int i = 0; i < numFences; ++i)
        {
            std::uint64_t height;
            std::cin >> height;
            fences[i] = height;
        }
        // Put zero to last fence
        fences[numFences] = 0;
        answers.emplace_back(solve(fences));
    }

    for (auto answer : answers)
    {
        std::cout << answer << "\n";
    }

    return 0;
}
