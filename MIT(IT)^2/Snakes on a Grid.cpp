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

inline int getSum(const vector<vector<int>> &PS, int r1, int c1, int r2, int c2) {
    if (r1 > r2 || c1 > c2) return 0;
    return PS[r2+1][c2+1] - PS[r1][c2+1] - PS[r2+1][c1] + PS[r1][c1];
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> A(N, vector<int>(M));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> A[i][j];
        }
    }

    vector<vector<int>> B(N, vector<int>(M, 0));
    vector<vector<int>> H(N, vector<int>(M, 0));
    vector<vector<int>> V(N, vector<int>(M, 0));

    for(int i = 0; i + 1 < N; i++){
        for(int j = 0; j + 1 < M; j++){
            if( A[i][j] == A[i][j+1]
             && A[i][j] == A[i+1][j]
             && A[i][j] == A[i+1][j+1] ){
                B[i][j] = 1;
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j + 2 < M; j++){
            if(A[i][j] == A[i][j+1] && A[i][j] == A[i][j+2]){
                H[i][j] = 1;
            }
        }
    }

    for(int i = 0; i + 2 < N; i++){
        for(int j = 0; j < M; j++){
            if(A[i][j] == A[i+1][j] && A[i][j] == A[i+2][j]){
                V[i][j] = 1;
            }
        }
    }

    vector<vector<int>> PB(N+1, vector<int>(M+1, 0));
    vector<vector<int>> PH(N+1, vector<int>(M+1, 0));
    vector<vector<int>> PV(N+1, vector<int>(M+1, 0));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            PB[i+1][j+1] = PB[i][j+1] + PB[i+1][j] - PB[i][j] + B[i][j];
            PH[i+1][j+1] = PH[i][j+1] + PH[i+1][j] - PH[i][j] + H[i][j];
            PV[i+1][j+1] = PV[i][j+1] + PV[i+1][j] - PV[i][j] + V[i][j];
        }
    }

    int Q; 
    cin >> Q;
    while(Q--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int sumB = getSum(PB, x1, y1, x2-1, y2-1);
        int sumH = getSum(PH, x1, y1, x2, y2-2);
        int sumV = getSum(PV, x1, y1, x2-2, y2);

        if(sumB > 0 || sumH > 0 || sumV > 0){
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}
