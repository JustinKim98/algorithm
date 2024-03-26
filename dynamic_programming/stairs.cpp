#include <map>
#include <iostream>
#include <tuple>
#include <cstdint>

const std::uint64_t divide = 1000000000;
std::map<std::tuple<std::uint16_t, int, int>, std::uint64_t> map;

std::uint64_t cases(std::uint16_t requiredDigits, int start, int numDigits)
{
    // std::cout << "digits : " << numDigits << start << std::endl;
    const auto key = std::make_tuple(requiredDigits, start, numDigits);
    if (map.find(key) != map.end())
        return map[key];

    /// no more required digits, and this is the last digit
    if (numDigits == 0 && requiredDigits == 0)
    {
        map[key] = 1;
        return 1;
    }

    /// There are digits left, but we have only one digit left (required digits does not contain start digit)
    if (numDigits == 0 && requiredDigits > 0)
    {
        map[key] = 0;
        return 0;
    }

    std::uint64_t totalCases = 0;
    if (start > 0)
    {
        totalCases += cases(requiredDigits & (~(1 << (start - 1))), start - 1, numDigits - 1);
    }
    if (start < 9)
    {
        totalCases += cases(requiredDigits & (~(1 << (start + 1))), start + 1, numDigits - 1);
    }

    map[key] = totalCases % divide;
    return totalCases % divide;
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::uint64_t totalCases = 0;
    std::int16_t requiredDigits = 0b0000001111111111;
    for (int nextDigit = 1; nextDigit < 10; ++nextDigit)
        totalCases += cases(requiredDigits & (~(1 << nextDigit)), nextDigit, N - 1);

    std::cout << totalCases % divide << std::endl;

    return 0;
}