#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>

// visited array in [id][cost]
int minDist[101][10001];

int numAirports, money, numTickets;

struct Point
{
    int Id;
    int Cost;
    int Dist;

    bool operator<(const Point &rhs) const
    {
        return Dist < rhs.Dist;
    }

    bool operator>(const Point &rhs) const
    {
        return Dist > rhs.Dist;
    }
};

// id, taken cost
std::priority_queue<Point, std::vector<Point>, std::greater<>>
    queue;

bool dijkstra(const std::vector<std::deque<std::tuple<int, int, int>>> &airports)
{
    queue.emplace(Point{0, 0, 0});

    while (!queue.empty())
    {
        auto curPoint = queue.top();
        queue.pop();
        auto from = curPoint.Id;
        auto curCost = curPoint.Cost;
        auto curDist = curPoint.Dist;

        if (from == numAirports - 1)
            return true;

        if (minDist[from][curCost] < curDist)
            continue;

        for (auto [to, cost, dist] : airports[from])
        {
            if (curCost + cost > money)
                continue;

            if (minDist[to][curCost + cost] > minDist[from][curCost] + dist)
            {
                queue.emplace(Point{to, curCost + cost, curDist + dist});
                for (int i = curCost + cost; i <= money; ++i)
                {
                    if (minDist[to][i] > curDist + dist)
                        minDist[to][i] = curDist + dist;
                    else
                        break;
                }
            }
        }
    }
    return false;
}

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    int testCases;
    std::cin >> testCases;

    for (int testIdx = 0; testIdx < testCases; ++testIdx)
    {
        std::cin >> numAirports >> money >> numTickets;
        std::vector<std::deque<std::tuple<int, int, int>>> airports(numAirports);

        for (int i = 0; i < numTickets; ++i)
        {
            int from, to, cost, time;
            std::cin >> from >> to >> cost >> time;
            airports[from - 1].emplace_back(std::make_tuple(to - 1, cost, time));
        }

        for (int i = 0; i < numAirports; ++i)
        {
            for (int j = 0; j <= money; ++j)
            {
                minDist[i][j] = std::numeric_limits<int>::max();
            }
        }

        if (dijkstra(airports))
        {
            std::cout << minDist[numAirports - 1][money] << "\n";
        }
        else
        {
            std::cout << "Poor KCM\n";
        }
    }
    return 0;
}
