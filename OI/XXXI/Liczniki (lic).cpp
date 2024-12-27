#include <bits/stdc++.h>
using namespace std;

void solveLiczniki(int N, int M, const vector<int>& C, const vector<int>& S, const vector<vector<int>>& readings) {
    vector<int> meterIndices(N);
    iota(meterIndices.begin(), meterIndices.end(), 0);
    sort(meterIndices.begin(), meterIndices.end(), [&](int i, int j) {
        return C[i] > C[j];
    });

    vector<int> initialStates(N);
    for (int i = 0; i < N; ++i) {
        initialStates[i] = S[meterIndices[i]];
    }

    vector<vector<int>> sortedReadings = readings;
    for (auto& month : sortedReadings) {
        sort(month.begin(), month.end());
    }

    vector<int> currentStates = initialStates;

    for (int month = 0; month < M; ++month) {
        vector<int> nextStates(N, -1);
        multiset<int> availableReadings(sortedReadings[month].begin(), sortedReadings[month].end());

        for (int i = 0; i < N; ++i) {
            int requiredMin = currentStates[i];
            auto it = availableReadings.lower_bound(requiredMin);
            if (it == availableReadings.end()) {
                cout << "NIE" << endl;
                return;
            }

            nextStates[i] = *it;
            availableReadings.erase(it);
        }

        currentStates = nextStates;
    }

    long long totalCost = 0;
    for (int i = 0; i < N; ++i) {
        totalCost += (long long)C[meterIndices[i]] * (currentStates[i] - initialStates[i]);
    }

    cout << totalCost << endl;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> C(N);
    for (int i = 0; i < N; ++i) {
        cin >> C[i];
    }

    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    vector<vector<int>> readings(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> readings[i][j];
        }
    }

    solveLiczniki(N, M, C, S, readings);
    return 0;
}
