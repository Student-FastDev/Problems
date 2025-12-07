// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    priority_queue<ll, vector<ll>, greater<ll>> valuesMinHeap;
    for (int i = 0; i < N; ++i) {
        ll whiteboardValue;
        cin >> whiteboardValue;
        valuesMinHeap.push(whiteboardValue);
    }

    for (int i = 0; i < M; ++i) {
        ll operationValue;
        cin >> operationValue;
        valuesMinHeap.pop();
        valuesMinHeap.push(operationValue);
    }

    ll totalSum = 0;
    while (!valuesMinHeap.empty()) {
        totalSum += valuesMinHeap.top();
        valuesMinHeap.pop();
    }
    cout << totalSum << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}