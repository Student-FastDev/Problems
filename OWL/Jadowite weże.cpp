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
#define sz(x)   (int)x.size()

const ll INF = 9223372036854775806;
const ll MAX = 2001;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<vector<char>> grid(N, vector<char>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    auto isAllowed = [](char C) {
        return C == '.' || C == '@' || C == 'O';
    };

    if (!isAllowed(grid[0][0]) || !isAllowed(grid[N-1][M-1])) {
        cout << "NIE" << endl;
        return;
    }

    vector<vector<bool>> DP(N, vector<bool>(M, false));
    DP[0][0] = true;

    for (int j = 1; j < M; ++j) {
        if (isAllowed(grid[0][j]) && DP[0][j-1]) {
            DP[0][j] = true;
        }
    }

    for (int i = 1; i < N; ++i) {
        if (isAllowed(grid[i][0]) && DP[i-1][0]) {
            DP[i][0] = true;
        }
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < M; ++j) {
            if (isAllowed(grid[i][j]) && (DP[i-1][j] || DP[i][j-1])) {
                DP[i][j] = true;
            }
        }
    }

    if (!DP[N-1][M-1]) {
        cout << "NIE" << endl;
        return;
    }

    vector<char> path;
    int i = N-1, j = M-1;
    while (i != 0 || j != 0) {
        if (i > 0 && DP[i-1][j]) {
            path.push_back('D');
            --i;
        } else {
            path.push_back('P');
            --j;
        }
    }

    reverse(all(path));

    vector<int> switchedRows(N, 0);
    vector<int> switchedColumns(M, 0);

    if(grid[0][0] == '@') {
        switchedRows[0] = 1;
        for(int j = 0; j < M; j++) {
            if(grid[0][j] == '@') {
                grid[0][j] = 'O';
            }
            else if(grid[0][j] == 'O') {
                grid[0][j] = '@';
            }
        }
    }

    int firstCoordinate = 0;
    int secondCoordinate = 0;
    for(int i = 0; i < size(path); i++) {
        if(grid[firstCoordinate][secondCoordinate] == '@' && path[i-1] == 'D') {
            switchedRows[firstCoordinate] = 1;
            for(int j = 0; j < M; j++) {
                if(grid[firstCoordinate][j] == '@') {
                    grid[firstCoordinate][j] = 'O';
                }
                else if(grid[firstCoordinate][j] == 'O') {
                    grid[firstCoordinate][j] = '@';
                }
            }
        }
        if(grid[firstCoordinate][secondCoordinate] == '@' && path[i-1] == 'P') {
            switchedColumns[secondCoordinate] = 1;
            for(int j = 0; j < N; j++) {
                if(grid[j][secondCoordinate] == '@') {
                    grid[j][secondCoordinate] = 'O';
                }
                else if(grid[j][secondCoordinate] == 'O') {
                    grid[j][secondCoordinate] = '@';
                }
            }
        }
        if(path[i] == 'D') {
            firstCoordinate++;
        }
        else {
            secondCoordinate++;
        }
    }

    if(grid[N-1][M-1] == '@') {
        if(path[size(path)-1] == 'D') {
            switchedRows[N-1] = 1;
            for(int j = 0; j < M; j++) {
                if(grid[N-1][j] == '@') {
                    grid[N-1][j] = 'O';
                }
                else if(grid[N-1][j] == 'O') {
                    grid[N-1][j] = '@';
                }
            }
        }
        else {
            switchedColumns[M-1] = 1;
            for(int j = 0; j < N; j++) {
                if(grid[j][M-1] == '@') {
                    grid[j][M-1] = 'O';
                }
                else if(grid[j][M-1] == 'O') {
                    grid[j][M-1] = '@';
                }
            }
        }
    }

    cout << "TAK" << endl;
    for(int i = 0; i < N; i++) {
        if(switchedRows[i] == 1) {
            cout << "T";
        }
        else {
            cout << "N";
        }
    }
    cout << endl;
    for(int i = 0; i < M; i++) {
        if(switchedColumns[i] == 1) {
            cout << "T";
        }
        else {
            cout << "N";
        }
    }
    cout << endl;
    for (char C : path) {
        cout << C;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }

    return 0;
}
