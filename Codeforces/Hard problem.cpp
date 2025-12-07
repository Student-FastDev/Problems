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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 1e18;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int stringCount;
    cin >> stringCount;

    vector<ll> costs(stringCount);
    for (int i = 0; i < stringCount; ++i) {
        cin >> costs[i];
    }

    vector<string> stringsArray(stringCount);
    vector<string> reversedStringsArray(stringCount);
    for (int i = 0; i < stringCount; ++i) {
        cin >> stringsArray[i];
        reversedStringsArray[i] = stringsArray[i];
        reverse(all(reversedStringsArray[i]));
    }

    vector<vector<ll>> minCost(stringCount, vector<ll>(2, INF));

    minCost[0][0] = 0;
    minCost[0][1] = costs[0];

    for (int i = 1; i < stringCount; ++i) {
        if (stringsArray[i] >= stringsArray[i - 1] && minCost[i - 1][0] != INF) {
            minCost[i][0] = min(minCost[i][0], minCost[i - 1][0]);
        }
        if (stringsArray[i] >= reversedStringsArray[i - 1] && minCost[i - 1][1] != INF) {
            minCost[i][0] = min(minCost[i][0], minCost[i - 1][1]);
        }

        if (reversedStringsArray[i] >= stringsArray[i - 1] && minCost[i - 1][0] != INF) {
            minCost[i][1] = min(minCost[i][1], minCost[i - 1][0] + costs[i]);
        }
        if (reversedStringsArray[i] >= reversedStringsArray[i - 1] && minCost[i - 1][1] != INF) {
            minCost[i][1] = min(minCost[i][1], minCost[i - 1][1] + costs[i]);
        }
    }

    ll finalAnswer = min(minCost[stringCount - 1][0], minCost[stringCount - 1][1]);

    if (finalAnswer == INF) {
        cout << -1 << endl;
    } else {
        cout << finalAnswer << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}