#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int findMaxSubstring(const string& S, int startIdx) {
    int N = S.size();
    int countS = 0, countB = -1, countC = -2;
    int maxLength = 0;

    for (int i = startIdx; i < N; i++) {
        if (S[i] == 'S')
            countS++;
        if (S[i] == 'B') {
            if (countB == -1)
                countB = 1;
            else
                countB++;
        }
        if (S[i] == 'C') {
            if (countC == -2)
                countC = 1;
            else
                countC++;
        }

        if (countS != countB && countB != countC && countS != countC)
            maxLength = i - startIdx + 1;
    }

    return maxLength;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    string S;
    cin >> N >> S;

    int maxSubstringLength = 0;

    maxSubstringLength = max(maxSubstringLength, findMaxSubstring(S, 0));
    maxSubstringLength = max(maxSubstringLength, findMaxSubstring(S, 1));
    maxSubstringLength = max(maxSubstringLength, findMaxSubstring(S, 2));
    
    reverse(S.begin(), S.end());

    maxSubstringLength = max(maxSubstringLength, findMaxSubstring(S, 0));
    maxSubstringLength = max(maxSubstringLength, findMaxSubstring(S, 1));
    maxSubstringLength = max(maxSubstringLength, findMaxSubstring(S, 2));

    cout << maxSubstringLength << "\n";
}
