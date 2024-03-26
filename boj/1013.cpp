#include <iostream>
#include <string>
#include <optional>
#include <vector>

std::optional<int> parse100(const std::string &str, int idx)
{
    if (str[idx] != '1' || str[idx + 1] != '0' || str[idx + 2] != '0')
        return std::nullopt;

    idx += 3;
    while (idx < str.size() && str[idx] == '0')
        idx += 1;

    return idx;
}

std::optional<int> parse1(const std::string &str, int idx)
{
    if (str[idx] != '1')
    {
        return std::nullopt;
    }

    if (auto newIdx = parse100(str, idx))
    {
        idx = newIdx.value();
    }
    else
    {
        return std::nullopt;
    }

    if (str[idx] != '1')
        return std::nullopt;
    idx += 1;

    while (idx < str.size() && str[idx] == '1')
    {
        if (auto newIdx = parse100(str, idx))
        {
            idx = newIdx.value();
            if (str[idx] != '1')
                return std::nullopt;
            idx += 1;
        }
        else
        {
            idx += 1;
        }
    }

    return idx;
}

std::optional<int> parse01(const std::string &str, int idx)
{
    if (idx + 1 >= str.size())
        return std::nullopt;

    if (str[idx] != '0' || str[idx + 1] != '1')
        return std::nullopt;

    return idx + 2;
}

bool test(const std::string &str)
{
    int idx = 0;
    bool success = true;
    while (idx < str.size())
    {
        if (auto newIdx = parse1(str, idx))
        {
            idx = newIdx.value();
        }
        else if (auto newIdx = parse01(str, idx))
        {
            idx = newIdx.value();
        }
        else
        {
            success = false;
            break;
        }
    }

    return success;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<bool> vect(n);
    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;

        vect[i] = test(str);
    }

    for (auto elem : vect)
    {
        if (elem)
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }

    return 0;
}