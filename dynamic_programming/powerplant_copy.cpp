#include <iostream>
#include <string>
#include <cstring>

#define endl "\n"
#define MAX 16
#define INF 987654321
using namespace std;

int N, P, Answer = INF;
int MAP[MAX][MAX];
int Cost[1 << MAX];
string S;

int Min(int A, int B)
{
    if (A < B)
        return A;
    return B;
}

void Input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }
    cin >> S;
    cin >> P;
}

int Bit_Count(int B)
{
    int Cnt = 0;
    while (B != 0)
    {
        Cnt = Cnt + (B & 1);
        B = B >> 1;
    }
    return Cnt;
}

int DFS(int State)
{
    if (Bit_Count(State) >= P)
        return 0;
    if (Cost[State] != -1)
        return Cost[State];

    Cost[State] = INF;
    for (int i = 0; i < N; i++)
    {
        if ((State & (1 << i)) == 0)
            continue;
        for (int j = 0; j < N; j++)
        {
            if ((State & (1 << j)) == 0)
            {
                int Next_State = State | (1 << j);
                Cost[State] = Min(Cost[State], MAP[i][j] + DFS(Next_State));
            }
        }
    }
    return Cost[State];
}

void Solution()
{
    int Bit_State = 0;
    for (int i = 0; i < S.length(); i++)
    {
        if (S[i] == 'Y')
            Bit_State = Bit_State | (1 << i);
    }

    memset(Cost, -1, sizeof(Cost));
    Answer = DFS(Bit_State);

    if (Answer == INF)
        cout << -1 << endl;
    else
        cout << Answer << endl;
}

void Solve()
{
    Input();
    Solution();
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // freopen("Input.txt", "r", stdin);
    Solve();

    return 0;
}
