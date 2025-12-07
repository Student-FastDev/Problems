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

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int rowSum1, rowSum2;
    int columnSum1, columnSum2;
    int diagonalSum1, diagonalSum2;

    cin >> rowSum1 >> rowSum2;
    cin >> columnSum1 >> columnSum2;
    cin >> diagonalSum1 >> diagonalSum2;

    for (int topLeft = 1; topLeft <= 9; ++topLeft) {
        int topRight = rowSum1 - topLeft;
        int bottomLeft = columnSum1 - topLeft;
        int bottomRight = diagonalSum1 - topLeft;

        if (topRight < 1 || topRight > 9) continue;
        if (bottomLeft < 1 || bottomLeft > 9) continue;
        if (bottomRight < 1 || bottomRight > 9) continue;

        if (topLeft == topRight || topLeft == bottomLeft || topLeft == bottomRight ||
            topRight == bottomLeft || topRight == bottomRight || bottomLeft == bottomRight) continue;

        if (bottomLeft + bottomRight != rowSum2) continue;
        if (topRight + bottomRight != columnSum2) continue;
        if (topRight + bottomLeft != diagonalSum2) continue;

        cout << topLeft << " " << topRight << endl;
        cout << bottomLeft << " " << bottomRight << endl;
        return;
    }

    cout << -1 << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}