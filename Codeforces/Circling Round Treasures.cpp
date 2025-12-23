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

struct Object {
    int row, col;
    int id;
};

int N, M;
vector<string> grid;
int startRow, startCol;
vector<int> treasureValues;
vector<Object> objects;
int distanceArray[22][22][256];

void solveTestCase() {
    cin >> N >> M;
    grid.resize(N);
    int maxTreasureCount = 0;
    for(int i = 0; i < N; ++i) {
        cin >> grid[i];
        for(int j = 0; j < M; ++j) {
            if(grid[i][j] == 'S') {
                startRow = i;
                startCol = j;
            } else if(isdigit(grid[i][j])) {
                maxTreasureCount = max(maxTreasureCount, grid[i][j] - '0');
            }
        }
    }

    treasureValues.resize(maxTreasureCount);
    for(int i = 0; i < maxTreasureCount; ++i) {
        cin >> treasureValues[i];
    }

    objects.clear();
    int bombCounter = maxTreasureCount;
    int bombMask = 0;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(isdigit(grid[i][j])) {
                objects.push_back({i, j, grid[i][j] - '1'});
            } else if(grid[i][j] == 'B') {
                objects.push_back({i, j, bombCounter});
                bombMask |= (1 << bombCounter);
                bombCounter++;
            }
        }
    }

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            for(int k = 0; k < 256; ++k)
                distanceArray[i][j][k] = 1e9;

    distanceArray[startRow][startCol][0] = 0;
    queue<tuple<int, int, int>> bfsQueue;
    bfsQueue.push({startRow, startCol, 0});

    int deltaRow[] = {0, 0, 1, -1};
    int deltaCol[] = {1, -1, 0, 0};

    while(!bfsQueue.empty()) {
        auto [currentRow, currentCol, currentMask] = bfsQueue.front();
        bfsQueue.pop();

        int currentDistance = distanceArray[currentRow][currentCol][currentMask];

        for(int i = 0; i < 4; ++i) {
            int nextRow = currentRow + deltaRow[i];
            int nextCol = currentCol + deltaCol[i];

            if(nextRow >= 0 && nextRow < N && nextCol >= 0 && nextCol < M) {
                char cell = grid[nextRow][nextCol];
                if(cell != '#' && !isdigit(cell) && cell != 'B') {
                    int nextMask = currentMask;
                    if(nextRow == currentRow) { // Horizontal move
                        for(auto& obj : objects) {
                            if(currentRow < obj.row) {
                                int minCol = min(currentCol, nextCol);
                                int maxCol = max(currentCol, nextCol);
                                if(minCol == obj.col && maxCol == obj.col + 1) {
                                    nextMask ^= (1 << obj.id);
                                }
                            }
                        }
                    }

                    if(distanceArray[nextRow][nextCol][nextMask] > currentDistance + 1) {
                        distanceArray[nextRow][nextCol][nextMask] = currentDistance + 1;
                        bfsQueue.push({nextRow, nextCol, nextMask});
                    }
                }
            }
        }
    }

    int maxProfit = 0;
    for(int mask = 0; mask < 256; ++mask) {
        if(distanceArray[startRow][startCol][mask] != 1e9) {
            if((mask & bombMask) == 0) {
                int currentProfit = 0;
                for(int i = 0; i < maxTreasureCount; ++i) {
                    if((mask >> i) & 1) {
                        currentProfit += treasureValues[i];
                    }
                }
                currentProfit -= distanceArray[startRow][startCol][mask];
                if(currentProfit > maxProfit) maxProfit = currentProfit;
            }
        }
    }

    cout << maxProfit << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    // cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}