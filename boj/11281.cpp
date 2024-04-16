#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_set>

bool done[20001];
int minCnt[20001];
int sccId[200001];
int cnt = 0;
int sccNum = 0;
int numVars, numTokens;

std::deque<int> stack;
// id = given + 10000;
std::unordered_map<int, std::unordered_set<int>> graph;
std::unordered_set<int> ids;

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
        while (true)
        {
            auto poppedId = stack.back();
            stack.pop_back();
            sccId[poppedId] = sccNum;
            done[poppedId] = true;
            if (poppedId == id)
                break;
        }
        sccNum += 1;
    }

    return childMin;
}

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> numVars >> numTokens;

    for (int i = 0; i < numTokens; ++i)
    {
        int from, to;
        std::cin >> from >> to;
        graph[getStoreId(-from)].emplace(getStoreId(to));
        graph[getStoreId(-to)].emplace(getStoreId(from));
    }

    for (int i = 0; i <= 20000; ++i)
    {
        done[i] = false;
        minCnt[i] = 0;
    }

    for (int i = 1; i <= numVars; ++i)
    {
        if (!done[getStoreId(i)])
            tarjan(getStoreId(i));
        if (!done[getStoreId(-i)])
            tarjan(getStoreId(-i));
    }

    for (int id = 1; id <= numVars; ++id)
    {
        if (sccId[getStoreId(id)] == sccId[getStoreId(-id)])
        {
            std::cout << 0 << "\n";
            return 0;
        }
    }

    std::cout << 1 << "\n";

    std::vector<std::pair<int, int>> order;
    order.reserve(2 * numVars);
    for (int i = 1; i <= numVars; ++i)
    {
        order.emplace_back(sccId[getStoreId(i)], i);
        order.emplace_back(sccId[getStoreId(-i)], -i);
    }

    std::sort(order.begin(), order.end(), std::greater<>());

    std::vector<int> ans(200001, -1);
    for (auto [sccId, varId] : order)
    {
        if (ans[getStoreId(varId)] == -1)
        {
            ans[getStoreId(varId)] = 0;
            ans[getStoreId(-varId)] = 1;
        }
    }

    for (int varId = 1; varId <= numVars; ++varId)
    {
        std::cout << ans[getStoreId(varId)] << " ";
    }
    std::cout << "\n";

    return 0;
}
