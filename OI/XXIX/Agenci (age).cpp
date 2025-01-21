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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'

const int INF = 1e9;
const ll MOD = 1e9 + 7;

vector<bool> isAgent;
vector<vector<int>> neighbourHood;
vector<int> topDP, downDP, DP;

void addEdge(int u, int v) {
    neighbourHood[u].push_back(v);
    neighbourHood[v].push_back(u);
}

void DFS(int node, int parent) {
    int S = 0;
    for (auto i : neighbourHood[node]) {
        if (i != parent) {
            DFS(i, node);
            S += DP[i];
        }
    }

    if (isAgent[node]) {
        topDP[node] = S;
        downDP[node] = -INF;
        DP[node] = S;
        for (auto i : neighbourHood[node]) {
            if (i != parent) {
                DP[node] = max(DP[node], S - DP[i] + downDP[i] + 1);
            }
        }
    } else {
        downDP[node] = S;
        for (auto i : neighbourHood[node]) {
            if (i != parent) {
                downDP[node] = max(downDP[node], S - DP[i] + downDP[i] + 1);
            }
        }

        topDP[node] = -INF;
        for (auto i : neighbourHood[node]) {
            if (i != parent) {
                topDP[node] = max(topDP[node], S - DP[i] + topDP[i] + 1);
            }
        }

        pair<int, int> MAX = {-INF, 0};
        pair<int, int> SECOND_MAX = {-INF, 0};
        for (auto i : neighbourHood[node]) {
            if (i != parent) {
                if (MAX.first < downDP[i] - DP[i]) {
                    SECOND_MAX = MAX;
                    MAX = {downDP[i] - DP[i], i};
                } else if (SECOND_MAX.first < downDP[i] - DP[i]) {
                    SECOND_MAX = {downDP[i] - DP[i], i};
                }
            }
        }

        DP[node] = S;
        for (auto i : neighbourHood[node]) {
            if (i != parent) {
                DP[node] = max(DP[node], S - DP[i] + topDP[i] + 1);
                if (MAX.second == i) {
                    DP[node] = max(DP[node], S - DP[i] + topDP[i] + SECOND_MAX.first + 2);
                } else {
                    DP[node] = max(DP[node], S - DP[i] + topDP[i] + MAX.first + 2);
                }
            }
        }
    }

    LOG(isAgent[node], DP[node], topDP[node], downDP[node]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    isAgent.resize(N + 1, false);
    neighbourHood.resize(N + 1);
    topDP.resize(N + 1, 0);
    downDP.resize(N + 1, 0);
    DP.resize(N + 1, 0);

    for (int i = 1; i <= K; i++) {
        int agentPosition;
        cin >> agentPosition;
        isAgent[agentPosition] = true;
    }

    for (int i = 1; i < N; i++) {
        int A, B;
        cin >> A >> B;
        addEdge(A, B);
    }

    DFS(1, -1);
    cout << 2 * (N - K) - DP[1] << endl;

    return 0;
}
