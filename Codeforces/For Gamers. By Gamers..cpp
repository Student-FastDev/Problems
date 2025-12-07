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
    int numberOfUnitTypes;
    ll maxCoins;
    cin >> numberOfUnitTypes >> maxCoins;

    vector<ll> maxBasePower(maxCoins + 1, 0);

    for(int i = 0; i < numberOfUnitTypes; ++i) {
        ll cost, damage, health;
        cin >> cost >> damage >> health;
        if(cost <= maxCoins) {
            maxBasePower[cost] = max(maxBasePower[cost], damage * health);
        }
    }

    vector<ll> bestPower(maxCoins + 1, 0);

    for(int i = 1; i <= maxCoins; ++i) {
        if(maxBasePower[i] == 0) continue;
        for(int j = i; j <= maxCoins; j += i) {
            ll currentPower = maxBasePower[i] * (j / i);
            if(currentPower > bestPower[j]) {
                bestPower[j] = currentPower;
            }
        }
    }

    for(int i = 1; i <= maxCoins; ++i) {
        if(bestPower[i-1] > bestPower[i]) {
            bestPower[i] = bestPower[i-1];
        }
    }

    int numberOfMonsters;
    cin >> numberOfMonsters;

    for(int i = 0; i < numberOfMonsters; ++i) {
        ll monsterDamage, monsterHealth;
        cin >> monsterDamage >> monsterHealth;
        ll requiredPower = monsterDamage * monsterHealth;

        auto iterator = upper_bound(all(bestPower), requiredPower);
        
        if(iterator == bestPower.end()) {
            cout << -1 << (i == numberOfMonsters - 1 ? "" : " ");
        } else {
            cout << (iterator - bestPower.begin()) << (i == numberOfMonsters - 1 ? "" : " ");
        }
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solveTestCase();
    return 0;
}