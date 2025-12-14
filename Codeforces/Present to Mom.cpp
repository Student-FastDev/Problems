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
    int N, M, K;
    if (!(cin >> N >> M >> K)) return;

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> starCenters(N, vector<int>(M, 0));

    for (int rowIndex = 1; rowIndex < N - 1; ++rowIndex) {
        for (int colIndex = 1; colIndex < M - 1; ++colIndex) {
            if (grid[rowIndex][colIndex] == '1' &&
                grid[rowIndex - 1][colIndex] == '1' &&
                grid[rowIndex + 1][colIndex] == '1' &&
                grid[rowIndex][colIndex - 1] == '1' &&
                grid[rowIndex][colIndex + 1] == '1') {
                starCenters[rowIndex][colIndex] = 1;
            }
        }
    }

    ll totalWays = 0;
    vector<int> colSums(M, 0);

    for (int top = 0; top <= N - 3; ++top) {
        fill(all(colSums), 0);

        int initialRow = top + 1;
        for (int colIndex = 0; colIndex < M; ++colIndex)
            colSums[colIndex] += starCenters[initialRow][colIndex];

        for (int bottom = top + 2; bottom < N; ++bottom) {
            int rightIndex = 1;
            int currentSum = 0;

            for (int leftIndex = 1; leftIndex <= M - 2; ++leftIndex) {
                if (rightIndex < leftIndex) {
                    rightIndex = leftIndex;
                    currentSum = 0;
                }
                while (rightIndex <= M - 2 && currentSum < K) {
                    currentSum += colSums[rightIndex];
                    rightIndex++;
                }

                if (currentSum >= K) {
                    totalWays += (ll)(M - rightIndex);
                }
                currentSum -= colSums[leftIndex];
            }

            if (bottom < N - 1) {
                for (int colIndex = 0; colIndex < M; ++colIndex) {
                    colSums[colIndex] += starCenters[bottom][colIndex];
                }
            }
        }
    }

    cout << totalWays << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}