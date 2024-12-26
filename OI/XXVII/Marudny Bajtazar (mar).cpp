#include <bits/stdc++.h>
using namespace std;

int findShortestMissingSubstring(const vector<int>& substringCount, int maxLen) {
    for (int len = 1; len <= maxLen; ++len) {
        int totalSubstrings = 1 << len; // 2^len
        if (substringCount[len] < totalSubstrings) {
            return len;
        }
    }
    return maxLen + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    string chain;
    cin >> chain;
    vector<int> changes(M);
    for (int i = 0; i < M; ++i) {
        cin >> changes[i];
        changes[i]--;
    }

    int maxLen = static_cast<int>(log2(N)) + 1;
    vector<int> substringCount(maxLen + 1, 0);
    unordered_map<string, int> substringFreq;

    for (int len = 1; len <= maxLen; ++len) {
        for (int i = 0; i <= N - len; ++i) {
            string sub = chain.substr(i, len);
            if (substringFreq[sub]++ == 0) {
                substringCount[len]++;
            }
        }
    }

    cout << findShortestMissingSubstring(substringCount, maxLen) << endl;

    for (int i = 0; i < M; ++i) {
        int pos = changes[i];

        for (int len = 1; len <= maxLen; ++len) {
            for (int j = max(0, pos - len + 1); j <= min(N - len, pos); ++j) {
                string oldSubstring = chain.substr(j, len);
                if (--substringFreq[oldSubstring] == 0) {
                    substringCount[len]--;
                }
            }
        }

        chain[pos] = (chain[pos] == '0') ? '1' : '0';

        for (int len = 1; len <= maxLen; ++len) {
            for (int j = max(0, pos - len + 1); j <= min(N - len, pos); ++j) {
                string newSubstring = chain.substr(j, len);
                if (substringFreq[newSubstring]++ == 0) {
                    substringCount[len]++;
                }
            }
        }

        cout << findShortestMissingSubstring(substringCount, maxLen) << endl;
    }

    return 0;
}
