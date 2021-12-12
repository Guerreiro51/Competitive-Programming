#include <bits/stdc++.h>

using namespace std;

// Given that the bitwise xor with all the numbers in the array is not zero (game isn't over),
// you can prove by induction that just the parity of the number of piles matter.
bool solve(const vector<int>& numbers) {
    int numbersXor = 0;
    for (const auto& number : numbers)
        numbersXor = numbersXor ^ number;

    if (!numbersXor)
        return true;
    return !(numbers.size() % 2);
}

int main() {
    size_t numberOfTestCases;
    cin >> numberOfTestCases;

    while (numberOfTestCases--) {
        size_t numberOfPiles;
        cin >> numberOfPiles;

        vector<int> piles(numberOfPiles);
        for (auto& pile : piles)
            cin >> pile;

        if (solve(piles))
            cout << "First\n";
        else
            cout << "Second\n";
    }
}