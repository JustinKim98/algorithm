#include <vector>
#include <iostream>
#define MAX_CASES 1000000000000000000
#define MOD 1000000007

using Mat = std::vector<std::vector<std::uint64_t>>;
// Transition matrix for states
Mat baseMatrix{{0, 1, 0, 0}, {1, 0, 2, 0}, {0, 1, 0, 1}, {0, 0, 1, 0}};

Mat matMul(const Mat &a, const Mat &b)
{
    Mat c = std::vector<std::vector<std::uint64_t>>(4, std::vector<std::uint64_t>(4, 0));

    for (int m = 0; m < 4; ++m)
        for (int n = 0; n < 4; ++n)
        {
            int sum = 0;
            for (int k = 0; k < 4; ++k)
                sum += (a[m][k] * b[k][n]) % MOD;
            c[m][n] = sum;
        }

    return c;
}

// Calculate matrix multilication in log(n)
Mat multiplySequence(std::uint64_t times)
{
    if (times == 1)
    {
        return baseMatrix;
    }

    std::uint64_t curNum = 2;
    Mat curMatrix = baseMatrix;
    while (curNum < times)
    {
        curMatrix = matMul(curMatrix, curMatrix);
        curNum *= 2;
    }
    curNum /= 2;

    if (times - curNum > 0)
    {
        curMatrix = matMul(curMatrix, multiplySequence(times - curNum));
    }

    return curMatrix;
}

int main()
{
    std::uint64_t size = 0;
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::cin >> size;

    if (size == 0)
    {
        std::cout << 0 << "\n";
        return 0;
    }
    if (size == 1)
    {
        std::cout << 0 << "\n";
        return 0;
    }

    std::vector<std::uint64_t> baseVect{0, 2, 0, 1};

    Mat mat = multiplySequence(size - 1);

    std::uint64_t res = 0;
    for (int n = 0; n < 4; ++n)
    {
        res += mat[2][n] * baseVect[n];
    }
    std::cout << res % MOD << std::endl;
}
