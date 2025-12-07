// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> elementsArray(N);
    for (int i = 0; i < N; ++i) cin >> elementsArray[i];

    int maxElementAll = 0;
    for (int element : elementsArray) maxElementAll = max(maxElementAll, element);

    if (N % 2 == 0) {
        cout << maxElementAll + N / 2 << endl;
    } else {
        int maxElementOddIndices = 0;
        for (int i = 0; i < N; i += 2) {
            maxElementOddIndices = max(maxElementOddIndices, elementsArray[i]);
        }
        int firstScore = maxElementOddIndices + (N + 1) / 2;
        int secondScore = maxElementAll + N / 2;
        cout << max(firstScore, secondScore) << endl;
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