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

struct Chip {
    int R, C, dir, id;
};

int getDirectionIndex(char C) {
    if(C == 'L') return 0;
    if(C == 'R') return 1;
    if(C == 'U') return 2;
    if(C == 'D') return 3;
    return -1;
}

void solveTestCase() {
    int numRows, numCols;
    cin >> numRows >> numCols;

    vector<string> grid(numRows);
    vector<Chip> chips;
    vector<vector<int>> gridIds(numRows, vector<int>(numCols, -1));

    for (int i = 0; i < numRows; ++i) {
        cin >> grid[i];
        for (int j = 0; j < numCols; ++j) {
            if (grid[i][j] != '.') {
                int direction = getDirectionIndex(grid[i][j]);
                gridIds[i][j] = (int)size(chips);
                chips.push_back({i, j, direction, (int)size(chips)});
            }
        }
    }

    int numChips = size(chips);
    vector<array<int, 4>> neighbourList(numChips, {-1, -1, -1, -1});

    for (int i = 0; i < numRows; ++i) {
        int lastChipId = -1;
        for (int j = 0; j < numCols; ++j) {
            if (gridIds[i][j] != -1) {
                int currentId = gridIds[i][j];
                if (lastChipId != -1) {
                    neighbourList[lastChipId][1] = currentId;
                    neighbourList[currentId][0] = lastChipId;
                }
                lastChipId = currentId;
            }
        }
    }

    for (int j = 0; j < numCols; ++j) {
        int lastChipId = -1;
        for (int i = 0; i < numRows; ++i) {
            if (gridIds[i][j] != -1) {
                int currentId = gridIds[i][j];
                if (lastChipId != -1) {
                    neighbourList[lastChipId][3] = currentId;
                    neighbourList[currentId][2] = lastChipId;
                }
                lastChipId = currentId;
            }
        }
    }

    int maxPoints = 0;
    int waysToGetMax = 0;

    vector<array<int, 4>> currentNeighbourList(numChips);

    for (int startNode = 0; startNode < numChips; ++startNode) {
        currentNeighbourList = neighbourList;

        int currentNode = startNode;
        int points = 0;

        while (true) {
            points++;
            int direction = chips[currentNode].dir;
            int nextNode = currentNeighbourList[currentNode][direction];

            int leftNeighbor = currentNeighbourList[currentNode][0];
            int rightNeighbor = currentNeighbourList[currentNode][1];
            int upNeighbor = currentNeighbourList[currentNode][2];
            int downNeighbor = currentNeighbourList[currentNode][3];

            if (leftNeighbor != -1) currentNeighbourList[leftNeighbor][1] = rightNeighbor;
            if (rightNeighbor != -1) currentNeighbourList[rightNeighbor][0] = leftNeighbor;

            if (upNeighbor != -1) currentNeighbourList[upNeighbor][3] = downNeighbor;
            if (downNeighbor != -1) currentNeighbourList[downNeighbor][2] = upNeighbor;

            if (nextNode == -1) break;
            currentNode = nextNode;
        }

        if (points > maxPoints) {
            maxPoints = points;
            waysToGetMax = 1;
        } else if (points == maxPoints) {
            waysToGetMax++;
        }
    }

    cout << maxPoints << " " << waysToGetMax << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}