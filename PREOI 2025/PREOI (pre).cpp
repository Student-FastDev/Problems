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
    int D, T;
    cin >> D >> T;

    vector<long long> maxProfit(1000001, 0LL);

    for(int i = 0; i < D; i++){
        long long dayVariable, profit;
        cin >> dayVariable >> profit;
        if(profit > maxProfit[dayVariable]){
            maxProfit[dayVariable] = profit;
        }
    }

    for(int x = 1; x <= 1000000; x++){
        maxProfit[x] = max(maxProfit[x], maxProfit[x-1]);
    }

    long long totalProfit = 0LL;

    for(int j = 0; j < T; j++){
        long long taskDay, taskCost;
        cin >> taskDay >> taskCost;
        long long profit = maxProfit[taskDay] - taskCost;
        if(profit > 0){
            totalProfit += profit;
        }
    }

    cout << totalProfit << "\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
