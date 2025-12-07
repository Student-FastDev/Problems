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
    int N, M;
    if (!(cin >> N >> M)) return;

    ll totalCost = 0;
    for (int i = 0; i < N; ++i) {
        ll baseTemp, maxTemp, compensation, busCost;
        cin >> baseTemp >> maxTemp >> compensation >> busCost;

        ll limitL = maxTemp - baseTemp;
        ll currentRegionMin = INF;
        ll valType2Only = busCost + (ll)M * compensation;
        currentRegionMin = min(currentRegionMin, valType2Only);

        if (limitL > 0) {
            ll busesType1 = (M + limitL - 1) / limitL;
            ll valType1Only = busesType1 * busCost;
            currentRegionMin = min(currentRegionMin, valType1Only);

            if (M > limitL) {
                ll remainingStudents = M - limitL - 1;
                
                ll busesNeeded = (remainingStudents + limitL - 1) / limitL; 
                ll valMixed1 = busesNeeded * busCost + busCost + (limitL + 1) * compensation;
                currentRegionMin = min(currentRegionMin, valMixed1);

                ll fullBuses = remainingStudents / limitL;
                ll valMixed2 = fullBuses * busCost + busCost + (M - fullBuses * limitL) * compensation;
                currentRegionMin = min(currentRegionMin, valMixed2);
            }
        }
        totalCost += currentRegionMin;
    }
    cout << totalCost << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}