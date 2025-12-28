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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> gridMatrix(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> gridMatrix[i][j];
        }
    }

    vector<vector<int>> minDifferenceMatrix(N, vector<int>(N, 2e9));
    vector<vector<int>> wrapDifferenceMatrix(N, vector<int>(N, 2e9));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int minimumValue = 2e9;
            for (int k = 0; k < M; ++k) {
                minimumValue = min(minimumValue, abs(gridMatrix[i][k] - gridMatrix[j][k]));
            }
            minDifferenceMatrix[i][j] = minimumValue;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int minimumValue = 2e9;
            for (int k = 0; k < M - 1; ++k) {
                minimumValue = min(minimumValue, abs(gridMatrix[i][k] - gridMatrix[j][k + 1]));
            }
            wrapDifferenceMatrix[i][j] = minimumValue;
        }
    }

    vector<int> dpArray((1 << N) * N);

    auto checkCondition = [&](int thresholdK) -> bool {
        fill(all(dpArray), 0);
        for (int i = 0; i < N; ++i) dpArray[(1 << i) * N + i] = (1 << i);

        for (int currentMask = 1; currentMask < (1 << N); ++currentMask) {
            for (int lastRow = 0; lastRow < N; ++lastRow) {
                int startRowsMask = dpArray[currentMask * N + lastRow];
                if (!startRowsMask) continue;

                for (int nextRow = 0; nextRow < N; ++nextRow) {
                    if (!((currentMask >> nextRow) & 1)) {
                        if (minDifferenceMatrix[lastRow][nextRow] >= thresholdK) {
                            dpArray[(currentMask | (1 << nextRow)) * N + nextRow] |= startRowsMask;
                        }
                    }
                }
            }
        }

        int fullMask = (1 << N) - 1;
        for (int lastRow = 0; lastRow < N; ++lastRow) {
            int startRowsMask = dpArray[fullMask * N + lastRow];
            if (!startRowsMask) continue;
            for (int startRow = 0; startRow < N; ++startRow) {
                if ((startRowsMask >> startRow) & 1) {
                    if (wrapDifferenceMatrix[lastRow][startRow] >= thresholdK) return true;
                }
            }
        }
        return false;
    };

    int lowValue = 0, highValue = 1000000000, answer = 0;
    while (lowValue <= highValue) {
        int midValue = lowValue + (highValue - lowValue) / 2;
        if (checkCondition(midValue)) {
            answer = midValue;
            lowValue = midValue + 1;
        } else {
            highValue = midValue - 1;
        }
    }
    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}