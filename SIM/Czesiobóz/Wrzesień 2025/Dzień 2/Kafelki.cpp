// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    vector<string> stringArray(N);
    for (int i = 0; i < N; i++) cin >> stringArray[i];

    vector<vector<int>> P(N+1, vector<int>(N + 1, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            P[i+1][j+1] = P[i][j+1] + P[i+1][j] - P[i][j] + (stringArray[i][j] == 'B');
        }
    }

    int totalB = P[N][N];

    auto prefixFunction = [&](int row, int column) -> int {
        return P[row][column];
    };

    auto F = [&](ll x, ll y) -> ll {
        if (x < 0 || y < 0) return 0;
        ll fullR = (x + 1) / N;
        int removeR = (x + 1) % N;
        ll fullC = (y + 1) / N;
        int removeC = (y + 1) % N;

        ll finalResult = 0;
        finalResult += fullR * fullC * 1LL * totalB;
        finalResult += fullC * 1LL * prefixFunction(removeR, N);
        finalResult += fullR * 1LL * prefixFunction(N, removeC);
        finalResult += prefixFunction(removeR, removeC);
        return finalResult;
    };

    while (Q--) {
        ll A, B, C, D;
        cin >> A >> B >> C >> D;
        ll answer = F(C, D) - F(A-1, D) - F(C, B-1) + F(A-1, B-1);
        cout << answer << endl;
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
