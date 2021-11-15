#include <bits/stdc++.h>

constexpr size_t MAX = 1e6;

using namespace std;

template <size_t MAX_P>
constexpr bitset<MAX_P> SieveOfEratosthenes() {
    bitset<MAX_P> primes;
    primes.set();
    primes[0] = primes[1] = false;

    // for all p up to sqrt(MAX) (using p squared to avoid calculating a square root)
    for (size_t p = 2; p * p <= MAX_P; p++) {
        if (primes[p] == true)  // if p is prime
            // then all multiples of p aren't prime
            for (size_t i = p * p; i <= MAX_P; i += p)  // here, we can actually start looking from p squared as smaller numbers will already be marked
                primes[i] = false;
    }
    return primes;
}

int main() {
    size_t arraySize;
    cin >> arraySize;

    vector<int> numbers(arraySize);
    for (auto& number : numbers)
        cin >> number;

    // Generate primes up to MAX
    bitset<MAX> primes = SieveOfEratosthenes<MAX>();

    // for every pair of numbers, check if their gcd is prime
    size_t numberOfHits = 0;
    for (size_t i = 0; i < numbers.size(); i++) {
        for (size_t j = i + 1; j < numbers.size(); j++) {   
            auto greatestCommonDivisor = gcd(numbers[i], numbers[j]);
            if (primes[greatestCommonDivisor])
                numberOfHits++;
        }
    }
    cout << numberOfHits << '\n';

    return 0;
}