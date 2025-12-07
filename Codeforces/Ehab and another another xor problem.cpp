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

int ask(int c, int d) {
    cout << "? " << c << " " << d << endl;
    cout.flush();
    int res;
    cin >> res;
    if (res == -2) exit(0);
    return res;
}

void solveTestCase() {
    int currentRelation = ask(0, 0);
    int ansA = 0;
    int ansB = 0;

    for (int i = 29; i >= 0; --i) {
        int res = ask(ansA | (1 << i), ansB | (1 << i));
        
        int valA = 0;
        int valB = 0;

        if (res != currentRelation) {
            if (currentRelation == 1) {
                valA = 1; valB = 0;
            } else {
                valA = 0; valB = 1;
            }
            
            if (valA) ansA |= (1 << i);
            if (valB) ansB |= (1 << i);
            
            if (i > 0)
                currentRelation = ask(ansA, ansB);
        } else {
            int res2 = ask(ansA | (1 << i), ansB);
            if (res2 == 1) {
                valA = 0; valB = 0;
            } else {
                valA = 1; valB = 1;
            }
            if (valA) ansA |= (1 << i);
            if (valB) ansB |= (1 << i);
        }
    }

    cout << "! " << ansA << " " << ansB << endl;
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}