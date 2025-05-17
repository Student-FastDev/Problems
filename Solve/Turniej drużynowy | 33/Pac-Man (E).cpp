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

const ll INF = 1000000007;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, K;
    cin >> N >> K;
    vector<string> gridArray(N);
    for (int i = 0; i < N; i++) cin >> gridArray[i];

    vector<pii> sourceArray(K + 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char C = gridArray[i][j];
            if (C >= '1' && C <= '9') {
                int indexValue = C - '0';
                sourceArray[indexValue] = {i, j};
            }
        }
    }

    vector<int> speedArray(K + 1);
    for (int i = 1; i <= K; ++i) cin >> speedArray[i];

    vector<vector<vector<int>>> distanceArray(K + 1, vector<vector<int>>(N, vector<int>(N, INF)));
    int dX[4] = { -1, 1, 0, 0 };
    int dY[4] = { 0, 0, -1, 1 };

    for (int i = 1; i <= K; i++) {
        auto &D = distanceArray[i];
        queue<pii> Q;
        auto [sX, sY] = sourceArray[i];
        D[sX][sY] = 0;
        Q.push({ sX, sY });
        while (!Q.empty()) {
            auto [X, Y] = Q.front(); Q.pop();
            for (int directionValue = 0; directionValue < 4; directionValue++) {
                int nX = X + dX[directionValue];
                int nY = Y + dY[directionValue];
                if (nX < 0 || nX >= N || nY < 0 || nY >= N) continue;
                if (gridArray[nX][nY] == '#') continue;
                if (D[nX][nY] > D[X][Y] + 1) {
                    D[nX][nY] = D[X][Y] + 1;
                    Q.push({ nX, nY });
                }
            }
        }
    }

    bool anyUnreachable = false;
    int bestTime = 0;

    for (int i = 0; i < N && !anyUnreachable; i++) {
        for (int j = 0; j < N; j++) {
            if (gridArray[i][j] != '.') continue;
            int minTime = INF;
            for (int k = 1; k <= K; ++k) {
                int D = distanceArray[k][i][j];
                if (D == INF) continue;
                int T = (D + speedArray[k] - 1) / speedArray[k];
                minTime = min(minTime, T);
            }
            if (minTime == INF) {
                anyUnreachable = true;
                break;
            }
            bestTime = max(bestTime, minTime);
        }
    }

    if (anyUnreachable) cout << "NIE" << endl;
    else cout << bestTime << endl;
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