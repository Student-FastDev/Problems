#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

vector<vector<int>> neighbourList;
vector<int> DP;
vector<bool> visited;
stack<int> topoStack;

void topoSort(int V) {
    visited[V] = true;
    for (int U : neighbourList[V]) {
        if (!visited[U]) {
            topoSort(U);
        }
    }
    topoStack.push(V);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    neighbourList.resize(N + 1);
    DP.resize(N + 1, 0);
    visited.resize(N + 1, false);

    for (int i = 0; i < M; i++) {
        int V, U;
        cin >> V >> U;
        neighbourList[V].push_back(U);
    }

    for (int i = 1; i <= N; i++)     {
        if (!visited[i]) {
            topoSort(i);
        }
    }

    while (!topoStack.empty()) {
        int V = topoStack.top();
        topoStack.pop();
        for (int U : neighbourList[V]) {
            DP[U] = max(DP[U], DP[V] + 1);
        }
    }

    int longestPath = *max_element(DP.begin(), DP.end());
    cout << longestPath << endl;
    return 0;
}
