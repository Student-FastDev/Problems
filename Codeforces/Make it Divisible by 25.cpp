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
    int N = size(S);

    int minimumRemovals = N;
    vector<string> targetPatterns = {"00", "25", "50", "75"};

    for (string pattern : targetPatterns) {
        int secondDigitIndex = -1;
        for (int i = N - 1; i >= 0; --i) {
            if (S[i] == pattern[1]) {
                secondDigitIndex = i;
                break;
            }
        }

        if (secondDigitIndex == -1) continue;

        int firstDigitIndex = -1;
        for (int i = secondDigitIndex - 1; i >= 0; --i) {
            if (S[i] == pattern[0]) {
                firstDigitIndex = i;
                break;
            }
        }

        if (firstDigitIndex != -1) {
            int currentRemovals = (N - 1 - secondDigitIndex) + (secondDigitIndex - 1 - firstDigitIndex);
            if (currentRemovals < minimumRemovals) {
                minimumRemovals = currentRemovals;
            }
        }
    }

    cout << minimumRemovals << endl;
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