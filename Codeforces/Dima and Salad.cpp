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

const int OFFSET = 100000;
const int RANGE_SIZE = 200005;

void solveTestCase() {
    int N, K;
    cin >> N >> K;

    vector<int> tasteArray(N);
    for (int i = 0; i < N; ++i) cin >> tasteArray[i];

    vector<int> caloriesArray(N);
    for (int i = 0; i < N; ++i) cin >> caloriesArray[i];

    vector<int> dpArray(RANGE_SIZE, -1);
    dpArray[OFFSET] = 0;

    for (int i = 0; i < N; ++i) {
        int taste = tasteArray[i];
        int calories = caloriesArray[i];
        int balance = taste - K * calories;

        vector<int> nextDpArray = dpArray;
        for (int j = 0; j < RANGE_SIZE; ++j) {
            if (dpArray[j] == -1) continue;
            int nextIndex = j + balance;
            if (nextIndex >= 0 && nextIndex < RANGE_SIZE) {
                nextDpArray[nextIndex] = max(nextDpArray[nextIndex], dpArray[j] + taste);
            }
        }
        dpArray = nextDpArray;
    }

    if (dpArray[OFFSET] <= 0) {
        cout << -1 << endl;
    } else {
        cout << dpArray[OFFSET] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}