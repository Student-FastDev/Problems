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

int N, M;
vector<vector<int>> neighbourList;
vector<int> depthArray, lowArray, parentArray, subtreeSize;
vector<ll> finalAnswer;

void DFS(int u) {
    lowArray[u] = depthArray[u];
    subtreeSize[u] = 1;
    for (int v : neighbourList[u]) {
        if (v == parentArray[u]) continue;
        if (depthArray[v] == -1) {
            parentArray[v] = u;
            depthArray[v] = depthArray[u] + 1;
            DFS(v);
            subtreeSize[u] += subtreeSize[v];
            lowArray[u] = min(lowArray[u], lowArray[v]);
        } else {
            lowArray[u] = min(lowArray[u], depthArray[v]);
        }
    }

    ll totalNumber = N - 1;
    ll sumSquares = 0;
    ll sumSeperateSizes = 0;
    for (int v : neighbourList[u]) {
        if (parentArray[v] == u && lowArray[v] >= depthArray[u]) {
            sumSquares += 1LL * subtreeSize[v] * subtreeSize[v];
            sumSeperateSizes += subtreeSize[v];
        }
    }
    ll restNumber = totalNumber - sumSeperateSizes;
    sumSquares += restNumber * restNumber;
    ll crossPairs = totalNumber * totalNumber - sumSquares; 
    finalAnswer[u] = 2LL * (N - 1) + crossPairs;
}

void solveTestCase() {
    cin >> N >> M;
    neighbourList.assign(N + 1, {});
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        neighbourList[A].push_back(B);
        neighbourList[B].push_back(A);
    }

    depthArray.assign(N+1, -1);
    lowArray.assign(N+1, 0);
    parentArray.assign(N+1, -1);
    subtreeSize.assign(N+1, 0);
    finalAnswer.assign(N+1, 0);

    for (int i = 1; i <= N; ++i) {
        if (depthArray[i] == -1) {
            parentArray[i] = -1;
            depthArray[i] = 0; 
            DFS(i);
        }
    }

    for (int i = 1; i <= N; ++i) {
        cout << finalAnswer[i] << endl;
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
