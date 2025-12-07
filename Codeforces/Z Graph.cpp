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
    int N, M;
    cin >> N >> M;

    map<pii, int> edgesMap;
    int totalCycles = 0;
    int sameLabelCycles = 0;

    for(int i = 0; i < M; ++i) {
        char Type;
        cin >> Type;
        if (Type == '+') {
            int U, V;
            char C;
            cin >> U >> V >> C;
            int charVal = C;
            
            if (edgesMap.count({V, U})) {
                totalCycles++;
                if (edgesMap[{V, U}] == charVal) {
                    sameLabelCycles++;
                }
            }
            edgesMap[{U, V}] = charVal;
        } else if (Type == '-') {
            int U, V;
            cin >> U >> V;
            
            if (edgesMap.count({V, U})) {
                totalCycles--;
                if (edgesMap[{V, U}] == edgesMap[{U, V}]) {
                    sameLabelCycles--;
                }
            }
            edgesMap.erase({U, V});
        } else {
            int K;
            cin >> K;
            bool possible = false;
            if (K % 2 != 0) {
                if (totalCycles > 0) possible = true;
            } else {
                if (sameLabelCycles > 0) possible = true;
            }
            
            if (possible) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
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