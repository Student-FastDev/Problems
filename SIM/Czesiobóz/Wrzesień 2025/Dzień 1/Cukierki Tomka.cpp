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

    vector<int> T(N + 1);
    vector<long long> K(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> T[i] >> K[i];
    }

    unordered_map<long long, vector<int>> stacksArray;
    stacksArray.reserve(N*2);
    stacksArray.max_load_factor(0.7);

    vector<int> eventsArray(N + 2, 0);
    bool isPossible = true;

    for (int i = 1; i <= N; i++) {
        if (T[i] == 1) {
            stacksArray[K[i]].push_back(i);
        } else {
            auto &element = stacksArray[K[i]];
            if (element.empty()) {
                isPossible = false;
                break;
            }
            int buyDay = element.back();
            element.pop_back();
            eventsArray[buyDay] += 1;
            eventsArray[i] -= 1;
        }
    }

    if (!isPossible) {
        cout << -1 << endl;
        return;
    }

    int currentValue = 0, maxValue = 0;
    for (int d = 1; d <= N; d++) {
        currentValue += eventsArray[d];
        maxValue = max(maxValue, currentValue);
    }

    cout << maxValue << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
