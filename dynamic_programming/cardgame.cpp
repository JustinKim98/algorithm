#include <iostream>
#include <algorithm>

int point[1000];
int cache[1000001];
int cardBegin; // Start index of the cards
int cardEnd;   // End index of the cards

int encode(int cardBegin, int cardEnd)
{
    return cardBegin * 1000 + cardEnd;
}

// Returns best possible point that 'turn' can get
int tryToWin(bool turn, int remainer)
{
    // If there are no more remaining cards
    int code = encode(cardBegin, cardEnd);
    if (cache[code] > 0)
        return cache[code];
    if (cardBegin == cardEnd)
    {
        cache[code] = point[cardBegin];
        return point[cardBegin];
    }

    // pick one from the beginning
    int startCardPoint = point[cardBegin];
    cardBegin++;
    int opponentPointBegin = tryToWin(!turn, remainer - startCardPoint);
    cardBegin--;

    int endCardPoint = point[cardEnd];
    cardEnd--;
    int opponentPointEnd = tryToWin(!turn, remainer - endCardPoint);
    cardEnd++;

    if (opponentPointBegin < opponentPointEnd)
    {
        int myPoint = remainer - opponentPointBegin;
        cache[code] = myPoint;
        return myPoint;
    }
    else
    {
        int myPoint = remainer - opponentPointEnd;
        cache[code] = myPoint;
        return myPoint;
    }
}

int main()
{
    int testCases;
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> testCases;

    std::vector<int> answers(testCases);
    for (int i = 0; i < testCases; ++i)
    {
        std::fill(point, point + 1000, 0);
        std::fill(cache, cache + 1000001, 0);
        int numCards;
        std::cin >> numCards;
        cardBegin = 0;
        cardEnd = numCards - 1;
        int pointSum = 0;
        for (int cardIdx = 0; cardIdx < numCards; ++cardIdx)
        {
            std::cin >> point[cardIdx];
            pointSum += point[cardIdx];
        }
        answers[i] = tryToWin(true, pointSum);
    }

    for (int i = 0; i < testCases; ++i)
        std::cout << answers[i] << std::endl;

    return 0;
}