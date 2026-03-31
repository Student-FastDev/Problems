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
typedef __int128 int128;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

string toString(int128 X) {
    if(X == 0) return "0";
    bool isNegative = false;
    if(X < 0) { isNegative = true; X = -X; }
    string S;
    while(X > 0) {
        S.push_back('0' + (int)(X % 10));
        X /= 10;
    }
    if(isNegative) S.push_back('-');
    reverse(S.begin(), S.end());
    return S;
}
 
inline int128 computeF(ll X, ll prefixValue, ll T) {
    ll R = T - prefixValue - X;
    int128 firstTerm = 0, secondTerm = 0, thirdTerm = 0;
    if(X >= 3) {
        firstTerm = (int128)X * (X - 1) * (X - 2) / 6;
    }
    if(X >= 2) {
        secondTerm = (int128)X * (X - 1) / 2 * (T - X);
    }
    thirdTerm = (int128)X * prefixValue * R;
    return firstTerm + secondTerm + thirdTerm;
}
 
bool isPossible(ll T, const vector<ll>& A) {
    ll prefix = 0;
    int N = size(A);

    for (int i = 0; i < N - 1; i++) {
        ll L = 0, R = T - prefix;
        ll best = -1;

        while (L <= R) {
            ll M = (L + R) / 2;
            if (computeF(M, prefix, T) >= A[i]) {
                best = M;
                R = M - 1;
            } else {
                L = M + 1;
            }
        }

        if (best == -1) return false;
        prefix += best;
        if (prefix > T) return false;
    }

    ll last = T - prefix;
    return computeF(last, prefix, T) >= A[N - 1];
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
 
    bool allZero = true;
    for(auto i : A){
        if(i != 0) {allZero = false; break;}
    }
    if(allZero){
        cout << 0 << endl;
        return;
    }
 
    ll L = 0, R = 1;
    while(!isPossible(R, A)) {
        R *= 2;
    }
 
    ll answerValue = R;
    while(L <= R) {
        ll M = L + (R - L) / 2;
        if(isPossible(M, A)) {
            answerValue = M;
            R = M - 1;
        } else {
            L = M + 1;
        }
    }
 
    cout << answerValue << endl;
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
