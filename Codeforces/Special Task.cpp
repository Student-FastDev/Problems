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
    string S;
    cin >> S;

    ll questionMarkCount = 0;
    int seenLettersMask = 0;
    for (char c : S) {
        if (c == '?') {
            questionMarkCount++;
        } else if (c >= 'A' && c <= 'J') {
            seenLettersMask |= (1 << (c - 'A'));
        }
    }

    int uniqueLetterCount = 0;
    for (int i = 0; i < 10; ++i) {
        if ((seenLettersMask >> i) & 1) uniqueLetterCount++;
    }

    auto getPermutations = [&](int n, int k) -> ll {
        if (k < 0 || k > n) return 0;
        ll result = 1;
        for (int i = 0; i < k; ++i) {
            result *= (n - i);
        }
        return result;
    };

    ll ways = 0;
    ll exponent = 0;

    if (isdigit(S[0])) {
        ways = getPermutations(10, uniqueLetterCount);
        exponent = questionMarkCount;
    } else if (S[0] == '?') {
        ways = getPermutations(10, uniqueLetterCount) * 9;
        exponent = questionMarkCount - 1;
    } else {
        ways = getPermutations(9, uniqueLetterCount - 1) * 9;
        exponent = questionMarkCount;
    }

    cout << ways;
    for (int i = 0; i < exponent; ++i) cout << '0';
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