#include <bits/stdc++.h>

using namespace std;

// Generates all possibles combinations of size combination.size() and store them in the sums array.
void generateCombination(const vector<int>& numbers, vector<int>& combination, size_t numbersIndex, size_t combinationIndex, int sumTotal, vector<vector<int>>& sums) {
    if (combinationIndex == combination.size()) {                               // combination vector is filled
        if (accumulate(combination.begin(), combination.end(), 0) == sumTotal)  // check if it matches the desired total
            sums.push_back(combination);
        return;
    }

    // create combinations with every number if there are sufficient numbers
    for (size_t i = numbersIndex + 1; (i <= numbers.size()) && ((numbers.size() - i + 1) >= (combination.size() - combinationIndex)); i++) {
        combination[combinationIndex] = numbers[i - 1];
        generateCombination(numbers, combination, i, combinationIndex + 1, sumTotal, sums);

        // skip repeated numbers
        while (i < numbers.size() && numbers[i - 1] == numbers[i])
            i++;
    }
}

bool CompareVector(const vector<int>& a, const vector<int>& b) {
    for (size_t i = 0; i < min(a.size(), b.size()); i++)
        if (a[i] != b[i]) return a[i] > b[i];  // greater number comes first
    return a.size() < b.size();                // equal vectors (maybe with + 0's at the end)
}

int main() {
    while (true) {
        int sumTotal;
        size_t numberOfNumbers;
        cin >> sumTotal >> numberOfNumbers;

        if (numberOfNumbers == 0)
            break;

        vector<int> numbers(numberOfNumbers);
        for (auto& number : numbers)
            cin >> number;

        vector<vector<int>> sums;
        for (size_t combinationSize = 1; combinationSize <= numberOfNumbers; combinationSize++) {
            vector<int> combination(combinationSize);
            generateCombination(numbers, combination, 0UL, 0UL, sumTotal, sums);
        }

        cout << "Sums of " << sumTotal << ":\n";
        if (!sums.empty()) {
            sort(sums.begin(), sums.end(), CompareVector);
            for (const auto& sum : sums) {
                for (size_t i = 0; i < sum.size() - 1; i++)
                    cout << sum[i] << "+";
                cout << sum.back() << '\n';
            }
        } else
            cout << "NONE\n";
    }

    return 0;
}