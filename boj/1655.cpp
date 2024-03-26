#include <iostream>
#include <list>
#include <vector>
#include <queue>

int main()
{
    int numCases;
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> numCases;

    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    std::vector<int> numbers(numCases);
    for (int i = 0; i < numCases; ++i)
        std::cin >> numbers[i];

    maxHeap.emplace(numbers[0]);
    std::cout << maxHeap.top() << "\n";
    for (int i = 1; i < numCases; ++i)
    {
        auto curNum = numbers[i];
        if (curNum <= maxHeap.top())
        {
            maxHeap.emplace(curNum);
            if (maxHeap.size() > minHeap.size() + 1)
            {
                minHeap.emplace(maxHeap.top());
                maxHeap.pop();
            }
            std::cout << maxHeap.top() << "\n";
        }
        else
        {
            minHeap.emplace(curNum);
            if (minHeap.size() > maxHeap.size())
            {
                maxHeap.emplace(minHeap.top());
                minHeap.pop();
            }
            std::cout << maxHeap.top() << "\n";
        }
    }

    return 0;
}
