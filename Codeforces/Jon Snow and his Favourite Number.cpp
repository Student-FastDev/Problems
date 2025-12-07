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

#define all(x)  (x).begin(), (x).end()
#define endl    '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int numberOfRangers, operationsCount, favoriteNumber;
    if (!(cin >> numberOfRangers >> operationsCount >> favoriteNumber)) return;

    vector<int> strengthCounts(1024, 0);
    for (int i = 0; i < numberOfRangers; ++i) {
        int strengthValue;
        cin >> strengthValue;
        strengthCounts[strengthValue]++;
    }

    vector<int> nextStrengthCounts(1024);

    for (int k = 0; k < operationsCount; ++k) {
        fill(all(nextStrengthCounts), 0);
        int currentParity = 0;

        for (int v = 0; v < 1024; ++v) {
            int rangerCount = strengthCounts[v];
            if (rangerCount > 0) {
                int numberXor = 0;
                int numberKeep = 0;

                if (currentParity == 0) {
                    numberXor = (rangerCount + 1) / 2;
                    numberKeep = rangerCount / 2;
                } else {
                    numberXor = rangerCount / 2;
                    numberKeep = (rangerCount + 1) / 2;
                }

                nextStrengthCounts[v ^ favoriteNumber] += numberXor;
                nextStrengthCounts[v] += numberKeep;

                currentParity ^= (rangerCount & 1);
            }
        }
        swap(strengthCounts, nextStrengthCounts);
    }

    int minStrength = -1;
    int maxStrength = -1;
    for (int i = 0; i < 1024; ++i) {
        if (strengthCounts[i] > 0) {
            if (minStrength == -1) minStrength = i;
            maxStrength = i;
        }
    }

    cout << maxStrength << " " << minStrength << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while (T--) {
        solveTestCase();
    }
    return 0;
}