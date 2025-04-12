#include <bits/stdc++.h>
using namespace std;

#define size(x) x.size()
typedef long long ll;

struct FenwickTree {
    vector<ll> treeArray;

    FenwickTree(int size) {
        treeArray.resize(size + 2, 0);
    }

    void updateTree(int positionValue, ll valueValue) {
        for (; positionValue < (int) size(treeArray); positionValue += positionValue & -positionValue) {
            treeArray[positionValue] += valueValue;
        }
    }

    ll queryTree(int positionValue) {
        ll sumValue = 0;
        for (; positionValue > 0; positionValue -= positionValue & -positionValue) {
            sumValue += treeArray[positionValue];
        }
        return sumValue;
    }

    ll rangeQuery(int L, int R) {
        return queryTree(R) - queryTree(L - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    vector<ll> B(N);
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }

    FenwickTree fenwickX(N), fenwickXS(N);
    ll resultValue = 0;

    for (int i = N; i >= 1; i--) {
        int S = max(1, i - K + 1);
        int T = i - S + 1;

        ll sumX = fenwickX.rangeQuery(S, i);
        ll sumXS = fenwickXS.rangeQuery(S, i);
        ll currentValue = sumX * (i + 1) - sumXS;

        if (currentValue >= B[i - 1]) {
            continue;
        }

        ll neededValue = B[i - 1] - currentValue;
        ll X = (neededValue + T - 1) / T;
        resultValue += X;

        fenwickX.updateTree(S, X);
        fenwickXS.updateTree(S, X * S);

        if (S + K <= N) {
            fenwickX.updateTree(S + K, -X);
            fenwickXS.updateTree(S + K, -X * S);
        }
    }

    cout << resultValue << endl;
    return 0;
}
