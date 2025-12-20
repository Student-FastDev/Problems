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

int N, M, Q;
vector<vector<pair<int, ll>>> neighbourList;
int currentTime;
vector<int> timeIn, lowArray;
vector<bool> onStack;
stack<int> stackArray;
int sccCount;
vector<int> sccNumber;

void tarjanDFS(int u) {
    timeIn[u] = lowArray[u] = ++currentTime;
    stackArray.push(u);
    onStack[u] = true;
    for(auto& edge : neighbourList[u]) {
        int v = edge.first;
        if(timeIn[v] == -1) {
            tarjanDFS(v);
            lowArray[u] = min(lowArray[u], lowArray[v]);
        } else if(onStack[v]) {
            lowArray[u] = min(lowArray[u], timeIn[v]);
        }
    }
    if(lowArray[u] == timeIn[u]) {
        while(true) {
            int v = stackArray.top();
            stackArray.pop();
            onStack[v] = false;
            sccNumber[v] = sccCount;
            if(u == v) break;
        }
        sccCount++;
    }
}

ll currentGcd;
vector<ll> dist;
vector<bool> visited;

void dfsGcd(int u, int currentSccId) {
    visited[u] = true;
    for(auto& edge : neighbourList[u]) {
        int v = edge.first;
        ll w = edge.second;
        if(sccNumber[v] != currentSccId) continue;
        if(visited[v]) {
            currentGcd = gcd(currentGcd, abs(dist[u] + w - dist[v]));
        } else {
            dist[v] = dist[u] + w;
            dfsGcd(v, currentSccId);
        }
    }
}

void solveTestCase() {
    cin >> N >> M;
    neighbourList.assign(N, {});
    for(int i = 0; i < M; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u; --v;
        neighbourList[u].push_back({v, w});
    }

    currentTime = 0;
    sccCount = 0;
    timeIn.assign(N, -1);
    lowArray.assign(N, -1);
    onStack.assign(N, false);
    sccNumber.assign(N, -1);
    for(int i = 0; i < N; ++i) {
        if(timeIn[i] == -1) tarjanDFS(i);
    }

    vector<vector<int>> nodesInScc(sccCount);
    for(int i = 0; i < N; ++i) nodesInScc[sccNumber[i]].push_back(i);

    vector<ll> sccGcd(sccCount, 0);
    vector<bool> isTrivial(sccCount, false);
    dist.assign(N, 0);
    visited.assign(N, false);

    for(int i = 0; i < sccCount; ++i) {
        if(nodesInScc[i].empty()) continue;
        if(size(nodesInScc[i]) == 1) {
            int u = nodesInScc[i][0];
            bool selfLoop = false;
            for(auto& edge : neighbourList[u]) {
                if(edge.first == u) { selfLoop = true; break; }
            }
            if(!selfLoop) {
                isTrivial[i] = true;
                continue;
            }
        }
        
        currentGcd = 0;
        int root = nodesInScc[i][0];
        dfsGcd(root, i);
        sccGcd[i] = currentGcd;
    }

    cin >> Q;
    while(Q--) {
        int v;
        ll s, t;
        cin >> v >> s >> t;
        --v;
        if(s % t == 0) {
            cout << "YES" << endl;
            continue;
        }
        int id = sccNumber[v];
        if(isTrivial[id]) {
            cout << "NO" << endl;
        } else {
            ll g = gcd(sccGcd[id], t);
            if(s % g == 0) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}