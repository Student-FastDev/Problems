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

ll baseKAdd(ll valA, ll valB, int baseK) {
    ll result = 0;
    ll multiplier = 1;
    while (valA > 0 || valB > 0) {
        int digitA = valA % baseK;
        int digitB = valB % baseK;
        int currentDigit = (digitA + digitB) % baseK;
        result += currentDigit * multiplier;
        valA /= baseK;
        valB /= baseK;
        multiplier *= baseK;
    }
    return result;
}

ll baseKSub(ll valA, ll valB, int baseK) {
    ll result = 0;
    ll multiplier = 1;
    while (valA > 0 || valB > 0) {
        int digitA = valA % baseK;
        int digitB = valB % baseK;
        int currentDigit = (digitA - digitB + baseK) % baseK;
        result += currentDigit * multiplier;
        valA /= baseK;
        valB /= baseK;
        multiplier *= baseK;
    }
    return result;
}

void solveTestCase() {
    int N, K;
    cin >> N >> K;

    ll currentValue = 0;
    for (int i = 0; i < N; ++i) {
        ll guessValue;
        if (i % 2 == 0) {
            guessValue = baseKAdd(currentValue, i, K);
        } else {
            guessValue = baseKSub(currentValue, i, K);
        }

        cout << guessValue << endl;
        cout.flush();

        int response;
        cin >> response;
        if (response == 1) return;
        if (response == -1) exit(0);

        currentValue = baseKSub(guessValue, currentValue, K);
    }
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