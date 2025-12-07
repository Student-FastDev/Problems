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
const ll MOD = 1e9+7; 

void solveTestCase() {
    ll K, D, T;
    cin >> K >> D >> T;

    ll cycleDuration = ((K + D - 1) / D) * D;
    ll cookedAmountPerCycleDoubled = 2 * K + (cycleDuration - K); 
    ll totalCookingNeededDoubled = 2 * T;

    ll numberOfFullCycles = totalCookingNeededDoubled / cookedAmountPerCycleDoubled;
    ll remainingCookingNeededDoubled = totalCookingNeededDoubled % cookedAmountPerCycleDoubled;

    double finalTime = (double)numberOfFullCycles * cycleDuration;

    if (remainingCookingNeededDoubled <= 2 * K) {
        finalTime += (double)remainingCookingNeededDoubled / 2.0;
    } else {
        finalTime += K;
        remainingCookingNeededDoubled -= 2 * K;
        finalTime += remainingCookingNeededDoubled;
    }

    cout << fixed << setprecision(9) << finalTime << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}