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
    vector<ll> A(N + 1);
    A[0] = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    vector<ll> diffArray(N);
    for (int i = 0; i < N; ++i) {
        diffArray[i] = A[i + 1] - A[i];
    }

    vector<int> possibleLengths;
    for (int k = 1; k <= N; ++k) {
        bool isValid = true;
        for (int i = 0; i < N - k; ++i) {
            if (diffArray[i] != diffArray[i + k]) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            possibleLengths.push_back(k);
        }
    }

    cout << size(possibleLengths) << endl;
    for (int i = 0; i < size(possibleLengths); ++i) {
        cout << possibleLengths[i] << (i == size(possibleLengths) - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}