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
    int countZero = 0;
    int countOne = 0;
    int countOthers = 0;
    for (int i = 0; i < N; ++i) {
        int currentValue;
        cin >> currentValue;
        if (currentValue == 0) countZero++;
        else if (currentValue == 1) countOne++;
        else countOthers++;
    }

    int countNonZero = N - countZero;

    if (countZero <= countNonZero + 1) {
        cout << 0 << endl;
    } else {
        if (countOne == 0 || countOthers > 0) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
        }
    }
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