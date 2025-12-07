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
    int N, M;
    cin >> N >> M;

    vector<vector<int>> tableGrid(N, vector<int>(M));
    vector<int> rowSums(N, 0);
    vector<int> columnSums(M, 0);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cin >> tableGrid[i][j];
            rowSums[i] += tableGrid[i][j];
            columnSums[j] += tableGrid[i][j];
        }
    }

    vector<int> negativeRows;
    vector<int> negativeColumns;
    vector<bool> isRowInQueue(N, false);
    vector<bool> isColumnInQueue(M, false);

    for(int i = 0; i < N; ++i) {
        if(rowSums[i] < 0) {
            negativeRows.push_back(i);
            isRowInQueue[i] = true;
        }
    }
    for(int j = 0; j < M; ++j) {
        if(columnSums[j] < 0) {
            negativeColumns.push_back(j);
            isColumnInQueue[j] = true;
        }
    }

    vector<int> rowFlips(N, 0);
    vector<int> columnFlips(M, 0);

    size_t rowQueueIndex = 0;
    size_t columnQueueIndex = 0;

    while(rowQueueIndex < size(negativeRows) || columnQueueIndex < size(negativeColumns)) {
        if (rowQueueIndex < size(negativeRows)) {
            int currentRow = negativeRows[rowQueueIndex++];
            isRowInQueue[currentRow] = false;

            if (rowSums[currentRow] >= 0) continue;

            rowFlips[currentRow] ^= 1;
            rowSums[currentRow] = -rowSums[currentRow];

            for(int j = 0; j < M; ++j) {
                columnSums[j] -= 2 * tableGrid[currentRow][j];
                tableGrid[currentRow][j] = -tableGrid[currentRow][j];
                if (columnSums[j] < 0 && !isColumnInQueue[j]) {
                    negativeColumns.push_back(j);
                    isColumnInQueue[j] = true;
                }
            }
        } else {
            int currentColumn = negativeColumns[columnQueueIndex++];
            isColumnInQueue[currentColumn] = false;

            if (columnSums[currentColumn] >= 0) continue;

            columnFlips[currentColumn] ^= 1;
            columnSums[currentColumn] = -columnSums[currentColumn];

            for(int i = 0; i < N; ++i) {
                rowSums[i] -= 2 * tableGrid[i][currentColumn];
                tableGrid[i][currentColumn] = -tableGrid[i][currentColumn];
                if (rowSums[i] < 0 && !isRowInQueue[i]) {
                    negativeRows.push_back(i);
                    isRowInQueue[i] = true;
                }
            }
        }
    }

    vector<int> resultRows;
    for(int i = 0; i < N; ++i) {
        if (rowFlips[i]) resultRows.push_back(i + 1);
    }

    vector<int> resultColumns;
    for(int j = 0; j < M; ++j) {
        if (columnFlips[j]) resultColumns.push_back(j + 1);
    }

    cout << size(resultRows);
    for(int r : resultRows) cout << " " << r;
    cout << endl;

    cout << size(resultColumns);
    for(int c : resultColumns) cout << " " << c;
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}