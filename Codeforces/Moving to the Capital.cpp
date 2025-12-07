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

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> neighbourList(N + 1);
    for(int i = 0; i < M; ++i) {
        int U, V;
        cin >> U >> V;
        neighbourList[U].push_back(V);
    }

    vector<int> distanceArray(N + 1, -1);
    queue<int> bfsQueue;

    distanceArray[1] = 0;
    bfsQueue.push(1);

    while(!bfsQueue.empty()) {
        int U = bfsQueue.front();
        bfsQueue.pop();

        for(int v : neighbourList[U]) {
            if(distanceArray[v] == -1) {
                distanceArray[v] = distanceArray[U] + 1;
                bfsQueue.push(v);
            }
        }
    }

    vector<vector<int>> nodesByDistance(N);
    for(int i = 1; i <= N; ++i) {
        if (distanceArray[i] != -1) {
            nodesByDistance[distanceArray[i]].push_back(i);
        }
    }

    vector<int> dpValues(N + 1);

    for(int d = N - 1; d >= 0; --d) {
        for(int u : nodesByDistance[d]) {
            dpValues[u] = distanceArray[u];
            for(int v : neighbourList[u]) {
                if(distanceArray[u] < distanceArray[v]) {
                    dpValues[u] = min(dpValues[u], dpValues[v]);
                } else {
                    dpValues[u] = min(dpValues[u], distanceArray[v]);
                }
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        cout << dpValues[i] << (i == N ? "" : " ");
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