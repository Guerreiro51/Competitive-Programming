#include <bits/stdc++.h>

using namespace std;

class Trie {
 private:
    int numberOfOccurrences;
    array<Trie*, 26> subTries;

 public:
    Trie() : numberOfOccurrences(0), subTries() {}

    void AddWord(const string& word) {
        Trie* curTrie = this;
        for(size_t i = 0; i < word.size(); i++, curTrie->numberOfOccurrences++) {
            if(curTrie->subTries[word[i]-'a'] == nullptr)
                curTrie->subTries[word[i]-'a'] = new Trie();
            curTrie = curTrie->subTries[word[i]-'a'];
        }
    }

    int search(const string& word) {
        Trie* curTrie = this;
        for(size_t i = 0; i < word.size(); i++) {
            if(curTrie->subTries[word[i]-'a'] == nullptr)
                return 0;
            curTrie = curTrie->subTries[word[i]-'a'];
        }
        return curTrie->numberOfOccurrences;
    }

    ~Trie() {
        for(size_t i = 0; i < subTries.size(); i++)
            delete subTries[i];
    }
};

int main() {
    size_t numberOfWords, numberOfQueries;
    cin >> numberOfWords >> numberOfQueries;

    Trie todoList;
    while(numberOfWords--) {
        string task;
        cin >> task;
        todoList.AddWord(task);
    }

    while(numberOfQueries--) {
        string query;
        cin >> query;
        cout << todoList.search(query) << '\n';
    }
}