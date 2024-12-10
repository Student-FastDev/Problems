#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

int calculateMinScore(const vector<string>& answers, const string& key) {
    int minScore = INT_MAX;
    for (const string& ans : answers) {
        int score = 0;
        for (size_t i = 0; i < key.size(); ++i) {
            if (ans[i] == key[i]) {
                ++score;
            }
        }
        minScore = min(minScore, score);
    }
    return minScore;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<string> answers(N);
    for (int i = 0; i < N; ++i) {
        cin >> answers[i];
    }
    
    int bestMinScore = 0;
    string bestKey(M, 'P');
    
    for (int mask = 0; mask < (1 << M); ++mask) {
        string key(M, 'P');
        for (int j = 0; j < M; ++j) {
            if (mask & (1 << j)) {
                key[j] = 'F';
            }
        }
        
        int minScore = calculateMinScore(answers, key);
        
        if (minScore > bestMinScore || (minScore == bestMinScore && key < bestKey)) {
            bestMinScore = minScore;
            bestKey = key;
        }
    }
    
    cout << bestKey << endl;
    cout << bestMinScore << endl;
    return 0;
}
