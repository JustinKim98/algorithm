#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>


void increasingSequence(const std::vector<int>& sequence, std::vector<int>& largestLength)
{
    for(std::size_t i =0; i < sequence.size(); ++i)
    {
        int largest = 1;
        for(int sequenceIdx = 0; sequenceIdx < i; ++sequenceIdx)
        {
            if(sequence[sequenceIdx] < sequence[i])
            {
                largest = std::max(static_cast<int>(largestLength[sequenceIdx] + 1), largest);
            }
        }
        largestLength[i] = largest;
    }
}

int main()
{
    int length;
    std::cin>>length;
    std::vector<int> sequence(length);
    std::vector<int> largestLength(length);
    for(int i =0; i < length; ++i)
    {
        std::cin>>sequence[i];
    }

    increasingSequence(sequence, largestLength);

    std::size_t largest = 0;
    for(const auto seq : largestLength)
    {
        if(seq > largest)
        {
            largest = seq;
        }
    }
    std::cout<<largest<<"\n";
    return 0;
}