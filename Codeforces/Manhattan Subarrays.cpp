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

bool isBadTriple(ll a, ll b, ll c) {
    return (a <= b && b <= c) || (a >= b && b >= c);
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    ll goodSubarraysCount = 0;

    for (int i = 0; i < N; ++i) {
        for (int length = 1; length <= 4; ++length) {
            if (i + length > N) break;
            
            bool isGoodSubarray = true;
            for (int p = 0; p < length; ++p) {
                for (int q = p + 1; q < length; ++q) {
                    for (int r = q + 1; r < length; ++r) {
                        if (isBadTriple(A[i + p], A[i + q], A[i + r])) {
                            isGoodSubarray = false;
                            break;
                        }
                    }
                    if (!isGoodSubarray) break;
                }
                if (!isGoodSubarray) break;
            }

            if (isGoodSubarray) goodSubarraysCount++;
        }
    }

    cout << goodSubarraysCount << endl;
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