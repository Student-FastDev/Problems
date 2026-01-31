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
    ll H;
    cin >> N >> H;

    priority_queue<ll> queueL;
    priority_queue<ll, vector<ll>, greater<ll>> queueR;

    ll lazyL = 0;
    ll lazyR = 0;
    
    ll minCost = 0;

    for (int i = 0; i < N; ++i) {
        ll S;
        cin >> S;

        if (i > 0) {
            lazyL -= H;
            lazyR += H;
        }

        queueL.push(S - lazyL);
        queueR.push(S - lazyR);

        ll l = queueL.top() + lazyL;
        ll r = queueR.top() + lazyR;

        if (l > r) {
            minCost += (l - r);

            queueL.pop();
            queueR.pop();

            queueL.push(r - lazyL);
            queueR.push(l - lazyR);
        }
    }

    cout << minCost << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}