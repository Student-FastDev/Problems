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

    vector<int> X(N), Y(N);
    for (int i = 0; i < N; i++) {
        X[i] = i + 1;
        Y[i] = 0;
    }

    int headValue = 0;

    while (Q--) {
        int queryType;
        cin >> queryType;
        if (queryType == 1) {
            char C;
            cin >> C;
            int dX = 0, dY = 0;
            if (C == 'G') dY = 1;
            else if (C == 'D') dY = -1;
            else if (C == 'P') dX = 1;
            else if (C == 'L') dX = -1;

            int nX = X[headValue] + dX;
            int nY = Y[headValue] + dY;

            headValue = (headValue - 1 + N) % N;
            X[headValue] = nX;
            Y[headValue] = nY;
        } else {
            int S;
            cin >> S;
            int indexValue = (headValue + S - 1) % N;
            cout << X[indexValue] << " " << Y[indexValue] << endl;
        }
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
