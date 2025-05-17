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

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    
    int* H = new int[N];
    for (int i = 0; i < N; i++){
        cin >> H[i];
    }
    
    long long differenceSum = 0;
    for (int i = 1; i < N; i++){
        differenceSum += abs(H[i] - H[i-1]);
    }
    
    while (Q--) {
        int Z;
        cin >> Z;
        long long answerValue = (abs(H[0] - Z) + abs(H[N - 1] - Z) + differenceSum) / 2;
        cout << answerValue << endl;
    }
    
    delete[] H;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}