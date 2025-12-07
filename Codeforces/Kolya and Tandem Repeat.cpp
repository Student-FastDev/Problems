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
    string inputString;
    cin >> inputString;
    int K;
    cin >> K;

    int N = size(inputString);
    int totalLength = N + K;
    int maxTandemLength = 0;

    for (int length = 1; length * 2 <= totalLength; ++length) {
        for (int startIndex = 0; startIndex + 2 * length <= totalLength; ++startIndex) {
            bool possible = true;
            for (int offset = 0; offset < length; ++offset) {
                int index1 = startIndex + offset;
                int index2 = startIndex + length + offset;
                
                if (index1 < N && index2 < N) {
                    if (inputString[index1] != inputString[index2]) {
                        possible = false;
                        break;
                    }
                }
            }
            if (possible) {
                maxTandemLength = max(maxTandemLength, 2 * length);
            }
        }
    }
    cout << maxTandemLength << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}