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
const ll MAX_N = 2 * 1e5 + 1;
const ll MOD = 1e9+7; // 998244353

const int LOG_N = 19;

int H, W, Q;
int X[MAX_N];
int L[MAX_N];
int R[MAX_N];
int nextStart[MAX_N];
int upTable[LOG_N][MAX_N];

void solveTestCase() {
    cin >> H >> W;

    for (int i = 1; i <= W; i++) {
        cin >> X[i];
    }

    for (int i = 0; i <= H + 1; i++) {
        L[i] = i;
        R[i] = i;
    }

    for (int i = W; i >= 1; i--) {
        int x = X[i];
        L[x] = L[x - 1];
    }

    for (int i = W; i >= 1; i--) {
        int x = X[i];
        R[x] = R[x + 1];
    }

    int pointerValue = 1;
    for (int i = 1; i <= H; i++) {
        if (pointerValue < i) pointerValue = i;
        while (pointerValue < H && L[pointerValue + 1] <= R[i]) pointerValue++;
        
        nextStart[i] = pointerValue + 1;
    }
    
    for (int i = 1; i <= H + 1; i++) {
         if (i > H) nextStart[i] = H + 1;
    }

    for (int i = 1; i <= H + 1; i++) {
        upTable[0][i] = nextStart[i];
    }

    for (int k = 1; k < LOG_N; k++) {
        for (int i = 1; i <= H + 1; i++) {
            int middleValue = upTable[k - 1][i];
            if (middleValue > H) upTable[k][i] = H + 1;
            else upTable[k][i] = upTable[k - 1][middleValue];
        }
    }

    cin >> Q;
    while (Q--) {
        int A, B;
        cin >> A >> B;
                
        int finalAnswer = 0;
        int currentValue = A;
        
        for (int k = LOG_N - 1; k >= 0; k--) {
            if (upTable[k][currentValue] <= B) {
                currentValue = upTable[k][currentValue];
                finalAnswer += (1 << k);
            }
        }
        
        cout << finalAnswer + 1 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
