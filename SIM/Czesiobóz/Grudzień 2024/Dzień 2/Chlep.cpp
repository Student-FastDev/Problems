#include <bits/stdc++.h>

using namespace std;

const long long INF = LLONG_MAX;
const long long barrierNumber = 69 * 1e17;

vector<vector<long long>> combinationMemo;

long long combination(int N, int K) {
    if (K > N) return 0;
    if (K == 0 || K == N) return 1;
    if (combinationMemo[N][K] != -1) return combinationMemo[N][K];
    
    long long result;
    if (combination(N - 1, K - 1) > barrierNumber - combination(N - 1, K)) {
        result = INF;
    }
    else {
        result = combination(N - 1, K - 1) + combination(N - 1, K);
    }
    
    return combinationMemo[N][K] = result;
}

long long countPermutations(const map<char, int>& frequencyTable, int N) {
    long long denominator = 1;
    for (const auto& [key, count] : frequencyTable) {
        if(combination(N, count) > barrierNumber / denominator) {
            return INF;
        }
        denominator *= combination(N, count);
        N -= count;
    }
    return denominator;
}

string findKthAnagram(string S, long long K) {
    map<char, int> frequencyTable;
    for (char C : S) {
        frequencyTable[C]++;
    }

    int N = static_cast<int>(S.size());
    long long totalPermutations = countPermutations(frequencyTable, N);
    
    if (K > totalPermutations) {
        return "-1";
    }

    string result;

    while (N > 0) {
        for (auto it = frequencyTable.begin(); it != frequencyTable.end(); ++it) {
            char C = it->first;
            if (it->second > 0) {
                frequencyTable[C]--;
                long long numPermutations = countPermutations(frequencyTable, N - 1);

                if (K <= numPermutations) {
                    result.push_back(C);
                    break;
                } else {
                    K -= numPermutations;
                    frequencyTable[C]++;
                }
            }
        }
        N--;
    }

    return result;
}

int main() {
    int maxN = 100;
    combinationMemo.assign(maxN + 1, vector<long long>(maxN + 1, -1));

    string S;
    long long a;

    cin >> S >> a;
    long long K = a;

    string result = findKthAnagram(S, K);

    if (result == "-1") {
        cout << "NIE" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
