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
const ll MOD = 1e9+7; 

struct Dinic {
    struct Edge {
        int to;
        int capacity;
        int flow;
        int rev;
    };

    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> ptr;
    int n;
    int source, sink;

    Dinic(int nodes, int s, int t) : n(nodes), source(s), sink(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void addEdge(int from, int to, int cap) {
        adj[from].push_back({to, cap, 0, (int)size(adj[to])});
        adj[to].push_back({from, 0, 0, (int)size(adj[from]) - 1});
    }

    bool bfs() {
        fill(all(level), -1);
        level[source] = 0;
        queue<int> q;
        q.push(source);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto& edge : adj[v]) {
                if (edge.capacity - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[sink] != -1;
    }

    int dfs(int v, int pushed) {
        if (pushed == 0) return 0;
        if (v == sink) return pushed;
        for (int& cid = ptr[v]; cid < size(adj[v]); ++cid) {
            auto& edge = adj[v][cid];
            int tr = edge.to;
            if (level[v] + 1 != level[tr] || edge.capacity - edge.flow == 0) continue;
            int push = dfs(tr, min(pushed, edge.capacity - edge.flow));
            if (push == 0) continue;
            edge.flow += push;
            adj[tr][edge.rev].flow -= push;
            return push;
        }
        return 0;
    }

    int maxFlow() {
        int flow = 0;
        while (bfs()) {
            fill(all(ptr), 0);
            while (int pushed = dfs(source, 1e9)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<string> grid(N);
    int blackCells = 0;
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
        for (char c : grid[i]) {
            if (c == '#') blackCells++;
        }
    }

    vector<vector<int>> hID(N, vector<int>(M, -1));
    vector<vector<int>> vID(N, vector<int>(M, -1));

    int cntH = 0;
    int cntV = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '#') {
                if (j + 1 < M && grid[i][j+1] == '#') {
                    hID[i][j] = cntH++;
                }
                if (i + 1 < N && grid[i+1][j] == '#') {
                    vID[i][j] = cntV++;
                }
            }
        }
    }

    int source = 0;
    int sink = cntH + cntV + 1;
    Dinic dinic(sink + 1, source, sink);

    for (int i = 0; i < cntH; ++i) {
        dinic.addEdge(source, i + 1, 1);
    }
    for (int i = 0; i < cntV; ++i) {
        dinic.addEdge(cntH + 1 + i, sink, 1);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (hID[i][j] != -1) {
                int u = hID[i][j] + 1; 
                
                if (vID[i][j] != -1) {
                    dinic.addEdge(u, cntH + 1 + vID[i][j], 1);
                }
                if (i > 0 && vID[i-1][j] != -1) {
                    dinic.addEdge(u, cntH + 1 + vID[i-1][j], 1);
                }
                if (vID[i][j+1] != -1) {
                    dinic.addEdge(u, cntH + 1 + vID[i][j+1], 1);
                }
                if (i > 0 && vID[i-1][j+1] != -1) {
                    dinic.addEdge(u, cntH + 1 + vID[i-1][j+1], 1);
                }
            }
        }
    }

    int maxMatching = dinic.maxFlow();
    int totalMerges = (cntH + cntV) - maxMatching;
    cout << blackCells - totalMerges << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solveTestCase();
    return 0;
}