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
    ll N, H, K;
    cin >> N >> H >> K;
    
    vector<ll> A(N);
    ll S = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        S += A[i];
    }

    ll M = (H - 1) / S;
    ll remainingValue = H - M * S;

    vector<ll> prefixMinimum(N);
    prefixMinimum[0] = A[0];
    for (int i = 1; i < N; ++i) prefixMinimum[i] = min(prefixMinimum[i - 1], A[i]);

    vector<ll> suffixMaximum(N);
    suffixMaximum[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; --i) suffixMaximum[i] = max(suffixMaximum[i + 1], A[i]);

    ll P = 0;
    ll bestValue = N;
    
    for (int x = 1; x <= N; ++x) {
        P += A[x - 1];
        ll maximumP = P;
        
        if (x < N) {
            ll currentGain = suffixMaximum[x] - prefixMinimum[x - 1];
            if (currentGain > 0) maximumP += currentGain;
        }
        
        if (maximumP >= remainingValue) {
            bestValue = x;
            break;
        }
    }

    ll finalAnswer = M * (N + K) + bestValue;
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
