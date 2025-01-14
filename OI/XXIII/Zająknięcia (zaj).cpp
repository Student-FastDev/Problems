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
const ll MAX_N = 15001;
const ll MOD = 1e9+7; // 998244353

inline void readLongLong(ll *number) {
    register char currentChar = 0;
    ll sign = 1;

    while (currentChar < 33) {
        currentChar = getc_unlocked(stdin);
    }

    if (currentChar == '-') {
        sign = -1;
        currentChar = getc_unlocked(stdin);
    }

    *number = 0;

    while (currentChar > 32) {
        *number = (*number) * 10 + (currentChar - '0');
        currentChar = getc_unlocked(stdin);
    }

    *number *= sign;
}

int main() {
    int N, M;
    readLongLong((ll*)&N);
    readLongLong((ll*)&M);

    vector<ll> A(N + 1);
    vector<ll> B(M + 1);

    for (int i = 1; i <= N; ++i) {
        readLongLong(&A[i]);
    }

    for (int j = 1; j <= M; ++j) {
        readLongLong(&B[j]);
    }

    vector<int> prevB(M + 1, 0);
    unordered_map<ll, int> lastSeenB;
    for(int j =1; j <= M; ++j){
        if(lastSeenB.find(B[j]) != lastSeenB.end()){
            prevB[j] = lastSeenB[B[j]];
        }
        else{
            prevB[j] = 0;
        }
        lastSeenB[B[j]] = j;
    }

    vector<vector<int>> DP(2, vector<int>(M + 1, 0));
    vector<int> MEMO(M + 1, 0);
    unordered_map<ll, int> lastA;

    for(int j = 0; j <= M; j++){
        DP[0][j] = 0;
        MEMO[j] = 0;
    }

    for(int i = 1; i <= N; i++){
        int currentRow = i % 2;
        int previousRow = (i - 1) % 2;
        DP[currentRow][0] = 0;
        for(int j = 1; j <= M; j++){
            if(A[i] == B[j] && lastA.find(A[i]) != lastA.end() && lastA[A[i]] >0 && prevB[j] > 0){
                DP[currentRow][j] = MEMO[prevB[j]] + 2;
            }
            else{
                DP[currentRow][j] = 0;
            }
            DP[currentRow][j] = max({DP[currentRow][j], DP[previousRow][j], DP[currentRow][j-1]});
            LOG(DP[currentRow][j]);
        }
        for(int j=1; j<=M; j++){
            if(A[i] == B[j]){
                MEMO[j] = DP[previousRow][j-1];
            }
        }
        lastA[A[i]] = i;
    }

    cout << DP[N % 2][M] << endl;
    return 0;
}
