// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N, K;
    cin >> N >> K;

    vector<ll> sequenceB(N);
    ll currentProduct = 1;
    for (int i = 0; i < N; ++i) {
        cin >> sequenceB[i];
        currentProduct *= sequenceB[i];
    }

    if (2023 % currentProduct != 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        ll missingValue = 2023 / currentProduct;
        cout << missingValue;
        for (int i = 0; i < K - 1; ++i) {
            cout << " " << 1;
        }
        cout << endl;
    }
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