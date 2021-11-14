#include <bits/stdc++.h>

using namespace std;

constexpr size_t BASE = 10;

int main() {
    size_t numberLength;
    cin >> numberLength;

    vector<int> number(numberLength);
    for (auto& digit : number) {
        char cDigit;
        cin >> cDigit;
        digit = cDigit - '0';
    }

    // A transform table
    int transform[BASE];
    transform[0] = 0;
    for (size_t i = 1; i < BASE; i++)
        cin >> transform[i];

    // Transforming if, and only if, the transformed number is bigger than the input number
    for (size_t i = 0; i < numberLength; i++)
        if (number[i] < transform[number[i]])
            number[i] = transform[number[i]];

    for (const auto& digit : number)
        cout << digit;

    return 0;
}