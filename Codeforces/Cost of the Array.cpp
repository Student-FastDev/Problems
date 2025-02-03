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
    int N, K;
    cin >> N >> K;
    vector<int> valuesArray(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> valuesArray[i];
    }

    auto findAnswerValue = [&]() -> int {
        for (int i = 2; i <= N; i += 2) {
            if (valuesArray[i] != i / 2) {
                return i / 2;
            }
        }
        return N / 2 + 1;
    };

    auto findPositionValue = [&]() -> int {
        for (int i = 2; i <= N - K + 2; i++) {
            if (valuesArray[i] != 1) {
                return i;
            }
        }
        return -1;
    };

    auto findCurrentValue = [&]() -> int {
        int current = 2;
        for (int i = N - K + 1; i <= N; i += 2) {
            if (valuesArray[i] != current) {
                break;
            }
            current++;
        }
        return current;
    };

    if (N == K) {
        cout << findAnswerValue() << endl;
    } else {
        int positionValue = findPositionValue();
        if (positionValue == -1) {
            cout << findCurrentValue() << endl;
        } else {
            cout << 1 << endl;
        }
    }
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
