#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestStaircaseSubsequence(const vector<int>& sequence) {
    vector<int> DP(10, 0);

    for (int num : sequence) {
        DP[num] = max(DP[num], DP[num - 1] + 1);
    }

    return *max_element(DP.begin(), DP.end());
}

int main() {
    int n;
    cin >> n;

    vector<int> sequence(n);
    for (int i = 0; i < n; i++) {
        cin >> sequence[i];
    }

    cout << longestStaircaseSubsequence(sequence) << endl;

    return 0;
}
