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
    int N;
    ll P;
    cin >> N >> P;

    if (P == 1) {
        cout << 0 << endl;
        return;
    }

    ll counts[3] = {0, 0, 0};
    ll lastR = 0;
    int iter = 0;

    while (lastR < P - 1) {
        ll currentR;
        int value = iter % 3;
        
        if (value == 2) {
            currentR = lastR + 1;
        } else {
            if (lastR == 0) currentR = 2;
            else currentR = lastR * 2;
        }

        ll start = lastR + 1;
        ll end = currentR;

        if (start < P) {
            ll actualEnd = min(end, P - 1);
            if (actualEnd >= start) {
                ll count = actualEnd - start + 1;
                ll A = P - start;
                ll B = P - actualEnd;
                ll sumValue = (A + B) * count / 2;
                sumValue %= MOD;
                counts[value] = (counts[value] + sumValue) % MOD;
            }
        }

        lastR = currentR;
        iter++;
    }

    vector<ll> DP(4, 0);
    DP[0] = 1;

    for (int i = 0; i < N; ++i) {
        vector<ll> nextDP(4, 0);
        for (int curXor = 0; curXor < 4; ++curXor) {
            if (DP[curXor] == 0) continue;
            for (int value = 0; value < 3; ++value) {
                int nextXor = curXor ^ value;
                ll ways = (DP[curXor] * counts[value]) % MOD;
                nextDP[nextXor] = (nextDP[nextXor] + ways) % MOD;
            }
        }
        DP = nextDP;
    }

    ll answer = (DP[1] + DP[2] + DP[3]) % MOD;
    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}