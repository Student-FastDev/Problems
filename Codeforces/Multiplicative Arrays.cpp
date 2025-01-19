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
const ll MOD = 998244353;

long long modExp(long long base, long long exp) {
    long long ans = 1 % MOD;
    base %= MOD;
    while(exp > 0) {
        if(exp & 1) ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return ans;
}

static long long factorial[20];
static long long inverseFactorial[20];

long long combSmall(long long N, int r) {
    if(r < 0) return 0;
    if(r == 0) return 1;
    long long numerator = 1;
    for(int i=0; i<r; i++) {
        numerator = (numerator * ((N - i) % MOD)) % MOD;
    }
    long long ans = (numerator * inverseFactorial[r]) % MOD;
    return ans;
}

void solveTestCase() {
    long long N; 
    int K;
    cin >> K >> N;
    if(K == 1){
        cout << (N % MOD) << endl;
        return;
    }

    int R_MAX = 0;
    while((1LL << (R_MAX+1)) <= K) R_MAX++;
    long long R = min<long long>(N, R_MAX);

    vector<vector<int>> DP(R+1, vector<int>(K+1, 0));
    
    for(int x = 2; x <= K; x++){
        DP[1][x] = 1;
    }

    for(int r = 2; r <= R; r++){
        for(int x = 2; x <= K; x++){
            int helperValue = DP[r-1][x];
            if(helperValue == 0) continue;
            for(long long m = (long long)2 * x; m <= K; m += x){
                int &destValue = DP[r][m];
                destValue = (destValue + helperValue);
                if(destValue >= MOD) destValue -= MOD;
            }
        }
    }

    vector<long long> binomialCoefficients(R+1, 0LL);
    for(int r = 1; r <= R; r++){
        binomialCoefficients[r] = combSmall(N+1, r+1);
    }

    {
        long long ans = (N % MOD);
        cout << ans;
    }
    for(int x = 2; x <= K; x++){
        long long ans = 0;
        for(int r = 1; r <= R; r++){
            ans += (long long)binomialCoefficients[r]* DP[r][x];
            ans %= MOD;
        }
        cout << " " << ans;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    factorial[0] = 1;
    for(int i=1; i<20; i++){
        factorial[i] = (factorial[i-1]*i) % MOD;
    }
    inverseFactorial[19] = modExp(factorial[19], MOD-2);
    for(int i=18; i>=0; i--){
        inverseFactorial[i] = (inverseFactorial[i+1]*(i+1)) % MOD;
    }

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
