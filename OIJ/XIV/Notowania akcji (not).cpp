#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> prices(N);
    for (int i = 0; i < N; ++i) {
        cin >> prices[i];
    }

    vector<int> lengths(N, 1);
    vector<long long> count(N + 1, 0);

    for (int i = 1; i < N; ++i) {
        if (prices[i] > prices[i - 1]) {
            lengths[i] = lengths[i - 1] + 1;
        }
    }

    for (int i = 0; i < N; ++i) {
        count[lengths[i]]++;
    }

    vector<long long> at_least(N + 1, 0);

    for (int i = N; i >= 1; --i) {
        if (i < N) {
            at_least[i] = at_least[i + 1];
        }
        at_least[i] += count[i];
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int K;
        cin >> K;
        cout << at_least[K] << '\n';
    }

    return 0;
}