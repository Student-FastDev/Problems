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
    vector<string> craftingGrid(3);
    for (int i = 0; i < 3; ++i) {
        cin >> craftingGrid[i];
    }

    vector<vector<string>> swordString = {
        {".#.", ".#.", ".|."}
    };

    vector<vector<string>> pickaxeString = {
        {"###", ".|.", ".|."}
    };

    vector<vector<string>> axeString = {
        {"##.", "#|.", ".|."},
        {".##", ".|#", ".|."}
    };

    auto matches = [&](const vector<string>& pattern) {
        for (int i = 0; i < 3; ++i)
            if (craftingGrid[i] != pattern[i])
                return false;
        return true;
    };

    if (matches(swordString[0])) {
        cout << "MIECZ" << endl;
    } else if (matches(pickaxeString[0])) {
        cout << "KILOF" << endl;
    } else if (matches(axeString[0]) || matches(axeString[1])) {
        cout << "SIEKIERA" << endl;
    } else {
        cout << "NIE" << endl;
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
