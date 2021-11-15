#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;
constexpr ull MAX = 1e9 + 7;

vector<ull> integer_divisors(ull n) {
    vector<ull> divisors;

    ull squareRoot = ceil(sqrt(n));  // Just to avoid repeatead heavy calculations
    for (ull i = 1; i < squareRoot; i++) {
        if (n % i == 0) {
            divisors.push_back(i % MAX);
            divisors.push_back((n / i) % MAX);
        }
    }
    // Special case where the square root is an integer
    if (squareRoot * squareRoot == n)
        divisors.push_back(squareRoot % MAX);

    // Sorting just in case
    sort(divisors.begin(), divisors.end());

    return divisors;
}

int main() {
    ull number;
    cin >> number;

    vector<ull> divisors = integer_divisors(number);

    // Iterating through the divisors and calculating the sum and products (mod 10e9 + 7)
    ull sum = 0;
    ull product = 1;
    for (const auto& divisor : divisors) {
        sum = (sum + divisor) % MAX;
        product = (product * divisor) % MAX;
    }
    cout << divisors.size() << " " << sum << " " << product << '\n';

    return 0;
}