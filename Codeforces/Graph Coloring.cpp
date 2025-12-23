// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

int dpTable[5005][5005];

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    int N1, N2, N3;
    cin >> N1 >> N2 >> N3;

    vector<vector<int>> neighbourList(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        neighbourList[u].push_back(v);
        neighbourList[v].push_back(u);
    }

    vector<int> vertexColors(N + 1, 0);
    vector<pair<vector<int>, vector<int>>> connectedComponents;
    bool isBipartite = true;

    for (int i = 1; i <= N; ++i) {
        if (vertexColors[i] != 0) continue;

        vector<int> firstPartition, secondPartition;
        queue<int> bfsQueue;
        
        vertexColors[i] = 1;
        firstPartition.push_back(i);
        bfsQueue.push(i);

        while (!bfsQueue.empty()) {
            int u = bfsQueue.front();
            bfsQueue.pop();

            for (int v : neighbourList[u]) {
                if (vertexColors[v] == 0) {
                    vertexColors[v] = 3 - vertexColors[u];
                    if (vertexColors[v] == 1) firstPartition.push_back(v);
                    else secondPartition.push_back(v);
                    bfsQueue.push(v);
                } else if (vertexColors[v] == vertexColors[u]) {
                    isBipartite = false;
                }
            }
        }
        connectedComponents.push_back({firstPartition, secondPartition});
    }

    if (!isBipartite) {
        cout << "NO" << endl;
        return;
    }

    int K = (int)size(connectedComponents);
    for (int i = 0; i <= K; ++i) {
        for (int j = 0; j <= N2; ++j) {
            dpTable[i][j] = -1;
        }
    }

    dpTable[0][0] = 0;

    for (int i = 0; i < K; ++i) {
        int size1 = (int)size(connectedComponents[i].first);
        int size2 = (int)size(connectedComponents[i].second);
        for (int j = 0; j <= N2; ++j) {
            if (dpTable[i][j] != -1) {
                if (j + size1 <= N2) dpTable[i + 1][j + size1] = 1;
                if (j + size2 <= N2) dpTable[i + 1][j + size2] = 2;
            }
        }
    }

    if (dpTable[K][N2] == -1) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    string resultLabels(N, ' ');
    vector<int> nonTwoVertices;

    int currentSum = N2;
    for (int i = K; i > 0; --i) {
        int choice = dpTable[i][currentSum];
        const vector<int>& chosenForTwo = (choice == 1) ? connectedComponents[i - 1].first : connectedComponents[i - 1].second;
        const vector<int>& chosenForOthers = (choice == 1) ? connectedComponents[i - 1].second : connectedComponents[i - 1].first;

        for (int u : chosenForTwo) {
            resultLabels[u - 1] = '2';
        }
        for (int u : chosenForOthers) {
            nonTwoVertices.push_back(u);
        }
        currentSum -= (int)size(chosenForTwo);
    }

    for (int i = 0; i < (int)size(nonTwoVertices); ++i) {
        if (i < N1) resultLabels[nonTwoVertices[i] - 1] = '1';
        else resultLabels[nonTwoVertices[i] - 1] = '3';
    }

    cout << resultLabels << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}