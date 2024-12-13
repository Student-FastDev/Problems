#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

vector<vector<int>> neighbourList;
vector<ll> dpWhite, dpBlack;

void DFS(int node, int parent) {
    dpWhite[node] = 1;
    dpBlack[node] = 1;

    for (int neighbor : neighbourList[node]) {
        if (neighbor == parent) continue;
        DFS(neighbor, node);
        dpWhite[node] = dpWhite[node] * (dpWhite[neighbor] + dpBlack[neighbor]) % MOD;
        dpBlack[node] = dpBlack[node] * dpWhite[neighbor] % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    neighbourList.resize(N + 1);
    dpWhite.resize(N + 1);
    dpBlack.resize(N + 1);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }

    DFS(1, -1);

    ll result = (dpWhite[1] + dpBlack[1]) % MOD;
    cout << result << endl;
    return 0;
}
