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
const int LOG = 20;

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    vector<int> parentArray(N+1,0);
    parentArray[1] = 0;

    vector<vector<int>> childrenArray(N+1);
    for (int i = 2; i <= N; i++){
        cin >> parentArray[i];
        childrenArray[parentArray[i]].push_back(i);
    }

    vector<int> herbArray(N+1);
    for (int i = 1; i <= N; i++){
        cin >> herbArray[i];
    }
 
    vector<vector<int>> upValue(N + 1, vector<int>(LOG, 0));
    vector<int> depthValue(N + 1,0);
    function<void(int,int)> dfsLCA = [&](int V, int p){
        upValue[V][0] = p;
        for (int i = 1; i < LOG; i++){
            upValue[V][i] = (upValue[V][i-1] ? upValue[upValue[V][i-1]][i-1] : 0);
        }
        for (int w: childrenArray[V]){
            depthValue[w] = depthValue[V] + 1;
            dfsLCA(w, V);
        }
    };
    dfsLCA(1,0);
 
    auto getLCA = [&](int A, int B) -> int {
        if(depthValue[A] < depthValue[B]) swap(A, B);
        int D = depthValue[A] - depthValue[B];
        for (int i = 0; i < LOG; i++){
            if(D & (1 << i))
                A = upValue[A][i];
        }
        if(A == B)return A;
        for (int i = LOG - 1; i >= 0; i--){
            if(upValue[A][i] != upValue[B][i]){
                A = upValue[A][i];
                B = upValue[B][i];
            }
        }
        return upValue[A][0];
    };
 
    vector<vector<pair<int,int>>> queriesAt(N+1);
    vector<int> answerArray(Q, -1);
    for (int i = 0; i < Q; i++){
        int U, V, H;
        cin >> U >> V >> H;
        int L = getLCA(U, V);
        queriesAt[L].push_back({i, H});
    }
 
    vector<int> lastArray(N+1, -1);
    function<void(int)> DFS = [&](int V){
        int previousValue = lastArray[herbArray[V]];
        lastArray[herbArray[V]] = V;

        for(auto &q : queriesAt[V]){
            int qFirst = q.first, reqHerb = q.second;
            answerArray[qFirst] = (lastArray[reqHerb] == -1 ? -1 : lastArray[reqHerb]);
        }
        for (int w : childrenArray[V]) DFS(w);
        lastArray[herbArray[V]] = previousValue;
    };
    DFS(1);
 
    for(auto A : answerArray) cout << A << endl;
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