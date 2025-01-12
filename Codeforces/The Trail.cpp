// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    string s;
    cin >> s;

    vector<vector<long long>> A(N, vector<long long>(M));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> A[i][j];
        }
    }

    vector<vector<bool>> onPath(N, vector<bool>(M, false));
    {
        int R = 0, C = 0;
        onPath[R][C] = true;
        for(char step : s) {
            if(step == 'R') ++C;
            else            ++R;
            onPath[R][C] = true;
        }
    }

    vector<long long> S(N, 0LL), T(M, 0LL);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(!onPath[i][j]) {
                S[i] += A[i][j];
                T[j] += A[i][j];
            }
        }
    }

    long long X = 0;
    if(N == M) {
        X = 0;
    } else {
        X = 0;
    }

    vector<long long> rowNeed(N), colNeed(M);
    for(int i = 0; i < N; i++){
        rowNeed[i] = X - S[i];
    }
    for(int j = 0; j < M; j++){
        colNeed[j] = X - T[j];
    }

    vector<vector<long long>> B(N, vector<long long>(M));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(onPath[i][j]) {
                B[i][j] = 0;
            } else {
                B[i][j] = A[i][j];
            }
        }
    }

    {
        int R = 0, C = 0;
        for(int idx = 0; idx < (N + M - 2); idx++){
            char move = s[idx];
            if(move == 'R') {
                long long fix = colNeed[C];
                B[R][C] += fix;
                rowNeed[R] -= fix;
                colNeed[C] = 0;
                C++;
            }
            else {
                long long fix = rowNeed[R];
                B[R][C] += fix;
                colNeed[C] -= fix;
                rowNeed[R] = 0;
                R++;
            }
        }
        long long fix = rowNeed[N-1];
        B[N-1][M-1] += fix;
        rowNeed[N-1] = 0;
        colNeed[M-1] -= fix; 
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << B[i][j] << (j + 1 < M ? ' ' : '\n');
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
