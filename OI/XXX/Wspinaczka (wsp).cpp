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
    int N, M, K;
    cin >> N >> M >> K;

    vector<ll> F(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> F[i];
    }

    vector<int> neighbourList(N + 1, 0);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        int differenceValue = v - u;
        if (differenceValue >= 1 && differenceValue <= K) {
            neighbourList[u] |= (1 << (differenceValue - 1));
        }
    }

    int maskSize = 1 << K;
    
    vector<ll> DP(maskSize, 0);    
    vector<ll> nextDP(maskSize);    
    vector<ll> finalResults(N + 1);

    for (int i = N; i >= 1; --i) {
        int currentNeighbour = neighbourList[i];
        ll currentValue = F[i];

        for (int mask = 0; mask < maskSize; ++mask) {
            if (mask & 1) {
                nextDP[mask] = currentValue + DP[currentNeighbour | (mask >> 1)];
            } else {
                nextDP[mask] = DP[mask >> 1];
            }
        }

        swap(DP, nextDP);
        finalResults[i] = DP[1];
    }

    for (int i = 1; i <= N; ++i) {
        cout << finalResults[i] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
