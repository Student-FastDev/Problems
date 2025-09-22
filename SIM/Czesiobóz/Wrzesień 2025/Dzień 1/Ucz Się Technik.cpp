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
using v = vector<int>;

const ll INF = 1e9;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, Q; 
    cin >> N >> Q;
    int M = N - 2;

    vector<array<int, 3>> trioArray(M);
    trioArray[0] = {1,2,3};
    for(int i = 1; i <= N - 3; i++){
        int u, v; 
        cin >> u >> v;
        trioArray[i] = {u, v, i + 3};
    }
    unordered_map<long long,int> edgeToTrio;
    edgeToTrio.reserve(M * 3 * 2);
    auto changeFunction = [&](int A, int B)->long long{ if(A > B) swap(A,B); return ((long long)A << 20) | B; };
    vector<vector<int>> trioNeighbourhood(M);
    for(int i = 0; i < M; i++){
        for(int e = 0; e < 3; e++){
            int A = trioArray[i][e], B = trioArray[i][(e + 1) % 3];
            long long K = changeFunction(A,B);
            auto it = edgeToTrio.find(K);
            if(it == edgeToTrio.end()) edgeToTrio[K] = i;
            else {
                int j = it->second;
                trioNeighbourhood[i].push_back(j);
                trioNeighbourhood[j].push_back(i);
            }
        }
    }

    vector<int> trioRepresentation(N+1);
    for(int v = 1; v <= N; ++v){
        if(v <= 3) trioRepresentation[v] = 0;
        else trioRepresentation[v] = v-3;
    }

    int LOG = 20;
    vector<int> zeroParent(M, -1), depthArray(M,0);
    {
        stack<int> stackArray;
        stackArray.push(0);
        zeroParent[0] = -1;
        depthArray[0] = 0;
        vector<char> wasSeen(M, 0); wasSeen[0] = 1;
        while(!stackArray.empty()){
            int u = stackArray.top(); stackArray.pop();
            for(int v: trioNeighbourhood[u]) if(!wasSeen[v]){
                wasSeen[v] = 1;
                zeroParent[v] = u;
                depthArray[v] = depthArray[u]+1;
                stackArray.push(v);
            }
        }
    }

    auto indexInTrio = [&](int trioID, int x)->int{
        for(int t = 0; t < 3; t++) if(trioArray[trioID][t] == x) return t;
        return -1;
    };

    auto makeMatrixEdge = [&](int child, int parent){
        array<int, 9> M;
        vector<int> sharedArray;
        for(int A = 0; A < 3; A++) for(int B = 0; B < 3; B++){
            if(trioArray[child][A] == trioArray[parent][B]) {
                if(sharedArray.empty() || sharedArray.back()!=trioArray[child][A]) sharedArray.push_back(trioArray[child][A]);
            }
        }
        for(int i = 0; i < 3; i++){
            int v = trioArray[child][i];
            for(int j = 0; j < 3; j++){
                int u = trioArray[parent][j];
                int bestValue = INF;
                for(int nodeValue : sharedArray){
                    int firstD = (v == nodeValue ? 0:1);
                    int secondD = (u == nodeValue ? 0:1);
                    bestValue = min(bestValue, firstD + secondD);
                }
                M[i * 3 + j] = bestValue;
            }
        }
        return M;
    };

    vector<v> UP(LOG, v(M, -1));
    vector<vector<array<int, 9>>> matrixUP(LOG, vector<array<int, 9>>(M));
    for(int v = 0; v < M; ++v){
        UP[0][v] = zeroParent[v] < 0 ? -1 : zeroParent[v];
        if(UP[0][v] != -1) matrixUP[0][v] = makeMatrixEdge(v, UP[0][v]);
        else {
            array<int, 9> I;
            for(int i = 0; i < 9; i++) I[i] = (i%4 == 0 ? 0 : INF);
            matrixUP[0][v] = I;
        }
    }

    auto mulMatrix = [&](const array<int,9> &A, const array<int,9> &B){
        array<int, 9> C;
        for(int i = 0; i < 3; i++){
            for(int K = 0; K < 3; K++){
                int bestValue = INF;
                for(int j = 0; j < 3; j++){
                    int o = A[i*3 + j];
                    int p = B[j*3 + K];
                    if(o >= INF || p >= INF) continue;
                    bestValue = min(bestValue, o + p);
                }
                C[i*3 + K] = bestValue;
            }
        }
        return C;
    };

    for(int l = 1; l < LOG; ++l){
        for(int v = 0; v < M; ++v){
            int middleValue = UP[l-1][v];
            if(middleValue == -1){
                UP[l][v] = -1;
                matrixUP[l][v] = matrixUP[l-1][v];
            } else {
                UP[l][v] = UP[l - 1][middleValue];
                matrixUP[l][v] = mulMatrix(matrixUP[l - 1][v], matrixUP[l - 1][middleValue]);
            }
        }
    }

    auto liftTo = [&](int &u, int h){
        array<int, 9> R;
        for(int i = 0; i < 9; i++) R[i] = (i % 4 == 0 ? 0 : INF);
        for(int l = 0; l < LOG; ++l){
            if(u == -1) break;
            if(h & (1 << l)){
                R = mulMatrix(R, matrixUP[l][u]);
                u = UP[l][u];
            }
        }
        return R;
    };

    auto LCA = [&](int A,int B){
        if(A == -1 || B == -1) return -1;
        if(depthArray[A] < depthArray[B]) swap(A,B);
        int differenceDepth = depthArray[A] - depthArray[B];
        for(int l = 0; l < LOG; ++l) if(differenceDepth & (1 << l)) A = UP[l][A];
        if(A == B) return A;
        for(int l = LOG - 1; l >= 0; --l){
            if(UP[l][A] != UP[l][B]){
                A = UP[l][A];
                B = UP[l][B];
            }
        }
        return zeroParent[A];
    };


    for(int p = 0; p < Q; ++p){
        int A, B; cin >> A >> B;
        if(A == B){ cout << 0 << endl; continue; }
        int tA = trioRepresentation[A], tB = trioRepresentation[B];
        if(tA == tB){
            cout << 1 << endl;
            continue;
        }
        int u = tA, v = tB;
        int L = LCA(u,v);
        int dU = depthArray[u] - depthArray[L];
        int dV = depthArray[v] - depthArray[L];
        array<int, 9> MA = liftTo(u, dU);
        array<int, 9> MB = liftTo(v, dV);
        int idxA = indexInTrio(tA, A);
        int idxB = indexInTrio(tB, B);
        int finalAnswer = INF;
        for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++){
            int dA = MA[idxA * 3 + x];
            int dB = MB[idxB * 3 + y];
            if(dA >= INF || dB >= INF) continue;
            int betweenValue = (trioArray[L][x] == trioArray[L][y] ? 0 : 1);
            finalAnswer = min(finalAnswer, dA + dB + betweenValue);
        }
        cout << finalAnswer << endl;
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
