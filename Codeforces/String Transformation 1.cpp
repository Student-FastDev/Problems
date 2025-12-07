// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& o, auto p) -> decltype(p.first, o) { return o << '(' << p.first << ", " << p.second << ')'; }
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) { o << '{'; int i = 2; for (auto e : x) o << (", ") + i << e, i = 0; return o << '}'; }
#define LOG(x...) cerr << "[" #x "]: ", [](auto... $) { ((cerr << $ << "; "), ...) << endl; }(x);
#else
#define LOG(x...) (void)0
#endif

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7; // 998244353

void solveTestCase() {
    int N;
    cin >> N;
    string stringA, stringB;
    cin >> stringA >> stringB;

    vector<int> adjacencyMask(20, 0);
    bool isPossible = true;

    for (int i = 0; i < N; ++i) {
        if (stringA[i] > stringB[i]) {
            isPossible = false;
            break;
        }
        if (stringA[i] < stringB[i]) {
            adjacencyMask[stringA[i] - 'a'] |= (1 << (stringB[i] - 'a'));
        }
    }

    if (!isPossible) {
        cout << -1 << endl;
        return;
    }

    int totalMoves = 0;
    for (int i = 0; i < 20; ++i) {
        if (adjacencyMask[i] == 0) continue;

        int targetChar = __builtin_ctz(adjacencyMask[i]);
        totalMoves++;

        int remainingRequirements = adjacencyMask[i] ^ (1 << targetChar);
        adjacencyMask[targetChar] |= remainingRequirements;
    }

    cout << totalMoves << endl;
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