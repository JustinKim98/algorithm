#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#define MAX 1000000

int bruteforceClosest(int numDigits, int channel, const std::vector<int>& aliveButtons, int curDigitIdx, int curNum)
{
    if(numDigits == curDigitIdx)
        return std::abs(channel - curNum);

    int smallest = MAX;
    for(int i =0; i < aliveButtons.size(); ++i)
    {
        int curBase = aliveButtons.at(i)*pow(10, numDigits-curDigitIdx-1);
        int diff = bruteforceClosest(numDigits, channel, aliveButtons, curDigitIdx + 1, curNum + curBase);
        if(diff < smallest)
            smallest = diff;
    }

    return smallest;
}

int distanceWithOneLessDigit(int numDigits, int channel, const std::vector<int>& aliveButtons)
{
    if(numDigits <= 1)
        return MAX;

    int largestButton = 0;
    for(auto button : aliveButtons)
        if(button > largestButton)
            largestButton = button;

    int number = 0;
    for(int i =0; i < numDigits-1; ++i)
        number += largestButton*pow(10, i);


    return std::abs(channel - number) + numDigits - 1;
}

int distanceWithOneMoreDigit(int numDigits, int channel, const std::vector<int>& aliveButtons)
{
    int smallestButton = 10;
    int nonZeroSmallestButton = 10;
    for(auto button : aliveButtons)
    {
        if(button < smallestButton)
            smallestButton = button;

        if(button < nonZeroSmallestButton && button > 0)
            nonZeroSmallestButton = button;
    }

    int number = 0;

    for(int i =0; i < numDigits; ++i)
        number += smallestButton*pow(10, i);
    
    number += nonZeroSmallestButton*pow(10, numDigits);

    //std::cout<<"number:"<<number<<std::endl;

    return std::abs(channel - number) + numDigits + 1;
}


int main()
{
    int channel, numBroken;
    std::cin>>channel;
    std::cin>>numBroken;

    std::vector<int> brokenButtons(numBroken);
    std::vector<int> aliveButtons;

    aliveButtons.reserve(10 - numBroken);

    for(int i=0; i < numBroken; ++i)
    {
        int value;
        std::cin>>value;
        brokenButtons[i] = value;
    }

    for(int i =0; i < 10; ++i)
        if(std::find(brokenButtons.begin(), brokenButtons.end(), i) == brokenButtons.end())
        {
            aliveButtons.emplace_back(i);
        }

    int numDigits = 0;
    while(channel > std::pow(10, numDigits))
        numDigits++;
    if(channel <= 1)
        numDigits = 1;
    
    if(aliveButtons.empty())
    {
        std::cout<<std::abs(channel-100)<<"\n";
        return 0;
    }


    if(aliveButtons.size() == 1 && aliveButtons.at(0) == 0)
    {
        std::cout<<std::min(std::abs(channel - 100), channel + 1)<<"\n";
        return 0;
    }

    std::vector<int> distances(4);
    distances[0] = std::abs(channel - 100);
    distances[1] = distanceWithOneLessDigit(numDigits, channel, aliveButtons);
    distances[2] = distanceWithOneMoreDigit(numDigits, channel, aliveButtons);
    int closest = bruteforceClosest(numDigits, channel, aliveButtons, 0, 0);
    //std::cout<<"closest:"<<closest<<std::endl;
    distances[3] = closest + numDigits;

    int smallestDist = MAX;
    for(auto dist : distances)
        if(dist < smallestDist)
            smallestDist = dist;

    //std::cout<<distances[0]<<","<<distances[1]<<","<<distances[2]<<","<<distances[3]<<std::endl;;

    std::cout<<smallestDist<<"\n";
    return 0;
}