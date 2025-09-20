// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<vector<int>> positionArray(N + 1);

    for (int j = 0; j < N; ++j) {
        int currentValue = A[N - 1 - j];
        positionArray[currentValue].push_back(j + 1);
    }

    vector<int> lisSequence;
    lisSequence.reserve(N);
    for (int i = 0; i < N; ++i) {
        int currentValue = A[i];
        auto &V = positionArray[currentValue];
        for (int k = (int)size(V) - 1; k >= 0; --k) lisSequence.push_back(V[k]);
    }

    vector<int> tailArray;
    for (int x : lisSequence) {
        auto it = lower_bound(tailArray.begin(), tailArray.end(), x);
        if (it == tailArray.end()) tailArray.push_back(x);
        else *it = x;
    }

    int LPS = (int)size(tailArray);
    int finalAnswer = (LPS / 2) * 2;
    cout << finalAnswer << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}
