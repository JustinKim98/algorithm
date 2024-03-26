#include <iostream>
#define MAX 20000

int status[3][3];
int boardStatus[MAX]; // Stores state of the board (win : 1, lose : -1, draw = 0)

int isWin(int turn)
{
    if (status[0][0] == status[1][1] && status[1][1] == status[2][2] && status[1][1] > 0)
        return status[1][1];
    if (status[2][0] == status[1][1] && status[1][1] == status[0][2] && status[1][1] > 0)
        return status[1][1];

    if (status[0][0] == status[0][1] && status[0][1] == status[0][2] && status[0][1] > 0)
        return status[0][1];
    if (status[1][0] == status[1][1] && status[1][1] == status[1][2] && status[1][1] > 0)
        return status[1][1];
    if (status[2][0] == status[2][1] && status[2][1] == status[2][2] && status[2][1] > 0)
        return status[2][1];

    if (status[0][0] == status[1][0] && status[1][0] == status[2][0] && status[1][0] > 0)
        return status[1][0];
    if (status[0][1] == status[1][1] && status[1][1] == status[2][1] && status[1][1] > 0)
        return status[1][1];
    if (status[0][2] == status[1][2] && status[1][2] == status[2][2] && status[1][2] > 0)
        return status[1][2];

    return 0; // Draw
}

bool isFilled()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            if (status[i][j] == 0)
                return false;
        }

    return true;
}

int encodeBoard()
{
    int code = 0;
    int encodeIdx = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            code += encodeIdx * status[i][j];
            encodeIdx *= 3;
        }

    return code;
}

int tryToWin(int curr)
{
    int code = encodeBoard();

    if (boardStatus[code] > -2)
        return boardStatus[code];
    // std::cout << " cur turn : " << curr << std::endl;
    int winner = isWin(curr);
    if (winner == curr)
    {
        boardStatus[code] = 1;
        return 1;
    }

    if (winner == 3 - curr)
    {
        boardStatus[code] = -1;
        return -1;
    }

    if (isFilled())
    {
        boardStatus[code] = 0;
        return 0;
    }

    int best = -1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            if (status[i][j] == 0)
            {
                status[i][j] = curr;
                best = std::max(best, -tryToWin(3 - curr));
                status[i][j] = 0; // revert the status
            }
        }

    return best;
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    int xs = 0; // 1
    int os = 0; // 2
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            int num;
            std::cin >> num;
            status[i][j] = num;
            if (status[i][j] == 1)
                xs += 1;
            if (status[i][j] == 2)
                os += 1;
        }

    int turn = 0;
    if (xs == os)
        turn = 1;
    else
        turn = 2;

    for (int i = 0; i < MAX; ++i)
        boardStatus[i] = -100;

    int win = tryToWin(turn);
    if (win == -1)
        std::cout << "L";
    if (win == 1)
        std::cout << "W";
    if (win == 0)
        std::cout << "D";

    return 0;
}
