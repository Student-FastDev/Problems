#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct State {
    int position;
    bool usedMagic;
};

int main() {
    int N;
    cin >> N;
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    vector<int> sharks(N);
    for (int i = 0; i < N; i++) {
        cin >> sharks[i];
    }

    vector<vector<bool>> DP(N, vector<bool>(2, false));
    DP[0][0] = true;

    int maxReach = 0;

    queue<State> q;
    q.push({0, false});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int pos = current.position;
        bool usedMagic = current.usedMagic;

        for (int jump : {A, B, C}) {
            int nextPos = pos + jump;
            if (nextPos < N && sharks[nextPos] == 0 && !DP[nextPos][usedMagic]) {
                DP[nextPos][usedMagic] = true;
                q.push({nextPos, usedMagic});
                maxReach = max(maxReach, nextPos);
            }
        }

        if (!usedMagic) {
            int nextPos = pos + D;
            if (nextPos < N && sharks[nextPos] == 0 && !DP[nextPos][true]) {
                DP[nextPos][true] = true;
                q.push({nextPos, true});
                maxReach = max(maxReach, nextPos);
            }
        }
    }

    cout << maxReach+1 << endl;

    return 0;
}
