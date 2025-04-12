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

const ll INF = INT_MAX / 2;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, K;
    cin >> N >> K;
    vector<int> horseColors(N);
    for(int i = 0; i < N; i++) {
        bool tempColor;
        cin >> tempColor;
        horseColors[i] = tempColor;
    }

    vector<int> prefixSums(N + 1, 0);
    for(int i = 0; i < N; i++) {
        prefixSums[i + 1] = prefixSums[i] + horseColors[i];
    }

    vector<vector<int>> DP(N + 1, vector<int>(K + 1, INF));
    DP[0][0] = 0;

    for(int j = 1; j <= K; j++) {
        for(int i = 1; i <= N; i++) {
            if(i < j) continue;
            for(int k = j - 1; k < i; k++) {
                int currentBlack = prefixSums[i] - prefixSums[k];
                int currentWhite = (i - k) - currentBlack;
                int costValue = currentBlack * currentWhite;
                if(DP[k][j - 1] + costValue < DP[i][j]) {
                    DP[i][j] = DP[k][j - 1] + costValue;
                }
            }
        }
    }

    cout << DP[N][K] << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
