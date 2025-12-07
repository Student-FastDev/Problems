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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7; // 998244353

void solveTestCase() {
    ll N, K;
    cin >> N >> K;

    ll totalSteps = 0;
    while (N > 0) {
        if (N % K == 0) {
            N /= K;
            totalSteps++;
        } else {
            ll remainderValue = N % K;
            totalSteps += remainderValue;
            N -= remainderValue;
        }
    }
    cout << totalSteps << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}