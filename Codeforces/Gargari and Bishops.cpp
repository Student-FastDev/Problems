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
    int N;
    cin >> N;

    vector<vector<ll>> chessboardMatrix(N, vector<ll>(N));
    vector<ll> mainDiagonalSums(2 * N + 5, 0);
    vector<ll> antiDiagonalSums(2 * N + 5, 0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> chessboardMatrix[i][j];
            mainDiagonalSums[i - j + N] += chessboardMatrix[i][j];
            antiDiagonalSums[i + j] += chessboardMatrix[i][j];
        }
    }

    ll bestWhiteScore = -1;
    int bestWhiteRow = 1, bestWhiteColumn = 1;

    ll bestBlackScore = -1;
    int bestBlackRow = 1, bestBlackColumn = 2;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ll currentScore = mainDiagonalSums[i - j + N] + antiDiagonalSums[i + j] - chessboardMatrix[i][j];
            
            if ((i + j) % 2 == 0) {
                if (currentScore > bestWhiteScore) {
                    bestWhiteScore = currentScore;
                    bestWhiteRow = i + 1;
                    bestWhiteColumn = j + 1;
                }
            } else {
                if (currentScore > bestBlackScore) {
                    bestBlackScore = currentScore;
                    bestBlackRow = i + 1;
                    bestBlackColumn = j + 1;
                }
            }
        }
    }

    cout << bestWhiteScore + bestBlackScore << endl;
    cout << bestWhiteRow << " " << bestWhiteColumn << " " << bestBlackRow << " " << bestBlackColumn << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}