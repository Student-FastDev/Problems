// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& O, auto P) -> decltype(P.first, O) { return O << '(' << P.first << ", " << P.second << ')'; }
auto operator<<(auto& O, auto X) -> decltype(X.end(), O) { O << '{'; int i = 2; for (auto E : X) O << (", ") + i << E, i = 0; return O << '}'; }
#define LOG(X...) cerr << "[" #X "]: ", [](auto... $) { ((cerr << $ << "; "), ...) << endl; }(X);
#else
#define LOG(X...) (void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X) (X).begin(), (X).end()
#define endl '\n'
#define size(X) (X).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N;
    cin >> N;
    int activeSwitches = 0;
    for (int i = 0; i < 2 * N; ++i) {
        int switchState;
        cin >> switchState;
        activeSwitches += switchState;
    }

    int minimumOn = activeSwitches % 2;
    int maximumOn = min(activeSwitches, 2 * N - activeSwitches);

    cout << minimumOn << " " << maximumOn << endl;
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