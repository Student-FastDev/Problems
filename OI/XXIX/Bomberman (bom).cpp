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
const int IINF = 1e9;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; 

int N;
vector<string> gridArray;
int startX, startY, endX, endY;
int directionX[] = {-1, 1, 0, 0};
int directionY[] = {0, 0, -1, 1};
char directionChar[] = {'G', 'D', 'L', 'P'};

void BFS(int currentStartX, int currentStartY, vector<vector<int>>& distanceArray) {
    for(int i = 1; i <= N; ++i) fill(all(distanceArray[i]), IINF);
    
    distanceArray[currentStartX][currentStartY] = 0;
    queue<pii> queueArray;
    queueArray.push({currentStartX, currentStartY});
    
    while(!queueArray.empty()) {
        pii vertex = queueArray.front();
        queueArray.pop();
        
        if (gridArray[vertex.first-1][vertex.second-1] == '#') continue; 

        for(int i = 0; i < 4; ++i) {
            int nextX = vertex.first + directionX[i];
            int nextY = vertex.second + directionY[i];
            
            if(nextX >= 1 && nextX <= N && nextY >= 1 && nextY <= N) {
                char cell = gridArray[nextX-1][nextY-1];
                if(cell != 'X') {
                    if(distanceArray[nextX][nextY] > distanceArray[vertex.first][vertex.second] + 1) {
                        distanceArray[nextX][nextY] = distanceArray[vertex.first][vertex.second] + 1;
                        if(cell != '#') {
                            queueArray.push({nextX, nextY});
                        }
                    }
                }
            }
        }
    }
}

void solveSegment(const vector<int>& inputValues, vector<int>& outputValues, int startIndex, int endIndex) {
    int minimumValue = IINF;
    for(int j = startIndex; j <= endIndex; ++j) {
        if(inputValues[j] != IINF) {
            minimumValue = min(minimumValue, inputValues[j] - j);
        }
        if(minimumValue != IINF) {
            outputValues[j] = min(outputValues[j], minimumValue + j);
        }
    }
    
    minimumValue = IINF;
    for(int j = endIndex; j >= startIndex; --j) {
        if(inputValues[j] != IINF) {
            minimumValue = min(minimumValue, inputValues[j] + j);
        }
        if(minimumValue != IINF) {
            outputValues[j] = min(outputValues[j], minimumValue - j);
        }
    }
}

void solveTestCase() {
    cin >> N;
    
    gridArray.resize(N);
    for(int i = 0; i < N; ++i) {
        cin >> gridArray[i];
        for(int j = 0; j < N; ++j) {
            if(gridArray[i][j] == 'P') { startX = i + 1; startY = j + 1; gridArray[i][j] = '.'; }
            else if(gridArray[i][j] == 'K') { endX = i + 1; endY = j + 1; gridArray[i][j] = '.'; }
        }
    }
    
    vector<vector<int>> distP(N + 1, vector<int>(N + 1));
    vector<vector<int>> distanceK(N + 1, vector<int>(N + 1));
    
    BFS(startX, startY, distP);
    BFS(endX, endY, distanceK);
    
    vector<vector<int>> rowP(N + 1, vector<int>(N + 1, IINF)); 
    vector<vector<int>> rowK(N + 1, vector<int>(N + 1, IINF)); 
    vector<vector<int>> columnP(N + 1, vector<int>(N + 1, IINF)); 
    vector<vector<int>> columnK(N + 1, vector<int>(N + 1, IINF)); 

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ) {
            if(gridArray[i-1][j-1] == 'X') {
                j++;
                continue;
            }
            int start = j;
            while(j <= N && gridArray[i-1][j-1] != 'X') j++;
            int end = j - 1;
            
            vector<int> segmentP(N + 1, IINF); 
            vector<int> resultP(N + 1, IINF);
            for(int k = start; k <= end; ++k) segmentP[k] = distP[i][k];
            solveSegment(segmentP, resultP, start, end);
            for(int k = start; k <= end; ++k) rowP[i][k] = resultP[k];
            
            vector<int> segmentK(N + 1, IINF);
            vector<int> resultK(N + 1, IINF);
            for(int k = start; k <= end; ++k) segmentK[k] = distanceK[i][k];
            solveSegment(segmentK, resultK, start, end);
            for(int k = start; k <= end; ++k) rowK[i][k] = resultK[k];
        }
    }
    
    for(int j = 1; j <= N; ++j) {
        for(int i = 1; i <= N; ) {
            if(gridArray[i-1][j-1] == 'X') {
                i++;
                continue;
            }
            int start = i;
            while(i <= N && gridArray[i-1][j-1] != 'X') i++;
            int end = i - 1;
            
            vector<int> segmentP(N + 1, IINF);
            vector<int> resultP(N + 1, IINF);
            for(int k = start; k <= end; ++k) segmentP[k] = distP[k][j];
            solveSegment(segmentP, resultP, start, end);
            for(int k = start; k <= end; ++k) columnP[k][j] = resultP[k];
            
            vector<int> segmentK(N + 1, IINF);
            vector<int> resultK(N + 1, IINF);
            for(int k = start; k <= end; ++k) segmentK[k] = distanceK[k][j];
            solveSegment(segmentK, resultK, start, end);
            for(int k = start; k <= end; ++k) columnK[k][j] = resultK[k];
        }
    }
    
    int minimumTime = IINF;
    int bombX = 1, bombY = 1; 
    
    if(distP[endX][endY] < minimumTime) {
        minimumTime = distP[endX][endY];
    }

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            if(gridArray[i-1][j-1] == 'X') continue;
            
            int currentValue = IINF;
            
            if(rowP[i][j] != IINF && distanceK[i][j] != IINF)
                currentValue = min(currentValue, rowP[i][j] + distanceK[i][j]);
                
            if(columnP[i][j] != IINF && distanceK[i][j] != IINF)
                currentValue = min(currentValue, columnP[i][j] + distanceK[i][j]);
                
            if(rowP[i][j] != IINF && columnK[i][j] != IINF)
                currentValue = min(currentValue, rowP[i][j] + columnK[i][j]);
                
            if(columnP[i][j] != IINF && rowK[i][j] != IINF)
                currentValue = min(currentValue, columnP[i][j] + rowK[i][j]);
            
            if(currentValue < minimumTime) {
                minimumTime = currentValue;
                bombX = i;
                bombY = j;
            }
        }
    }
    
    if(minimumTime == IINF) {
        cout << "NIE" << endl;
        return;
    }
    
    if(gridArray[bombX-1][bombY-1] == 'X') {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(gridArray[i][j] != 'X') {
                    bombX = i + 1;
                    bombY = j + 1;
                    goto foundSafe;
                }
            }
        }
        foundSafe:;
    }

    cout << minimumTime << endl;
    cout << bombX << " " << bombY << endl;
    
    int c = bombY;
    while(c >= 1 && gridArray[bombX-1][c-1] != 'X') {
        if(gridArray[bombX-1][c-1] == '#') gridArray[bombX-1][c-1] = '.';
        c--;
    }
    c = bombY;
    while(c <= N && gridArray[bombX-1][c-1] != 'X') {
        if(gridArray[bombX-1][c-1] == '#') gridArray[bombX-1][c-1] = '.';
        c++;
    }
    int r = bombX;
    while(r >= 1 && gridArray[r-1][bombY-1] != 'X') {
        if(gridArray[r-1][bombY-1] == '#') gridArray[r-1][bombY-1] = '.';
        r--;
    }
    r = bombX;
    while(r <= N && gridArray[r-1][bombY-1] != 'X') {
        if(gridArray[r-1][bombY-1] == '#') gridArray[r-1][bombY-1] = '.';
        r++;
    }
    
    vector<vector<int>> finalDistances(N + 1, vector<int>(N + 1, IINF));
    vector<vector<int>> parentDirection(N + 1, vector<int>(N + 1, -1)); 
    queue<pii> queueArray;
    
    finalDistances[startX][startY] = 0;
    queueArray.push({startX, startY});
    
    while(!queueArray.empty()) {
        auto [cX, cY] = queueArray.front();
        queueArray.pop();
        
        if(cX == endX && cY == endY) break;
        
        for(int i = 0; i < 4; ++i) {
            int nX = cX + directionX[i];
            int nY = cY + directionY[i];
            
            if(nX >= 1 && nX <= N && nY >= 1 && nY <= N) {
                if(gridArray[nX-1][nY-1] == '.' && finalDistances[nX][nY] == IINF) {
                    finalDistances[nX][nY] = finalDistances[cX][cY] + 1;
                    parentDirection[nX][nY] = i;
                    queueArray.push({nX, nY});
                }
            }
        }
    }
    
    string pathString = "";
    int currentX = endX, currentY = endY;
    while(currentX != startX || currentY != startY) {
        int dir = parentDirection[currentX][currentY];
        pathString += directionChar[dir];
        currentX -= directionX[dir];
        currentY -= directionY[dir];
    }
    reverse(all(pathString));
    cout << pathString << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}