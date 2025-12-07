// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& out, auto pair) -> decltype(pair.first, out) { return out << '(' << pair.first << ", " << pair.second << ')'; }
auto operator<<(auto& out, auto container) -> decltype(container.end(), out) { out << '{'; int i = 2; for (auto element : container) out << (", ") + i << element, i = 0; return out << '}'; }
#define LOG(x...) cerr << "[" #x "]: ", [](auto... $) { ((cerr << $ << "; "), ...) << endl; }(x);
#else
#define LOG(x...) (void)0
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
const ll MOD = 1e9 + 7; // 998244353

void solveTestCase() {
    ll N;
    int K;
    cin >> N >> K;

    ll minimumRemainder = INF;
    int bestTypeIndex = -1;
    ll bestBoxCount = 0;

    for (int i = 1; i <= K; ++i) {
        ll currentCapacity;
        cin >> currentCapacity;

        ll currentRemainder = N % currentCapacity;
        if (currentRemainder < minimumRemainder) {
            minimumRemainder = currentRemainder;
            bestTypeIndex = i;
            bestBoxCount = N / currentCapacity;
        }
    }

    cout << bestTypeIndex << " " << bestBoxCount << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}