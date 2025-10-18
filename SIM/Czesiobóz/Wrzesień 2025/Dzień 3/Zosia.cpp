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
    ll N, M;
    long long K;
    cin >> N >> M >> K;

    if(N == M){
        cout << -1 << endl;
        return;
    }

    ll G = __gcd(N, M);
    ll LCM = (ll)(N / G) * (ll)M;

    auto countFunction = [&](ll x)->ll{
        ll a = x / N;
        ll b = x / M;
        ll c = x / LCM;
        return a + b - 2*c;
    };

    ll leftRange = 1;
    ll rightRange = (ll)max(N,M) * (ll)K;

    while(leftRange < rightRange){
        ll middleValue = (leftRange + rightRange) / 2;
        if(countFunction(middleValue) < (ll)K) leftRange = middleValue + 1;
        else rightRange = middleValue;
    }

    ll finalAnswer = leftRange;
    cout << finalAnswer << endl;
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
