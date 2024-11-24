#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

long long computeHash(const string& word, int P, int M) {
    long long hashValue = 0;
    for (char c : word) {
        hashValue = (hashValue * P + (c - 'a' + 1)) % M;
    }
    return hashValue;
}

string generateRandomWord(int N) {
    string word;
    for (int i = 0; i < N; i++) {
        word += (char)('a' + rand() % 26);
    }
    return word;
}

int main() {
    int P, M;
    cin >> P >> M;

    const int N = 25;
    unordered_map<long long, string> hashMap;

    srand(time(0));

    while (true) {
        string word = generateRandomWord(N);

        long long hashValue = computeHash(word, P, M);

        if (hashMap.find(hashValue) != hashMap.end()) {
            cout << N << endl;
            cout << hashMap[hashValue] << endl;
            cout << word << endl;
            break;
        }

        hashMap[hashValue] = word;
    }

    return 0;
}
