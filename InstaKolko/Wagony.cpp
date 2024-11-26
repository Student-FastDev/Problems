#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INT_MAX = 1e9 + 1;

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int C, M, T;
    cin >> C >> M >> T;

    const int MAX_N = 1000;

    vector<int> DP(MAX_N + 1, INT_MAX);

    DP[1] = 0;

    for (int i = 2; i <= MAX_N; ++i) {
        for (int j = 1; j <= i / 2; ++j) {
            int A = j;
            int B = i - j;
            int cost = (C * (A + B)) % M;
            DP[i] = min(DP[i], DP[A] + DP[B] + cost);
        }
    }

    vector<int> results(T);
    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        results[t] = DP[N];
    }

    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}
