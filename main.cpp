#include <iostream>

// Function to return gcd of a and b
int gcd(int a, int b)
{
    // Find Minimum of a and b
    int result = std::min(a, b);
    while (result > 0) {
        if (a % result == 0 && b % result == 0) {
            break;
        }
        result--;
    }

    // Return gcd of a and b
    return result;
}

// Driver code
int main()
{
    int a = 98, b = 56;
    std::cout << "GCD of " << a << " and " << b << " is "
         << gcd(a, b);
    return 0;
}
