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

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    vector<pair<int,int>> edgesArray;
    edgesArray.reserve(M);

    for (int i = 0; i < M; i++) {
        int U, V;
        cin >> U >> V;
        edgesArray.emplace_back(U, V);
    }

    vector<char> isNeighborOf1(N + 1, 0);
    for (auto &e : edgesArray) {
        int U = e.first, V = e.second;
        if (U == 1) isNeighborOf1[V] = 1;
        else if (V == 1) isNeighborOf1[U] = 1;
    }

    for (auto &e : edgesArray) {
        int U = e.first, V = e.second;
        if (U != 1 && V != 1 && isNeighborOf1[U] && isNeighborOf1[V]) {
            cout << "TAK" << endl;
            return;
        }
    }

    cout << "NIE" << endl;
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}