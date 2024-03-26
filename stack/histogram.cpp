#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

int solve(const std::vector<unsigned int>& histogram)
{
    std::deque<unsigned int> stack;

    unsigned int largestArea = 0;
    for(std::size_t i =0; i < histogram.size(); ++i)
    {
        const auto rightSideHeight = histogram.at(i);
        while(!stack.empty() && histogram.at(stack.back()) >= rightSideHeight)
        {
            const auto curHighestIdx = stack.back();
            const auto currentHeight = histogram.at(curHighestIdx);
            stack.pop_back();
            

            int width = 0;
            if(stack.empty())
            {
                width = i;
            }
            else
            {
                width = i - stack.back() - 1;
            }
            largestArea = std::max(largestArea, width*currentHeight);
        }

        stack.push_back(i);
    }

    return largestArea;
}

int main()
{
    int n;
    std::cin>>n;
    std::vector<unsigned int> histogram(n + 1);

    for(int i =0; i < n; ++i)
    {
        unsigned int height;
        std::cin>>height;
        histogram.at(i) = height;
    }
    histogram.at(n) = 0;
    std::cout<<solve(histogram)<<"\n";
    return 0;
}