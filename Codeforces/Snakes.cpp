#include <bits/stdc++.h>
typedef long long Ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, Q;
    cin >> N >> Q;

    vector<pair<int, char>> eventsArray(Q);
    for (int I = 0; I < Q; ++I) {
        int S;
        char operationVariable;
        cin >> S >> operationVariable;
        eventsArray[I] = {S, operationVariable};
    }

    vector<vector<int>> minDist(N + 1, vector<int>(N + 1, 0));

    for (int I = 1; I <= N; ++I) {
        for (int J = 1; J <= N; ++J) {
            if (I == J) continue;
            int gapVariable = 0, minGap = 0;
            for (const auto& event : eventsArray) {
                if (event.first == I && event.second == '+') {
                    gapVariable--;
                } else if (event.first == J && event.second == '-') {
                    gapVariable++;
                }
                minGap = min(minGap, gapVariable);
            }
            minDist[I][J] = -minGap + 1;
        }
    }

    vector<vector<int>> DP(1 << N, vector<int>(N + 1, INT_MAX));
    for (int I = 1; I <= N; ++I) {
        DP[1 << (I - 1)][I] = 1;
    }

    for (int mask = 0; mask < (1 << N); ++mask) {
        for (int last = 1; last <= N; ++last) {
            if (!(mask & (1 << (last - 1)))) continue;
            for (int next = 1; next <= N; ++next) {
                if (mask & (1 << (next - 1))) continue;
                int newMask = mask | (1 << (next - 1));
                DP[newMask][next] = min(DP[newMask][next], DP[mask][last] + minDist[last][next]);
            }
        }
    }

    int result = INT_MAX;
    for (int I = 1; I <= N; ++I) {
        int enlargements = 0;
        for (const auto& event : eventsArray) {
            if (event.first == I && event.second == '+') {
                enlargements++;
            }
        }
        result = min(result, DP[(1 << N) - 1][I] + enlargements);
    }

    cout << result << endl;

    return 0;
}
