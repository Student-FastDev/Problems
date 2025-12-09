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
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

ll query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    ll result;
    cin >> result;
    if (result == -1) exit(0);
    return result;
}

void solveTestCase() {
    int N;
    cin >> N;
    
    vector<ll> A(N + 1);
    vector<int> P(N);
    iota(all(P), 1);

    shuffle(all(P), rng);

    int i = 0;
    while (i + 2 < N) {
        int U = P[i];
        int V = P[i + 1];
        int W = P[i + 2];

        ll firstP = query(U, V);
        ll secondP = query(V, W);

        ll G = gcd(firstP, secondP);
        
        ll firstA = G;
        ll secondA = firstP / firstA;
        ll thirdA = secondP / firstA;
        
        A[U] = secondA;
        A[V] = firstA;
        A[W] = thirdA;
        
        i += 3;
    }

    int bestAnchor = -1;
    for (int k = 0; k < i; ++k) {
        if (A[P[k]] % 2 != 0) {
            bestAnchor = P[k];
            break;
        }
    }
    if (bestAnchor == -1 && i > 0) bestAnchor = P[0];

    int currentAnchor = bestAnchor;
    while (i < N) {
        int Z = P[i];
        ll P = query(currentAnchor, Z);
        A[Z] = P / A[currentAnchor];
        
        currentAnchor = Z;
        i++;
    }

    cout << "!";
    for (int k = 1; k <= N; ++k) {
        cout << " " << A[k];
    }
    cout << endl;
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
