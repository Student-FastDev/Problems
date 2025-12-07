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

int numberOfRows, numberOfColumns;
ll walkCost;
vector<vector<int>> grid;
int rowOffsets[] = {0, 0, 1, -1};
int colOffsets[] = {1, -1, 0, 0};

void performBFS(pii startCell, vector<vector<int>>& distances) {
    for(int i = 0; i < numberOfRows; ++i) {
        fill(all(distances[i]), -1);
    }
    
    queue<pii> bfsQueue;
    bfsQueue.push(startCell);
    distances[startCell.first][startCell.second] = 0;
    
    while(!bfsQueue.empty()) {
        pii currentCell = bfsQueue.front();
        bfsQueue.pop();
        
        int R = currentCell.first;
        int C = currentCell.second;
        
        for(int i = 0; i < 4; ++i) {
            int nextR = R + rowOffsets[i];
            int nextC = C + colOffsets[i];
            
            if(nextR >= 0 && nextR < numberOfRows && nextC >= 0 && nextC < numberOfColumns) {
                if(grid[nextR][nextC] != -1 && distances[nextR][nextC] == -1) {
                    distances[nextR][nextC] = distances[R][C] + 1;
                    bfsQueue.push({nextR, nextC});
                }
            }
        }
    }
}

void solveTestCase() {
    cin >> numberOfRows >> numberOfColumns >> walkCost;
    
    grid.assign(numberOfRows, vector<int>(numberOfColumns));
    for(int i = 0; i < numberOfRows; ++i) {
        for(int j = 0; j < numberOfColumns; ++j) {
            cin >> grid[i][j];
        }
    }
    
    vector<vector<int>> distanceFromStart(numberOfRows, vector<int>(numberOfColumns));
    performBFS({0, 0}, distanceFromStart);
    
    vector<vector<int>> distanceFromEnd(numberOfRows, vector<int>(numberOfColumns));
    performBFS({numberOfRows - 1, numberOfColumns - 1}, distanceFromEnd);
    
    ll minPortalCostStart = INF;
    ll minPortalCostEnd = INF;
    
    for(int i = 0; i < numberOfRows; ++i) {
        for(int j = 0; j < numberOfColumns; ++j) {
            if(grid[i][j] > 0) {
                if(distanceFromStart[i][j] != -1) {
                    ll currentCost = (ll)distanceFromStart[i][j] * walkCost + grid[i][j];
                    if(currentCost < minPortalCostStart) {
                        minPortalCostStart = currentCost;
                    }
                }
                if(distanceFromEnd[i][j] != -1) {
                    ll currentCost = (ll)distanceFromEnd[i][j] * walkCost + grid[i][j];
                    if(currentCost < minPortalCostEnd) {
                        minPortalCostEnd = currentCost;
                    }
                }
            }
        }
    }
    
    ll finalAnswer = INF;
    
    if(distanceFromStart[numberOfRows - 1][numberOfColumns - 1] != -1) {
        finalAnswer = (ll)distanceFromStart[numberOfRows - 1][numberOfColumns - 1] * walkCost;
    }
    
    if(minPortalCostStart != INF && minPortalCostEnd != INF) {
        ll portalPathCost = minPortalCostStart + minPortalCostEnd;
        if(portalPathCost < finalAnswer) {
            finalAnswer = portalPathCost;
        }
    }
    
    if(finalAnswer == INF) {
        cout << -1 << endl;
    } else {
        cout << finalAnswer << endl;
    }
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