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
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    vector<int> prefixSumArray(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        prefixSumArray[i + 1] = prefixSumArray[i] + A[i];
    }

    for (int l = 1; l <= N - 2; ++l) {
        for (int r = l + 1; r <= N - 1; ++r) {
            int sumPart1 = prefixSumArray[l] % 3;
            int sumPart2 = (prefixSumArray[r] - prefixSumArray[l]) % 3;
            int sumPart3 = (prefixSumArray[N] - prefixSumArray[r]) % 3;

            bool areAllSame = (sumPart1 == sumPart2 && sumPart2 == sumPart3);
            bool areAllDistinct = (sumPart1 != sumPart2 && sumPart1 != sumPart3 && sumPart2 != sumPart3);

            if (areAllSame || areAllDistinct) {
                cout << l << " " << r << endl;
                return;
            }
        }
    }

    cout << 0 << " " << 0 << endl;
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