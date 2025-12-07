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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    string S;
    cin >> S;

    int stringLength = size(S);
    int firstOneIndex = -1;
    int lastOneIndex = -1;

    for (int i = 0; i < stringLength; ++i) {
        if (S[i] == '1') {
            if (firstOneIndex == -1) {
                firstOneIndex = i;
            }
            lastOneIndex = i;
        }
    }

    if (firstOneIndex == -1) {
        cout << 0 << endl;
        return;
    }

    int erasedZerosCount = 0;
    for (int i = firstOneIndex; i <= lastOneIndex; ++i) {
        if (S[i] == '0') {
            erasedZerosCount++;
        }
    }

    cout << erasedZerosCount << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}