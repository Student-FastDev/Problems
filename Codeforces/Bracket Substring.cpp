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
    int N;
    cin >> N;
    string S;
    cin >> S;
    int M = size(S);

    vector<int> prefixFunction(M);
    for (int i = 1; i < M; ++i) {
        int j = prefixFunction[i - 1];
        while (j > 0 && S[i] != S[j]) j = prefixFunction[j - 1];
        if (S[i] == S[j]) j++;
        prefixFunction[i] = j;
    }

    vector<vector<int>> kmpAutomata(M, vector<int>(2));
    for (int i = 0; i < M; ++i) {
        for (int b = 0; b < 2; ++b) {
            char ch = (b == 0 ? '(' : ')');
            int j = i;
            while (j > 0 && ch != S[j]) j = prefixFunction[j - 1];
            if (ch == S[j]) j++;
            kmpAutomata[i][b] = j;
        }
    }

    int totalLength = 2 * N;
    vector<vector<vector<int>>> dpWithoutS(totalLength + 1, vector<vector<int>>(N + 2, vector<int>(M, 0)));
    dpWithoutS[0][0][0] = 1;

    for (int i = 0; i < totalLength; ++i) {
        for (int j = 0; j <= N; ++j) {
            for (int k = 0; k < M; ++k) {
                if (!dpWithoutS[i][j][k]) continue;
                ll currentValue = dpWithoutS[i][j][k];

                if (j + 1 <= N) {
                    int nextK = kmpAutomata[k][0];
                    if (nextK < M) {
                        dpWithoutS[i + 1][j + 1][nextK] = (dpWithoutS[i + 1][j + 1][nextK] + currentValue) % MOD;
                    }
                }

                if (j > 0) {
                    int nextK = kmpAutomata[k][1];
                    if (nextK < M) {
                        dpWithoutS[i + 1][j - 1][nextK] = (dpWithoutS[i + 1][j - 1][nextK] + currentValue) % MOD;
                    }
                }
            }
        }
    }

    ll countWithoutS = 0;
    for (int k = 0; k < M; ++k) {
        countWithoutS = (countWithoutS + dpWithoutS[totalLength][0][k]) % MOD;
    }

    vector<vector<int>> dpTotalRBS(totalLength + 1, vector<int>(N + 2, 0));
    dpTotalRBS[0][0] = 1;
    for (int i = 0; i < totalLength; ++i) {
        for (int j = 0; j <= N; ++j) {
            if (!dpTotalRBS[i][j]) continue;
            ll currentValue = dpTotalRBS[i][j];

            if (j + 1 <= N) {
                dpTotalRBS[i + 1][j + 1] = (dpTotalRBS[i + 1][j + 1] + currentValue) % MOD;
            }
            if (j > 0) {
                dpTotalRBS[i + 1][j - 1] = (dpTotalRBS[i + 1][j - 1] + currentValue) % MOD;
            }
        }
    }

    ll totalRBSCount = dpTotalRBS[totalLength][0];
    cout << (totalRBSCount - countWithoutS + MOD) % MOD << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}