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
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

struct Line {
    ll slope, yIntercept;
    ll eval(ll x) const { return slope * x + yIntercept; }
};

void solveTestCase() {
    int numberOfTrees;
    cin >> numberOfTrees;

    vector<ll> treeHeights(numberOfTrees), rechargeCosts(numberOfTrees);
    for (int i = 0; i < numberOfTrees; ++i) cin >> treeHeights[i];
    for (int i = 0; i < numberOfTrees; ++i) cin >> rechargeCosts[i];

    if (numberOfTrees == 1) {
        cout << 0 << endl;
        return;
    }

    deque<Line> linesDeque;
    linesDeque.push_back({rechargeCosts[0], 0});

    ll minimumCost = 0;

    for (int i = 1; i < numberOfTrees; ++i) {
        while (size(linesDeque) >= 2 && linesDeque[0].eval(treeHeights[i]) >= linesDeque[1].eval(treeHeights[i])) {
            linesDeque.pop_front();
        }

        minimumCost = linesDeque[0].eval(treeHeights[i]);

        Line newLine = {rechargeCosts[i], minimumCost};

        while (size(linesDeque) >= 2) {
            const Line& lastLine = linesDeque.back();
            const Line& secondLastLine = linesDeque[size(linesDeque) - 2];

            __int128 numeratorLeft = (__int128)(lastLine.yIntercept - secondLastLine.yIntercept);
            __int128 denominatorLeft = (__int128)(secondLastLine.slope - lastLine.slope);
            __int128 numeratorRight = (__int128)(newLine.yIntercept - lastLine.yIntercept);
            __int128 denominatorRight = (__int128)(lastLine.slope - newLine.slope);

            if (numeratorLeft * denominatorRight >= numeratorRight * denominatorLeft) {
                linesDeque.pop_back();
            } else {
                break;
            }
        }
        linesDeque.push_back(newLine);
    }

    cout << minimumCost << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}