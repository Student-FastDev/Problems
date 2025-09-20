// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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

struct Edge {
    int U, V, W, edgeID;
    bool inMST;
};

struct DSU {
    vector<int> P, R;
    DSU(int N): P(N+1), R(N+1,0) {
        iota(P.begin(), P.end(), 0);
    }
    int find(int x) { return P[x]==x ? x : P[x]=find(P[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if(a == b) return false;
        if(R[a] < R[b]) swap(a,b);
        P[b] = a;
        if(R[a] == R[b]) R[a]++;
        return true;
    }
};

const int LOG = 20;

vector<vector<pair<int,int>>> neighborHood;
vector<vector<int>> up, maxEdge;
vector<int> depth;

void DFS(int V, int P, int W) {
    up[V][0] = P;
    maxEdge[V][0] = W;
    for(int i = 1; i < LOG; i++){
        up[V][i] = up[ up[V][i-1] ][i-1];
        maxEdge[V][i] = max(maxEdge[V][i-1], maxEdge[ up[V][i-1] ][i-1]);
    }
    for(auto [to, c] : neighborHood[V]){
        if(to == P) continue;
        depth[to] = depth[V]+1;
        DFS(to, V, c);
    }
}

int getMaxEdge(int a, int b) {
    if(depth[a] < depth[b]) swap(a,b);
    int finalResult=0;
    int depthDifference = depth[a] - depth[b];
    for(int i = LOG-1; i >= 0; i--){
        if(depthDifference & (1 << i)){
            finalResult = max(finalResult, maxEdge[a][i]);
            a = up[a][i];
        }
    }
    if(a == b) return finalResult;
    for(int i = LOG-1; i>=0; i--){
        if(up[a][i]!=up[b][i]){
            finalResult = max({finalResult, maxEdge[a][i], maxEdge[b][i]});
            a = up[a][i];
            b = up[b][i];
        }
    }
    finalResult = max({finalResult, maxEdge[a][0], maxEdge[b][0]});
    return finalResult;
}
 
void solveTestCase() {
    int N, M;
    cin>> N >> M;
    vector<Edge> edgesArray(M);
    for(int i = 0; i < M; i++){
        cin >> edgesArray[i].U >> edgesArray[i].V >> edgesArray[i].W;
        edgesArray[i].edgeID = i;
        edgesArray[i].inMST = false;
    }

    neighborHood.assign(N+1, {});
    up.assign(N+1, vector<int>(LOG));
    maxEdge.assign(N+1, vector<int>(LOG));
    depth.assign(N+1, 0);

    sort(edgesArray.begin(), edgesArray.end(), [](auto &a, auto &b){return a.W<b.W;});
    DSU dsu(N);
    for(auto &e: edgesArray){
        if(dsu.unite(e.U,e.V)){
            e.inMST = true;
            neighborHood[e.U].push_back({e.V,e.W});
            neighborHood[e.V].push_back({e.U,e.W});
        }
    }

    depth[1]=0;
    DFS(1, 1, 0);

    vector<string> finalAnswer(M);
    for(auto &e: edgesArray){
        if(e.inMST){
            finalAnswer[e.edgeID] = "TAK";
        }else{
            int maxValue = getMaxEdge(e.U,e.V);
            if(maxValue >= e.W) finalAnswer[e.edgeID] = "TAK";
            else finalAnswer[e.edgeID] = "NIE";
        }
    }

    for(auto &s: finalAnswer) cout << s << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
