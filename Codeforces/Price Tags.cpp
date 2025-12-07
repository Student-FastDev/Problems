// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& o, auto p) -> decltype(p.first, o) {
    return o << '(' << p.first << ", " << p.second << ')';
}
auto operator<<(auto& o, auto x) -> decltype(x.end(), o) {
    o << '{';
    int i = 2;
    for (auto e : x) o << (", ") + i << e, i = 0;
    return o << '}';
}
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
const int MAX_VALUE = 200010;
const ll MOD = 1e9 + 7;

int frequencyArray[MAX_VALUE];
int prefixSumArray[MAX_VALUE];

void solveTestCase() {
    int N;
    ll Y;
    cin >> N >> Y;

    vector<int> costValues(N);
    int maximumValue = 0;
    for (int i = 0; i < N; ++i) {
        cin >> costValues[i];
        maximumValue = max(maximumValue, costValues[i]);
    }

    for (int i = 0; i <= maximumValue + 5; ++i) {
        frequencyArray[i] = 0;
        prefixSumArray[i] = 0;
    }

    for (int value : costValues) {
        frequencyArray[value]++;
    }

    for (int i = 1; i <= maximumValue + 2; ++i) {
        prefixSumArray[i] = prefixSumArray[i - 1] + frequencyArray[i];
    }

    ll maximumIncome = -INF;

    for (int x = 2; x <= maximumValue + 1; ++x) {
        ll currentSumPrices = 0;
        ll currentOverlap = 0;

        for (int k = 1;; ++k) {
            ll leftBound = (ll)(k - 1) * x + 1;
            if (leftBound > maximumValue) break;

            ll rightBound = (ll)k * x;
            if (rightBound > maximumValue) rightBound = maximumValue;

            int countInRange = prefixSumArray[(int)rightBound] - prefixSumArray[(int)leftBound - 1];

            if (countInRange > 0) {
                currentSumPrices += (ll)countInRange * k;
                int availableItems = (k <= maximumValue) ? frequencyArray[k] : 0;
                currentOverlap += min(countInRange, availableItems);
            }
        }

        ll tagsToPrint = N - currentOverlap;
        ll currentIncome = currentSumPrices - tagsToPrint * Y;
        if (currentIncome > maximumIncome) {
            maximumIncome = currentIncome;
        }
    }

    cout << maximumIncome << endl;
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