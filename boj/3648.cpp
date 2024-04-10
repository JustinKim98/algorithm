#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_set>

bool done[20001];
int minCnt[20001];
int sccId[200001];
int cnt = 0;
int numVars, numTokens;

std::deque<int> stack;
std::deque<std::unordered_set<int>> sccs;
// id = given + 10000;
std::unordered_map<int, std::unordered_set<int>> graph;

inline int getOriginId(int id)
{
    return id - 10000;
}

inline int getStoreId(int id)
{
    return id + 10000;
}

inline bool negative(int id)
{
    return id < 10000;
}

bool getNegativeStoreId(int id)
{
    return getStoreId(-getOriginId(id));
}

inline int getVarId(int id)
{
    return std::abs(getOriginId(id));
}

int tarjan(int id)
{
    cnt += 1;
    const int curCnt = cnt;
    minCnt[id] = curCnt;
    int childMin = minCnt[id];
    stack.emplace_back(id);

    for (auto childId : graph[id])
    {
        if (done[childId])
            continue;

        if (minCnt[childId] > 0)
        {
            childMin = std::min(childMin, minCnt[childId]);
        }
        else
        {
            childMin = std::min(childMin, tarjan(childId));
        }
    }

    if (childMin == curCnt)
    {
        std::unordered_set<int> scc;
        while (true)
        {
            auto poppedId = stack.back();
            stack.pop_back();
            scc.emplace(poppedId);
            sccId[poppedId] = sccs.size();
            done[poppedId] = true;
            if (poppedId == id)
                break;
        }
        sccs.emplace_back(scc);
    }

    return childMin;
}

bool hasSolution()
{
    for (const auto &scc : sccs)
    {
        for (auto id : scc)
        {
            if (negative(id) && scc.find(getStoreId(-getOriginId(id))) != scc.end())
                return false;
        }
    }
    return true;
}

int ans[200001];

bool isPossible(int curId)
{
    const auto curSccId = sccId[curId];
    const auto &curScc = sccs[sccId[curId]];
    for (const auto id : curScc)
    {
        if (ans[id] == 0 || ans[getNegativeStoreId(id)] == 1)
            return false;

        ans[id] = 1;
        ans[getNegativeStoreId(id)] = 0;
    }

    for (const auto id : curScc)
    {
        for (auto next : graph[id])
        {
            if (sccId[next] != curSccId && !isPossible(next))
                return false;
        }
    }

    return true;
}

int main()
{
    while (std::cin >> numVars >> numTokens)
    {
        graph.clear();
        sccs.clear();
        stack.clear();
        for (int i = 0; i < numTokens; ++i)
        {
            int from, to;
            std::cin >> from >> to;
            graph[getStoreId(-from)].emplace(getStoreId(to));
            graph[getStoreId(-to)].emplace(getStoreId(from));
        }
        graph[getStoreId(-1)].emplace(getStoreId(1));

        for (int i = 0; i <= 20000; ++i)
        {
            done[i] = false;
            minCnt[i] = 0;
            ans[i] = -1;
        }

        for (int i = 1; i <= numVars; ++i)
        {
            if (!done[getStoreId(i)])
                tarjan(getStoreId(i));
            if (!done[getStoreId(-i)])
                tarjan(getStoreId(-i));
        }

        if (hasSolution())
            std::cout << "yes\n";
        else
            std::cout << "no\n";
    }

    return 0;
}
