// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    int edgeCount = 2 * M;
    vector<int> headArray(N + 1, -1);
    vector<int> toArray(edgeCount);
    vector<int> nextArray(edgeCount);
    int indexValue = 0;
    auto addEdge = [&](int u, int v){
        toArray[indexValue] = v;
        nextArray[indexValue] = headArray[u];
        headArray[u] = indexValue++;
    };
    
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    
    vector<int> distanceArray(N + 1, -1);
    deque<int> dequeArray;
    distanceArray[1] = 0;
    dequeArray.push_back(1);
    while (!dequeArray.empty()) {
        int u = dequeArray.front(); dequeArray.pop_front();
        for (int e = headArray[u]; e != -1; e = nextArray[e]) {
            int v = toArray[e];
            if (distanceArray[v] == -1) {
                distanceArray[v] = distanceArray[u] + 1;
                dequeArray.push_back(v);
            }
        }
    }
    
    int maxD = 0;
    for (int i = 1; i <= N; ++i) if (distanceArray[i] > maxD) maxD = distanceArray[i];
    bool first = true;
    for (int i = 1; i <= N; ++i) {
        if (distanceArray[i] == maxD) {
            if (!first) cout << ' ';
            cout << i;
            first = false;
        }
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
