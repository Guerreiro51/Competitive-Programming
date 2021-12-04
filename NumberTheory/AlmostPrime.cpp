#include <bits/stdc++.h>

using namespace std;
using ul = unsigned long;

constexpr size_t MAX_P = 3000 + 1;

vector<unsigned long> SieveOfEratosthenes() {
    bitset<MAX_P> sieve;
    sieve.set();
    sieve[0] = sieve[1] = false;
    vector<ul> primes;

    for (size_t p = 2; p < MAX_P; p++) {
        if (sieve[p]) {  // if p is prime
            primes.push_back(p);

            // then all multiples of p aren't prime
            for (size_t i = p * p; i <= MAX_P; i += p)  // here, we can actually start looking from p squared as smaller numbers will already be marked
                sieve[i] = false;
        }
    }
    return primes;
}

ul numberOfAlmostPrimes(size_t n, vector<ul> primes) {
    size_t numberOfAlmostPrime = 0;
    for (size_t curNum = 6; curNum <= n; curNum++) {
        size_t numberOfPrimeDivisors = 0;
        for (size_t primeIndex = 0; primes[primeIndex] <= curNum && primeIndex < primes.size(); primeIndex++) {
            if (curNum % primes[primeIndex] == 0)
                numberOfPrimeDivisors++;
        }
        if (numberOfPrimeDivisors == 2)
            numberOfAlmostPrime++;
    }
    return numberOfAlmostPrime;
}

int main() {
    size_t checkUpTo;
    cin >> checkUpTo;

    vector<ul> primes = SieveOfEratosthenes();
    cout << numberOfAlmostPrimes(checkUpTo, primes) << '\n';
}