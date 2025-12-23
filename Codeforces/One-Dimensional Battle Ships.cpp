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
    int N, K, A;
    cin >> N >> K >> A;
    int M;
    cin >> M;

    set<int> blockedCells;
    blockedCells.insert(0);
    blockedCells.insert(N + 1);

    int maxShips = (N + 1) / (A + 1);

    for (int i = 1; i <= M; ++i) {
        int shotPosition;
        cin >> shotPosition;

        auto blockIterator = blockedCells.upper_bound(shotPosition);
        int rightBoundary = *blockIterator;
        int leftBoundary = *prev(blockIterator);

        int oldSegmentLength = rightBoundary - leftBoundary - 1;
        int leftSegmentLength = shotPosition - leftBoundary - 1;
        int rightSegmentLength = rightBoundary - shotPosition - 1;

        maxShips -= (oldSegmentLength + 1) / (A + 1);
        maxShips += (leftSegmentLength + 1) / (A + 1);
        maxShips += (rightSegmentLength + 1) / (A + 1);

        blockedCells.insert(shotPosition);

        if (maxShips < K) {
            cout << i << endl;
            return;
        }
    }

    cout << -1 << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}