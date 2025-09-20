// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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
    vector<long long> P(N);
    for (int i = 0; i < N; ++i) cin >> P[i];
    sort(P.begin(), P.end());
    long long lastValue = LLONG_MIN / 4;
    int finalAnswer = 0;
    for (int i = 0; i < N; ++i) {
        long long a = P[i] - 1;
        long long b = P[i];
        long long c = P[i] + 1;
        if (a > lastValue) {
            lastValue = a;
            ++finalAnswer;
        } else if (b > lastValue) {
            lastValue = b;
            ++finalAnswer;
        } else if (c > lastValue) {
            lastValue = c;
            ++finalAnswer;
        }
    }
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
