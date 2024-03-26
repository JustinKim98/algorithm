#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int largestFromMiddle(const std::vector<int>& fence, int startIdx, int endIdx)
{
    int midIdx = (endIdx + startIdx)/2;

    if(midIdx + 1 == endIdx && endIdx == fence.size())
        return fence.at(startIdx);
    
    int lowestHeight = std::min(fence.at(midIdx), fence.at(midIdx+1));
    int largest = lowestHeight*2;
    int fenceSize = 2;

    int lowIdx = midIdx;
    int highIdx = midIdx + 1;

    //! go largest as possible
    while(lowIdx - 1 >= 0 && fence.at(lowIdx - 1) >= lowestHeight)
    {
        lowIdx -= 1;
        fenceSize += 1;
        largest = fenceSize * lowestHeight;
    }

    while(highIdx + 1 < endIdx && fence.at(highIdx + 1) >= lowestHeight)
    {
        highIdx += 1;
        fenceSize += 1;
        largest = fenceSize * lowestHeight;
    }

    while(highIdx < endIdx-1)
    {
        int oldLowIdx = lowIdx;
        int oldHighIdx = highIdx;
        while(lowIdx > 0)
        {
            lowIdx -= 1;
            lowestHeight = fence.at(lowIdx);
            fenceSize += 1;
            if(largest < fenceSize*lowestHeight)
                largest = fenceSize * lowestHeight;
            while(lowIdx - 1 >= 0 && fence.at(lowIdx - 1) >= lowestHeight)
            {
                lowIdx -= 1;
                fenceSize += 1;
                if(largest < fenceSize*lowestHeight)
                    largest = fenceSize * lowestHeight;
            }

            while(highIdx + 1 < endIdx && fence.at(highIdx + 1) >= lowestHeight)
            {       
                highIdx += 1;
                fenceSize += 1;
                if(largest < fenceSize*lowestHeight)
                    largest = fenceSize * lowestHeight;
            }
        }

        if(highIdx + 1 >= endIdx)
            break;

        lowIdx = oldLowIdx;
        highIdx += 1;
        fenceSize += 1;
        lowestHeight = fence.at(highIdx);
        if(largest < fenceSize*lowestHeight)
            largest = fenceSize * lowestHeight;

        while(lowIdx - 1 >= 0 && fence.at(lowIdx - 1) >= lowestHeight)
        {
            lowIdx -= 1;
            fenceSize += 1;
            if(largest < fenceSize*lowestHeight)
                largest = fenceSize * lowestHeight;
        }

        while(highIdx + 1 < endIdx && fence.at(highIdx + 1) >= lowestHeight)
        {       
            highIdx += 1;
            fenceSize += 1;
            if(largest < fenceSize*lowestHeight)
                largest = fenceSize * lowestHeight;
        }
    }

    return largest;
}

int solve(const std::vector<int>& fence, int startIdx, int endIdx)
{
    if(startIdx == endIdx && endIdx < fence.size())
        return fence.at(startIdx);
    if(startIdx == endIdx - 1)
        return std::max(largestFromMiddle(fence, startIdx, endIdx), fence.at(startIdx));

    int mid = (endIdx + startIdx)/2;

    int largest0 = largestFromMiddle(fence, startIdx, endIdx);
    int largest1 = solve(fence, startIdx, mid);
    int largest2 = solve(fence, mid, endIdx);

    return std::max(std::max(largest0, largest1), largest2);
}

int main()
{
    int numFences;
    std::cin>>numFences;
    std::vector<int> fences(numFences);

    for(int i = 0; i < numFences; ++i)
        std::cin>>fences.at(i);

    auto largest = solve(fences, 0, fences.size());
    std::cout<<largest<<std::endl;
}