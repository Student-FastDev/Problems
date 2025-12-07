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
    int N;
    ll K;
    cin >> N >> K;

    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<ll> B(N);
    for (int i = 0; i < N; ++i) cin >> B[i];
    if (K % 2 == 0) {
        for (int i = 0; i < N; ++i) B[i] = 0;
    }

    vector<ll> P(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        P[i + 1] = P[i] + A[i];
    }

    vector<ll> minPrefix(N);
    ll currentMin = P[0];
    for (int i = 0; i < N; ++i) {
        if (P[i] < currentMin) currentMin = P[i];
        minPrefix[i] = currentMin;
    }

    vector<ll> suffixMax(N);
    ll currentMax = -INF;
    for (int i = N - 1; i >= 0; --i) {
        if (P[i + 1] > currentMax) currentMax = P[i + 1];
        suffixMax[i] = currentMax;
    }

    ll finalAnswer = -INF;
    for (int i = 0; i < N; ++i) {
        ll value = suffixMax[i] - minPrefix[i] + B[i];
        if (value > finalAnswer) finalAnswer = value;
    }

    cout << finalAnswer << endl;
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
