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
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

int N, M, S;
int timeUsed = 0;
int waitsUsed = 0;

vector<vector<bool>> candidateB;
vector<vector<bool>> candidateK;

vector<string> boardArray;

int observeQuery(int X, int Y) {
    cout << "BADAJ " << X << " " << Y << endl;
    int queryResult;
    cin >> queryResult;
    return queryResult;
}

void waitQuery(int T) {
    cout << "CZEKAJ " << T << endl;
    for (int i = 0; i < N; i++) cin >> boardArray[i];
}

int keepModulo(int i, int n) {
    return (i % n + n) % n;
}

void observeZero(int row, int column, int time) {
    int rowB = keepModulo(row - time, N);
    int columnB = column;
    candidateB[rowB][columnB] = false;

    int rowK = row;
    int columnK = keepModulo(column - time, M);
    candidateK[rowK][columnK] = false;
}

void removeFound(int row, int column, int time, bool remainingB, bool remainingK) {
    if (remainingB) {
        int rowB = keepModulo(row - time, N);
        int columnB = column;
        candidateB[rowB][columnB] = false;
    }
    if (remainingK) {
        int rowK = row;
        int columnK = keepModulo(column - time, M);
        candidateK[rowK][columnK] = false;
    }
}

bool isPossibleB(int row, int column, int time) {
    int startRow = keepModulo(row - time, N);
    return candidateB[startRow][column];
}

bool isPossibleK(int row, int column, int time) {
    int startColumn = keepModulo(column - time, M);
    return candidateK[row][startColumn];
}

int countOnes() {
    int currentCount = 0;
    for (const string& row : boardArray) {
        for (char column : row) if (column == '1') currentCount++;
    }
    return currentCount;
}

void solveTestCase() {
    cin >> N >> M >> S;

    boardArray.resize(N);
    candidateB.assign(N, vector<bool>(M, false));
    candidateK.assign(N, vector<bool>(M, false));

    for (int i = 0; i < N; i++) {
        cin >> boardArray[i];
        for (int j = 0; j < M; j++) {
            if (boardArray[i][j] == '1') {
                candidateB[i][j] = true;
                candidateK[i][j] = true;
            } else {
                candidateB[i][j] = false;
                candidateK[i][j] = false;
            }
        }
    }

    while (true) {
        while (true) {
            bool localChange = false;
            for (int row = 0; row < N; row++) {
                for (int column = 0; column < M; column++) {
                    if (boardArray[row][column] == '1') {
                        bool positionB = isPossibleB(row, column, timeUsed);
                        bool positionK = isPossibleK(row, column, timeUsed);

                        if ((positionB && !positionK) || (!positionB && positionK)) {
                            int finalResult = observeQuery(row + 1, column + 1);
                            
                            if (positionB && !positionK) {
                                removeFound(row, column, timeUsed, true, false); 
                                if (finalResult == 2) removeFound(row, column, timeUsed, false, true);
                            } else {
                                removeFound(row, column, timeUsed, false, true);
                                if (finalResult == 2) removeFound(row, column, timeUsed, true, false);
                            }

                            boardArray[row][column] = '0';
                            localChange = true;
                            if (countOnes() == 0) return;
                        }
                    }
                }
            }
            if (!localChange) break;
        }

        if (countOnes() == 0) break;
        
        if (waitsUsed == 9) {
            for (int row = 0; row < N; row++) {
                for (int column = 0; column < M; column++) {
                    if (boardArray[row][column] == '1') {
                        int finalResult = observeQuery(row + 1, column + 1);
                        boardArray[row][column] = '0';
                        if (countOnes() == 0) return;
                    }
                }
            }
            return;
        }

        int bestT = 1;
        ll maxScore = -INF;
        int maxValue = N * M; 
        
        for (int value = 1; value <= maxValue; value++) {
            int simulationTime = timeUsed + value;
            int safeCount = 0;
            int overCount = 0;

            for (int row = 0; row < N; row++) {
                for (int column = 0; column < M; column++) {
                    bool possibilityB = isPossibleB(row, column, simulationTime);
                    bool possibilityK = isPossibleK(row, column, simulationTime);
                    
                    if (possibilityB && !possibilityK) safeCount++;
                    else if (!possibilityB && possibilityK) safeCount++;
                    else if (possibilityB && possibilityK) overCount++;
                }
            }
            
            ll score = safeCount * 10000 - overCount;
            
            if (score > maxScore) {
                maxScore = score;
                bestT = value;
            }
        }

        waitQuery(bestT);
        timeUsed += bestT;
        waitsUsed++;

        for(int row = 0; row < N; ++row) {
            for(int column = 0; column <M; ++column) {
                if(boardArray[row][column] == '0') observeZero(row, column, timeUsed);
            }
        }
        
        if (countOnes() == 0) break;
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
