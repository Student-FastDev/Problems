// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& o, auto p) -> decltype(p.first, o) { return o << '(' << p.first << ", " << p.second << ')'; }
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) { o << '{'; int i = 2; for (auto e : x) o << (", ") + i << e, i = 0; return o << '}'; }
#define LOG(x...) cerr << "[" #x "]: ", [](auto... $) { ((cerr << $ << "; "), ...) << endl; }(x);
#else
#define LOG(x...) (void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(), (x).end()
#define endl    '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N;
    cin >> N;

    if (N == 1) {
        cout << 0 << endl;
        return;
    }

    vector<vector<int>> neighbourList(N + 1);
    vector<int> degree(N + 1, 0);

    for (int i = 0; i < N - 1; ++i) {
        int U, V;
        cin >> U >> V;
        neighbourList[U].push_back(V);
        neighbourList[V].push_back(U);
        degree[U]++;
        degree[V]++;
    }

    vector<int> majorVertices;
    for (int i = 1; i <= N; ++i) {
        if (degree[i] >= 3) {
            majorVertices.push_back(i);
        }
    }

    if (size(majorVertices) == 0) {
        cout << 1 << endl;
        return;
    }

    int root = majorVertices[0];
    vector<int> parent(N + 1, 0);
    vector<int> traversalOrder;
    traversalOrder.reserve(N);
    vector<bool> visited(N + 1, false);

    queue<int> bfsQueue;
    bfsQueue.push(root);
    visited[root] = true;

    while (!bfsQueue.empty()) {
        int U = bfsQueue.front();
        bfsQueue.pop();
        traversalOrder.push_back(U);

        for (int v : neighbourList[U]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = U;
                bfsQueue.push(v);
            }
        }
    }

    vector<int> majorCountInSubtree(N + 1, 0);

    for (int i = N - 1; i >= 0; --i) {
        int U = traversalOrder[i];
        if (degree[U] >= 3) {
            majorCountInSubtree[U] = 1;
        }
        for (int v : neighbourList[U]) {
            if (v != parent[U]) {
                majorCountInSubtree[U] += majorCountInSubtree[v];
            }
        }
    }

    int queriesNeeded = 0;
    for (int u : majorVertices) {
        int legs = 0;
        for (int v : neighbourList[u]) {
            if (v == parent[u]) continue;

            if (majorCountInSubtree[v] == 0) {
                legs++;
            }
        }
        if (legs > 0) {
            queriesNeeded += (legs - 1);
        }
    }

    cout << queriesNeeded << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}