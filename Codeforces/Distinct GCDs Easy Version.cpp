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

int N;
int K;
vector<ll> valuesArray;
int neighbourList[100][100];
vector<int> pathTrack; 

void DFS(int u) {
    for (int v = 0; v < K; ++v) {
        if (neighbourList[u][v] > 0) {
            neighbourList[u][v]--;
            if (u != v) neighbourList[v][u]--;            
            DFS(v);
        }
    }
    pathTrack.push_back(u);
}

void solveTestCase() {
    cin >> N;

    if (N == 1) {
        cout << "1" << endl;
        return;
    }

    K = 1;
    while (true) {
        int maxEdges = K * (K + 1) / 2;
        if (K % 2 == 0) maxEdges -= (K - 2) / 2;
        if (maxEdges >= N - 1) break;
        K++;
    }

    valuesArray.clear();
    for (int i = 0; i < K; ++i) {
        ll currentValue = 1;
        for (int p = 0; p < i; ++p) currentValue *= 2;
        for (int p = 0; p < K - 1 - i; ++p) currentValue *= 3;
        valuesArray.push_back(currentValue);
    }

    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            neighbourList[i][j] = 0;
        }
    }
    for (int i = 0; i < K; ++i) {
        for (int j = i; j < K; ++j) {
            neighbourList[i][j] = 1;
            neighbourList[j][i] = 1;
        }
    }

    int startNode = 0;
    if (K % 2 == 0) {
        int removePairs = (K - 2) / 2;
        for (int i = 0; i < removePairs; ++i) {
            int u = 2 * i;
            int v = 2 * i + 1;
            neighbourList[u][v] = 0;
            neighbourList[v][u] = 0;
        }
        startNode = 2 * removePairs;
    }

    pathTrack.clear();
    DFS(startNode);

    for (int i = 0; i < N; ++i) {
        cout << valuesArray[pathTrack[i]] << (i == N - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
