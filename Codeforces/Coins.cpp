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
    map<char, int> scoreMap;
    scoreMap['A'] = 0;
    scoreMap['B'] = 0;
    scoreMap['C'] = 0;

    for (int i = 0; i < 3; ++i) {
        string comparisonString;
        cin >> comparisonString;
        char characterLeft = comparisonString[0];
        char comparisonSign = comparisonString[1];
        char characterRight = comparisonString[2];

        if (comparisonSign == '>') {
            scoreMap[characterLeft]++;
        } else {
            scoreMap[characterRight]++;
        }
    }

    vector<pair<int, char>> coinList;
    for (auto const& entry : scoreMap) {
        coinList.push_back({entry.second, entry.first});
    }
    sort(all(coinList));

    if (coinList[0].first == 0 && coinList[1].first == 1 && coinList[2].first == 2) {
        cout << coinList[0].second << coinList[1].second << coinList[2].second << endl;
    } else {
        cout << "Impossible" << endl;
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