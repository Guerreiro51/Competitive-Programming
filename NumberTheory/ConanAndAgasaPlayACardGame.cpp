#include <bits/stdc++.h>

using namespace std;

bool existOddFrequencyNumber(const vector<int>& numbers) {
    unordered_map<int, int> frequency;

    for (const auto& number : numbers)
        frequency[number]++;

    for (const auto& number : frequency)
        if (number.second % 2)
            return true;
    return false;
}

int main() {
    size_t numberOfCards;
    cin >> numberOfCards;

    vector<int> cards(numberOfCards);
    for (auto& card : cards)
        cin >> card;

    // In this game, we're in a winning state if there is a card with odd frequency
    // That happens because you can always pick the biggest odd frequency card leaving
    // every card with an even frequency. After that, you just keep picking the same
    // card as your opponent and you'll eventually win.
    if (existOddFrequencyNumber(cards))
        cout << "Conan\n";
    else
        cout << "Agasa\n";
}