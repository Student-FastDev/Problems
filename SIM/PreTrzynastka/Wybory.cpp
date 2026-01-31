// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto currentPoint)->decltype(currentPoint.first,o){return o<<'('<<currentPoint.first<<", "<<currentPoint.second <<')';}
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

const int K = 2500;
const int OFFSET = 2505;
const int GRID_SIZE = 5010;

short distanceGrid[GRID_SIZE][GRID_SIZE];

struct Point {
    short x, y;
};

ll arithmeticSum(ll L, ll R, int currentParity) {
    if (L > R) return 0;
    
    ll start = L;
    if (start % 2 != currentParity) start++;
    
    ll end = R;
    if (end % 2 != currentParity) end--;
    
    if (start > end) return 0;
    
    ll count = (end - start) / 2 + 1;
    return 2 * count * (start + end);
}

void solveTestCase() {
    int N;
    ll S;
    cin >> N >> S;

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            distanceGrid[i][j] = -1;
        }
    }

    for (int i = 0; i < N; ++i) {
        int r, c;
        cin >> r >> c;
        if (abs(r) < 2500 && abs(c) < 2500) {
            distanceGrid[r + OFFSET][c + OFFSET] = -2;
        }
    }

    queue<Point> queueArray;
    int startX = 0 + OFFSET;
    int startY = 0 + OFFSET;
    
    distanceGrid[startX][startY] = 0;
    queueArray.push({(short)startX, (short)startY});

    vector<ll> countArray(K + 1, 0);
    countArray[0] = 1;

    int dX[] = {0, 0, 1, -1};
    int dY[] = {1, -1, 0, 0};

    while (!queueArray.empty()) {
        Point currentPoint = queueArray.front();
        queueArray.pop();

        int d = distanceGrid[currentPoint.x][currentPoint.y];
        
        if (d >= K) continue;

        for (int i = 0; i < 4; ++i) {
            int nX = currentPoint.x + dX[i];
            int nY = currentPoint.y + dY[i];

            if (nX >= 0 && nX < GRID_SIZE && nY >= 0 && nY < GRID_SIZE) {
                if (distanceGrid[nX][nY] == -1) {
                    distanceGrid[nX][nY] = d + 1;
                    if (d + 1 <= K) {
                        countArray[d + 1]++;
                    }
                    queueArray.push({(short)nX, (short)nY});
                }
            }
        }
    }

    ll redCount = 0;
    ll blueCount = 0;

    int limitBFS = (S < K) ? (int)S : K;
    for (int d = 0; d <= limitBFS; ++d) {
        if (d % 2 == 0) redCount += countArray[d];
        else blueCount += countArray[d];
    }

    if (S > K) {
        if (countArray[K] == 4LL * K) {
            redCount += arithmeticSum(K + 1, S, 0);
            blueCount += arithmeticSum(K + 1, S, 1);
        }
    }

    cout << redCount << " " << blueCount << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}