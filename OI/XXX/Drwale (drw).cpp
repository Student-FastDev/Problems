#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    sort(A.rbegin(), A.rend());

    int largest = A[0];
    A.erase(A.begin());

    int totalSum = accumulate(A.begin(), A.end(), 0);

    unordered_map<int, int> valueCount;
    for (int value : A) {
        valueCount[value]++;
    }

    bitset<5000001> DP;
    DP[0] = 1;
    for (const auto& [value, count] : valueCount) {
        int remaining = count;
        for (int k = 1; remaining > 0; k <<= 1) {
            int num = min(k, remaining);
            DP |= DP << (value * num);
            remaining -= num;
        }
    }

    int halfSum = totalSum / 2;
    int bestSum = 0;
    for (int i = halfSum; i >= 0; --i) {
        if (DP[i]) {
            bestSum = i;
            break;
        }
    }

    int result = max(bestSum + largest, totalSum - bestSum);
    cout << result << endl;

    return 0;
}
