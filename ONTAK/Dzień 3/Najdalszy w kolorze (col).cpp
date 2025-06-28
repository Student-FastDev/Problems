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
const ll MAX_N = 500000;
const ll MOD = 1e9+7; // 998244353

int N, Q;
vector<int> G[MAX_N+1];
int colorArray[MAX_N+1];
vector<int> nodesArray[MAX_N+1];

int upArray[20][MAX_N + 1], depthArray[MAX_N + 1];

void DFS(int U, int P){
    upArray[0][U] = P;
    for(int V: G[U]){
        if(V == P) continue;
        depthArray[V] = depthArray[U] + 1;
        DFS(V, U);
    }
}

int LCA(int U, int V){
    if(depthArray[U] < depthArray[V]) swap(U, V);
    int heightDifference = depthArray[U] - depthArray[V];
    for(int k = 0; k < 20; k++)
        if(heightDifference & (1 << k)) U = upArray[k][U];

    if(U == V) return U;
    for(int k = 19; k >= 0; k--){
        if(upArray[k][U] != upArray[k][V]){
            U = upArray[k][U];
            V = upArray[k][V];
        }
    }
    return upArray[0][U];
}

inline int distanceBetweenNodes(int U, int V){
    int W = LCA(U,V);
    return depthArray[U] + depthArray[V] - 2 * depthArray[W];
}

void solveTestCase() {
    cin >> N >> Q;
    for(int i = 1; i <= N; i++){
        cin >> colorArray[i];
        nodesArray[colorArray[i]].push_back(i);
    }
    for(int i = 1; i < N; i++){
        int U, V; cin >> U >> V;
        G[U].push_back(V);
        G[V].push_back(U);
    }

    depthArray[1] = 0;
    DFS(1, 1);
    for(int k = 1; k < 20; k++){
        for(int V = 1; V <= N; V++){
            upArray[k][V] = upArray[k-1][upArray[k-1][V]];
        }
    }

    vector<pii> roadsEnd(MAX_N+1, {-1,-1});
    for(int C = 1; C <= MAX_N; C++){
        if(nodesArray[C].empty()) continue;
        int S = nodesArray[C][0], A = S;
        for(int U: nodesArray[C]){
            if(distanceBetweenNodes(S, U) > distanceBetweenNodes(S, A))
                A = U;
        }
        int B = A;
        for(int U: nodesArray[C]){
            if(distanceBetweenNodes(A, U) > distanceBetweenNodes(A, B))
                B = U;
        }
        roadsEnd[C] = {A, B};
    }

    while(Q--){
        int V, C; cin >> V >> C;

        if(roadsEnd[C].first < 0){
            cout << -1 << endl;
        } else {
            auto [A, B] = roadsEnd[C];
            int finalAnswer = max(distanceBetweenNodes(V,A), distanceBetweenNodes(V,B));
            cout << finalAnswer << endl;
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
