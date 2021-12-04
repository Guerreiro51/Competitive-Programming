#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

ull numberOfDivisors(ull number) {
    ull divisorsCount = 0;
    ull sqrtNumber = sqrt(number);
    for (ull i = 1; i <= sqrtNumber; i++)
        if (number % i == 0)
            divisorsCount += 2; // i and number/i

    // Avoids repeated counting when the sqrt is a divisor
    if (sqrtNumber * sqrtNumber == number)
        divisorsCount--;

    return divisorsCount;
}

ull numberOfCommonDivisors(vector<ull> elements) {
    // We can simplify this problem by calculating the GCD of the elements of the array
    // and counting its divisors

    ull arrayGCD = elements[0];
    for (const auto& element : elements)
        arrayGCD = gcd(arrayGCD, element);

    return numberOfDivisors(arrayGCD);
}

int main() {
    size_t numberOfElements;
    cin >> numberOfElements;

    vector<ull> elements(numberOfElements);
    for (auto& element : elements)
        cin >> element;

    cout << numberOfCommonDivisors(elements) << '\n';
}