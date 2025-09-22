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
    cin >> N;
    vector<ll> numberArray(N);
    for (int i = 0; i < N; ++i) cin >> numberArray[i];
    if (N == 0) { cout << 0 << endl; return; }

    ll bestValue = -INF;
    for (int i = 0; i < N; ++i) bestValue = max(bestValue, numberArray[i]);

    if (N >= 2) {
        for (int i = 0; i + 1 < N; ++i) bestValue = max(bestValue, numberArray[i] + numberArray[i + 1] - 1);
    }

    if (N >= 3) {
        ll prefixValue = numberArray[0] + 1;
        ll currentM = -INF;
        for (int j = 1; j < N; ++j) {
            ll temporaryM = prefixValue + numberArray[j];
            if (temporaryM > currentM) currentM = temporaryM;
            int C = j + 1;
            if (C < N) {
                ll currentCandidate = currentM + numberArray[C] - (C + 1);
                if (currentCandidate > bestValue) bestValue = currentCandidate;
            }
            prefixValue = max(prefixValue, numberArray[j] + (j + 1));
        }
    }

    cout << bestValue << endl;
    return;
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