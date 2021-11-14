#include <bits/stdc++.h>

using namespace std;

bool solve(string& guessedWord, string& typedWord) {
    size_t guessed = 0, typed = 0;

    while (guessed < guessedWord.size()) {
        char currentGuessed = guessedWord[guessed];
        char currentTyped = typedWord[typed];
        if (currentTyped != currentGuessed) return false;
        size_t countGuessed = 0;
        size_t countTyped = 0;

        while (guessedWord[guessed] == currentGuessed) {
            countGuessed++;
            guessed++;
        }
        while (typedWord[typed] == currentTyped) {
            countTyped++;
            typed++;
        }
        if (countGuessed > countTyped) return false;
    }
    return typed == typedWord.size();
}
int main() {
    size_t numberOfPairs;
    cin >> numberOfPairs;

    while (numberOfPairs--) {
        string guessedWord, typedWord;
        cin >> guessedWord >> typedWord;

        if (solve(guessedWord, typedWord))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}