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

const ll INVERSE = 500000004;

ll calculateFunction(ll N, ll M) {
    ll DP[2][2] = {0};
    DP[0][0] = 1;

    for(int bit = 60; bit >= 0; bit--) {
        ll nextDP[2][2] = {0};
        int bitN = (N >> bit) & 1;
        int bitM = (M >> bit) & 1;

        for(int lessN = 0; lessN < 2; lessN++) {
            for(int lessM = 0; lessM < 2; lessM++) {
                ll currentWays = DP[lessN][lessM];
                if(!currentWays) continue;

                for(int x = 0; x < 2; x++) {
                    if(!lessN && x > bitN) continue;;

                    for(int y = 0; y < 2; y++) {
                        if(x == 1 && y == 1) continue;
                        if(!lessM && y > bitM) continue;   
                        int nextLessN = lessN || (x < bitN);
                        int nextLessM = lessM || (y < bitM);

                        nextDP[nextLessN][nextLessM] = (nextDP[nextLessN][nextLessM] + currentWays) % MOD;
                    }
                }
            }
        }

        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                DP[i][j] = nextDP[i][j];
            }
        }
    }

    ll finalAnswer = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            finalAnswer = finalAnswer + (DP[i][j]) % MOD;
        }
    }
    return finalAnswer;
}

void solveTestCase() {
    ll A, B;
    cin >> A >> B;
    
    ll finalAnswer = (calculateFunction(B, B) - 2 * calculateFunction(A - 1, B) + calculateFunction(A - 1, A - 1)) % MOD;
    if (finalAnswer < 0) finalAnswer += MOD;
    
    finalAnswer = (finalAnswer * INVERSE) % MOD;
    cout << finalAnswer << endl;
    return;
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