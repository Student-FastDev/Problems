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
    
    vector<int> healthArray(N);
    int maxHealth = 0;
    for (int i = 0; i < N; ++i) {
        cin >> healthArray[i];
        maxHealth = max(maxHealth, healthArray[i]);
    }

    vector<int> differenceArray(maxHealth + 2, 0);
    int previousHealth = 0;
    for (int i = 0; i < N; ++i) {
        int currentHealth = healthArray[i];
        if (currentHealth > previousHealth) {
            differenceArray[previousHealth + 1]++;
            differenceArray[currentHealth + 1]--;
        }
        previousHealth = currentHealth;
    }

    vector<int> thresholdCounts(maxHealth + 1, 0);
    int currentCount = 0;
    for (int i = 1; i <= maxHealth; ++i) {
        currentCount += differenceArray[i];
        thresholdCounts[i] = currentCount;
    }

    for (int damage = 1; damage <= maxHealth; ++damage) {
        ll totalSeconds = 0;
        for (int threshold = 1; threshold <= maxHealth; threshold += damage) {
            totalSeconds += thresholdCounts[threshold];
        }
        cout << totalSeconds << (damage == maxHealth ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}