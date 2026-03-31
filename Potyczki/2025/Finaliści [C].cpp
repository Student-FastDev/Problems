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
    int N;
    cin >> N;
    vector<pair<int, int>> isEligible;
    
    for (int i = 1; i <= N; i++) {
        string S;
        int X;
        cin >> S >> X;
        if (S == "TAK") {
            isEligible.emplace_back(i, X);
        }
    }
    
    vector<int> finalistsArray;
    for (int i = 0; i < 10; i++) {
        finalistsArray.push_back(isEligible[i].first);
    }
    
    int countValue = 10;
    for (int i = 10; countValue < 20 && i < (int) size(isEligible); i++) {
        if (isEligible[i].second < 2) {
            finalistsArray.push_back(isEligible[i].first);
            countValue++;
        }
    }
    
    sort(finalistsArray.begin(), finalistsArray.end());
    for (int X : finalistsArray) {
        cout << X << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
