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
    ll leftMoves, rightMoves, downMoves, upMoves;
    cin >> leftMoves >> rightMoves >> downMoves >> upMoves;

    ll startX, startY, boxX1, boxY1, boxX2, boxY2;
    cin >> startX >> startY >> boxX1 >> boxY1 >> boxX2 >> boxY2;

    ll finalX = startX - leftMoves + rightMoves;
    ll finalY = startY - downMoves + upMoves;

    bool isPositionValid = (finalX >= boxX1 && finalX <= boxX2 && finalY >= boxY1 && finalY <= boxY2);
    
    if (!isPositionValid) {
        cout << "No" << endl;
        return;
    }

    if (leftMoves > 0 && rightMoves > 0 && boxX1 == boxX2) {
        cout << "No" << endl;
        return;
    }

    if (downMoves > 0 && upMoves > 0 && boxY1 == boxY2) {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}