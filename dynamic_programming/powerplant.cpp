// #include <iostream>
// #define INF 999999999
// int cache[1 << 16];
// int adj[16][16];
// int numPlants;
// int minOn;

// int turnOn(int state, int idx) { return state | (1 << idx); }

// int numTurnedOn(int state) {
//   int cnt = 0;
//   for (int i = 0; i < 16; ++i) {
//     if ((state >> i) & 0x01)
//       cnt += 1;
//   }
//   return cnt;
// }

// bool isOn(int state, int idx) { return state >> idx; }

// int minCost(int state) {
//   if (numTurnedOn(state) >= minOn)
//     return 0;

//   int minimum = INF;
//   int minState = 0;
//   for (int i = 0; i < numPlants; ++i)
//     if (isOn(state, i)) {
//       for (int j = 0; j < numPlants; ++j) {
//         if (!isOn(state, j)) {
//           if (minimum > adj[i][j]) {
//             minimum = adj[i][j];
//             minState = turnOn(state, j);
//           }
//         }
//       }
//     }

//   return minimum + minCost(minState);
// }

// int main() {

// std::cin>>numPlants;
// for(int i = 0; i < numPlants; ++i)
//     for(int j = 0; j < numPlants; ++j)
//     {
//         std::cin>>a[i][j];
//     }

// int initialState = 0;
// for(int i =0; i < numPlants; ++i)
// {
//     std::string

// }

// }

#include <cstdint>
#include <iostream>

#define INF 9999999
int N;
int cache[1 << 16];
int map[16][16];

/// Get minimum cost to turn on powerplant 'n'
int minCostToTurnOn(std::uint16_t state, int n)
{
  int min = INF;
  for (int i = 0; i < N; ++i)
    // If powerplant is connected, and powerplant 'i' is turned on
    if (min > map[i][n] && (state & (1 << i)))
    {
      min = map[i][n];
    }
  return min;
}

int numTurnedOn(std::uint16_t state)
{
  int cnt = 0;
  for (int i = 0; i < N; ++i)
  {
    if (state & (1 << i))
      cnt++;
  }
  // std::cout << "turned on " << cnt << std::endl;
  return cnt;
}

// define state[i] to be minimum cost to turn the powerplant on to N - n;
int getMinCost(std::uint16_t state, int minOn)
{
  /// powerplants off
  if (cache[state] >= 0)
    return cache[state];

  /// Already, enough number of powerplants are on
  if (numTurnedOn(state) >= minOn)
  {
    cache[state] = 0;
    return 0;
  }

  int min = INF;
  for (int i = 0; i < N; ++i)
  {
    // If powerplant was off
    if (!(state & (1 << i)))
    {
      auto curMin = minCostToTurnOn(state, i);
      auto minCost = getMinCost(state | (1 << i), minOn);
      if (min > curMin + minCost)
        min = curMin + minCost;
    }
  }
  cache[state] = min;
  return min;
}

int main()
{
  std::cin.tie(0);
  std::ios::sync_with_stdio(false);

  std::cin >> N;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      std::cin >> map[i][j];

  char isOn[16 + 1];
  std::cin >> isOn;
  std::uint16_t initialState = 0;
  for (int i = 0; i < N; ++i)
  {
    if (isOn[i] == 'Y')
      initialState |= (1 << i);
  }

  int minOn;
  std::cin >> minOn;

  for (int i = 0; i < (1 << 16); ++i)
    cache[i] = -1;

  auto minCost = getMinCost(initialState, minOn);
  if (minCost == INF)
    std::cout << -1 << std::endl;
  else
    std::cout << minCost << std::endl;

  return 0;
}