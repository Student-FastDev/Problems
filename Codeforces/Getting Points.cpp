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
    ll N, P, L, T;
    cin >> N >> P >> L >> T;

    ll numberOfTasks = (N - 1) / 7 + 1;

    ll lowValue = 1;
    ll highValue = N;
    ll minStudyDays = N;

    while (lowValue <= highValue) {
        ll midValue = lowValue + (highValue - lowValue) / 2;
        ll currentPoints = midValue * L + min(2 * midValue, numberOfTasks) * T;
        if (currentPoints >= P) {
            minStudyDays = midValue;
            highValue = midValue - 1;
        } else {
            lowValue = midValue + 1;
        }
    }

    cout << N - minStudyDays << endl;
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