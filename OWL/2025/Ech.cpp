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
    int u, v;
};

void solveTestCase(){
    int N; 
    cin >> N;

    vector<Edge> edges(N);
    vector<vector<pair<int,int>>> tree(N+1);

    for (int i = 1; i <= N-1; i++){
        int A, B; 
        cin >> A >> B;
        edges[i] = {A, B};
        tree[A].push_back({B,i});
        tree[B].push_back({A,i});
    }

    vector<int> P(N+1);
    for (int i = 1; i <= N; i++){
        cin >> P[i];
    }

    vector<int> pairsArray(N+1, 0), depthArray(N+1, 0), pairsEdge(N+1, 0); 
    vector<bool> visitedArray(N+1, false);
    queue<int> queueArray;
    int root = 1;
    visitedArray[root] = true;
    depthArray[root] = 0;
    pairsArray[root] = 0;
    queueArray.push(root);
    while(!queueArray.empty()){
        int current = queueArray.front();
        queueArray.pop();
        for(auto &nbr : tree[current]){
            int nxt = nbr.first, eid = nbr.second;
            if(!visitedArray[nxt]){
                visitedArray[nxt] = true;
                pairsArray[nxt] = current;
                depthArray[nxt] = depthArray[current] + 1;
                pairsEdge[nxt] = eid;
                queueArray.push(nxt);
            }
        }
    }

    int LOG = 0;
    while((1 << LOG) <= N) LOG++;
    vector<vector<int>> up(N+1, vector<int>(LOG, 0));
    for (int i = 1; i <= N; i++){
        up[i][0] = pairsArray[i];
    }
    for (int j = 1; j < LOG; j++){
        for (int i = 1; i <= N; i++){
            up[i][j] = up[ up[i][j-1] ][j-1];
        }
    }
    auto LCA = [&](int A, int B) -> int {
        if(depthArray[A] < depthArray[B]) swap(A, B);
        int d = depthArray[A] - depthArray[B];
        for (int i = 0; i < LOG; i++){
            if(d & (1 << i))
                A = up[A][i];
        }
        if(A == B) return A;
        for (int i = LOG-1; i >= 0; i--){
            if(up[A][i] != up[B][i]){
                A = up[A][i];
                B = up[B][i];
            }
        }
        return pairsArray[A];
    };

    vector<vector<int>> DAG(N, vector<int>());
    vector<int> inDegree(N, 0);
    vector<bool> isPrimary(N, false);

    for (int A = 1; A <= N; A++){
        int U = P[A];
        if(U == A) continue;
        int l = LCA(A, U);
        vector<int> path;

        int current = A;
        while(current != l){
            path.push_back(pairsEdge[current]);
            current = pairsArray[current];
        }
        vector<int> temp;
        current = U;
        while(current != l){
            temp.push_back(pairsEdge[current]);
            current = pairsArray[current];
        }
        reverse(temp.begin(), temp.end());
        for(auto eid : temp)
            path.push_back(eid);

        if(path.empty()) continue;

        for (auto eid : path)
            isPrimary[eid] = true;

        for (size_t i = 0; i + 1 < size(path); i++){
            int aedge = path[i], bedge = path[i+1];
            DAG[aedge].push_back(bedge);
            inDegree[bedge]++;
        }

        int firstEdge = path[0];
        for(auto &pr : tree[A]){
            int eid = pr.second;
            if(eid == firstEdge) continue;
            DAG[firstEdge].push_back(eid);
            inDegree[eid]++;
        }
    }

    queue<int> dqArray;
    vector<int> topoSort;
    for (int i = 1; i <= N-1; i++){
        if(inDegree[i] == 0) dqArray.push(i);
    }
    while(!dqArray.empty()){
        int node = dqArray.front();
        dqArray.pop();
        topoSort.push_back(node);
        for (int nxt : DAG[node]){
            inDegree[nxt]--;
            if(inDegree[nxt] == 0)
                dqArray.push(nxt);
        }
    }
    if((int)size(topoSort) != N-1){
        cout << -1 << endl;
        return;
    }

    vector<int> solutionArray;
    for (int eid : topoSort){
        if(isPrimary[eid])
            solutionArray.push_back(eid);
    }

    cout << size(solutionArray) << endl;
    for (int eid : solutionArray){
        cout << edges[eid].u << " " << edges[eid].v << endl;
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
