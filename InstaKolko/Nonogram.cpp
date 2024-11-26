#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int minimalChanges(string S, int N) {
    int l = S.length();
    vector<int> prefixSum(l + 1, 0);

    for (int i = 0; i < l; ++i) {
        prefixSum[i + 1] = prefixSum[i] + (S[i] == '1' ? 1 : 0);
    }

    int minChanges = l;

    for (int i = 0; i + N <= l; ++i) {
        int onesInBlock = prefixSum[i + N] - prefixSum[i];
        int changesToFormBlock = N - onesInBlock;
        int changesToFormZeroOutside = prefixSum[l] - onesInBlock;
        int totalChanges = changesToFormBlock + changesToFormZeroOutside;

        minChanges = min(minChanges, totalChanges);
    }

    return minChanges;
}

int main() {
    string S;
    int N;

    cin >> S >> N;

    cout << minimalChanges(S, N) << endl;

    return 0;
}
