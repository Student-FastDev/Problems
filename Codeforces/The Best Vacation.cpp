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

ll getSum(ll n) {
    return n * (n + 1) / 2;
}

void solveTestCase() {
    ll N, X;
    cin >> N >> X;

    vector<ll> daysInMonth(N);
    for (int i = 0; i < N; ++i) cin >> daysInMonth[i];

    vector<ll> doubledDays = daysInMonth;
    doubledDays.insert(doubledDays.end(), all(daysInMonth));

    ll currentDays = 0;
    ll currentHugs = 0;
    ll maxHugs = 0;
    int leftIndex = 0;

    for (int rightIndex = 0; rightIndex < 2 * N; ++rightIndex) {
        currentDays += doubledDays[rightIndex];
        currentHugs += getSum(doubledDays[rightIndex]);

        while (currentDays > X) {
            currentDays -= doubledDays[leftIndex];
            currentHugs -= getSum(doubledDays[leftIndex]);
            leftIndex++;
        }

        ll windowHugs = currentHugs;
        ll needed = X - currentDays;

        if (needed > 0) {
            if (leftIndex > 0) {
                ll previousMonthDays = doubledDays[leftIndex - 1];
                windowHugs += (getSum(previousMonthDays) - getSum(previousMonthDays - needed));
            } else {
                continue;
            }
        }
        maxHugs = max(maxHugs, windowHugs);
    }

    cout << maxHugs << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    // cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}