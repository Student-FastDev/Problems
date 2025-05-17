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
    int N;
    cin >> N;
    vector<long long> T(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    long long previousA = 0, currentA = 1;
    long long previousB = 0, currentB = -T[0];

    for (int i = 1; i < N-1; i++) {
        long long nextA = 1 - 2 * currentA - previousA;
        long long nextB = -T[i] - 2 * currentB - previousB;
        previousA = currentA; currentA = nextA;
        previousB = currentB; currentB = nextB;
    }

    long long alphaN = currentA, betaN = currentB;
    if (alphaN == 0 || (-betaN) % alphaN != 0) {
        cout << "NIE" << endl;
        return;
    }
    long long H = (-betaN) / alphaN;

    vector<long long> A(N, 0);
    A[1] = H - T[0];
    if (A[1] < 0) {
        cout << "NIE" << endl;
        return;
    }
    for (int i = 1; i < N-1; i++) {
        long long nextA = H - T[i] - 2*A[i] - A[i-1];
        if (nextA < 0) {
            cout << "NIE" << endl;
            return;
        }
        A[i+1] = nextA;
    }

    if (A[N-1] != 0) {
        cout << "NIE" << endl;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (i) cout << ' ';
        cout << A[i];
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