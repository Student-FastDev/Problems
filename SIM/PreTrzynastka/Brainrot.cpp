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
const ll MAX_N = 2e5 + 1;
const ll MOD = 1e9 + 7;

const int B = 8;

int DP[B + 1][MAX_N];
int N, Q;

void updateFunction(int i, int r) {
    DP[0][i] = r;
    
    for (int j = 1; j <= B; ++j) {
        int currentLength = 1 << j;
        int halfLength = 1 << (j - 1);
        
        int startIndex = max(1, i - currentLength + 1);
        int endIndex = min(N - currentLength + 1, i);
        
        for (int k = startIndex; k <= endIndex; ++k) {
            DP[j][k] = abs(DP[j - 1][k] - DP[j - 1][k + halfLength]);
        }
    }
}

int queryFunction(int l, int k) {
    if (k <= B) {
        return DP[k][l];
    }
    
    int blocksCount = 1 << (k - B);
    int currentStep = 1 << B;
    
    int tempArray[1024];
    
    for (int x = 0; x < blocksCount; ++x) {
        tempArray[x] = DP[B][l + x * currentStep];
    }
    
    int currentCount = blocksCount;
    while (currentCount > 1) {
        for (int x = 0; x < currentCount / 2; ++x) {
            tempArray[x] = abs(tempArray[2 * x] - tempArray[2 * x + 1]);
        }
        currentCount /= 2;
    }
    
    return tempArray[0];
}

void solveTestCase() {
    cin >> N >> Q;
    
    for (int i = 1; i <= N; ++i) {
        cin >> DP[0][i];
    }
    
    for (int j = 1; j <= B; ++j) {
        int halfLength = 1 << (j - 1);
        int currentLength = 1 << j;
        int lengthLimit = N - currentLength + 1;
        
        for (int i = 1; i <= lengthLimit; ++i) {
            DP[j][i] = abs(DP[j - 1][i] - DP[j - 1][i + halfLength]);
        }
    }
    
    for (int q = 0; q < Q; ++q) {
        int currentType;
        cin >> currentType;
        if (currentType == 1) {
            int i, r;
            cin >> i >> r;
            updateFunction(i, r);
        } else {
            int l, k;
            cin >> l >> k;
            cout << queryFunction(l, k) << endl;
        }
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}