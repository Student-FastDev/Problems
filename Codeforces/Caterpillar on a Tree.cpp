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
#define size(x)  (int)x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; 

vector<vector<int>> adj;
vector<int> depth;
vector<int> height;
vector<int> target;
priority_queue<pii> pq;

void dfsCalc(int u, int d) {
    depth[u] = d;
    height[u] = 0;
    target[u] = -1;
    
    for (int v : adj[u]) {
        dfsCalc(v, d + 1);
        if (height[v] + 1 > height[u]) {
            height[u] = height[v] + 1;
            target[u] = v;
        }
    }
}

void addPath(int u) {
    int curr = u;
    while (curr != -1) {
        for (int v : adj[curr]) {
            if (v != target[curr]) {
                int val = 1 + height[v] - depth[curr];
                pq.push({val, v});
            }
        }
        curr = target[curr];
    }
}

void solveTestCase() {
    int N;
    ll K;
    cin >> N >> K;

    adj.assign(N + 1, vector<int>());
    for (int i = 2; i <= N; ++i) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    depth.assign(N + 1, 0);
    height.assign(N + 1, 0);
    target.assign(N + 1, -1);
    
    pq = priority_queue<pii>();

    dfsCalc(1, 0);

    pq.push({height[1], 1});

    ll totalSavings = 0;
    
    for (int i = 0; i <= K; ++i) {
        if (pq.empty()) break;
        pii top = pq.top();
        pq.pop();
        
        if (top.first <= 0) break;
        
        totalSavings += top.first;
        addPath(top.second);
    }

    ll totalEdges = N - 1;
    ll ans = 2 * totalEdges - totalSavings;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}