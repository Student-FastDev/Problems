#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<pair<int, int>> values(N);
        for (int i = 0; i < N; i++) {
            cin >> values[i].first;
            values[i].second = i;
        }

        sort(values.begin(), values.end(), [](pair<int, int> &a, pair<int, int> &b) {
            if (a.first == b.first)
                return a.second > b.second;
            return a.first < b.first;
        });

        long long totalSum = 0;
        int tasksDone = 0;
        vector<int> additions(N, 0);

        for (int i = 0; tasksDone < K; i++) {
            int tasksToAdd = min(M, K - tasksDone);
            additions[values[i].second] += tasksToAdd;
            totalSum += static_cast<long long>(values[i].first) * tasksToAdd;
            tasksDone += tasksToAdd;
        }

        int runningSum = 0;
        for (int i = 0; i < N; i++) {
            totalSum += static_cast<long long>(additions[i]) * runningSum;
            runningSum += additions[i];
        }

        cout << totalSum << "\n";
    }

    return 0;
}
