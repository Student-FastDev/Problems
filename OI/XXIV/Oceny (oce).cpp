// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(), (x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct SegmentTree {
    struct Node {
        int minValue;
        int countValue;
        int currentLazy;
    };

    vector<Node> treeArray;
    int treeSize;

    SegmentTree(int N) : treeSize(N) {
        treeArray.resize(4 * treeSize);
    }

    void buildTree(const vector<int>& differenceArray) {
        buildTree(1, 1, treeSize, differenceArray);
    }

    void updateRange(int L, int R, int value) {
        updateTree(1, 1, treeSize, L, R, value);
    }

    int getZeroCount() const {
        const Node& currentRoot = treeArray[1];
        return (currentRoot.minValue == 0 ? currentRoot.countValue : 0) + 1;
    }

private:
    void buildTree(int indexValue, int l, int r, const vector<int>& differenceArray) {
        treeArray[indexValue].currentLazy = 0;
        if (l == r) {
            treeArray[indexValue].minValue = differenceArray[l];
            treeArray[indexValue].countValue = 1;
            return;
        }
        int middleValue = (l + r) >> 1;
        buildTree(indexValue << 1, l, middleValue, differenceArray);
        buildTree(indexValue << 1 | 1, middleValue + 1, r, differenceArray);
        pullTree(indexValue);
    }

    void applyNode(int indexValue, int value) {
        treeArray[indexValue].minValue += value;
        treeArray[indexValue].currentLazy += value;
    }

    void pushNode(int indexValue) {
        if (treeArray[indexValue].currentLazy != 0) {
            applyNode(indexValue << 1, treeArray[indexValue].currentLazy);
            applyNode(indexValue << 1 | 1, treeArray[indexValue].currentLazy);
            treeArray[indexValue].currentLazy = 0;
        }
    }

    void updateTree(int indexValue, int l, int r, int L, int R, int value) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) {
            applyNode(indexValue, value);
            return;
        }
        pushNode(indexValue);
        int middleValue = (l + r) >> 1;
        updateTree(indexValue << 1, l, middleValue, L, R, value);
        updateTree(indexValue << 1 | 1, middleValue + 1, r, L, R, value);
        pullTree(indexValue);
    }

    void pullTree(int indexValue) {
        const Node &L = treeArray[indexValue << 1], &R = treeArray[indexValue << 1 | 1];
        treeArray[indexValue].minValue = min(L.minValue, R.minValue);
        treeArray[indexValue].countValue = 0;
        if (treeArray[indexValue].minValue == L.minValue) treeArray[indexValue].countValue += L.countValue;
        if (treeArray[indexValue].minValue == R.minValue) treeArray[indexValue].countValue += R.countValue;
    }
};

void solveTestCase() {
    int N, Z;
    cin >> N >> Z;

    vector<int> P(N + 1), positionArray(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> P[i];
        positionArray[P[i]] = i;
    }

    vector<int> differenceArray(max(1, N));
    if (N > 1) {
        differenceArray.assign(N, 0);
        for (int v = 1; v <= N; v++) {
            if (positionArray[v] > v) {
                differenceArray[v] += 1;
                differenceArray[positionArray[v]] -= 1;
            }
        }
        int currentValue = 0;
        for (int i = 1; i < N; i++) {
            currentValue += differenceArray[i];
            differenceArray[i] = currentValue;
        }
    }

    SegmentTree segmentArray(max(1, N - 1));
    if (N > 1) segmentArray.buildTree(differenceArray);

    cout << (N == 1 ? 1 : segmentArray.getZeroCount()) << endl;

    while (Z-- > 1) {
        int firstPosition, secondPosition;
        cin >> firstPosition >> secondPosition;
        int X = P[firstPosition], Y = P[secondPosition];

        auto removeContribution = [&](int value, int oldPosition) {
            if (oldPosition > value) {
                segmentArray.updateRange(value, oldPosition - 1, -1);
            }
        };
        removeContribution(X, positionArray[X]);
        removeContribution(Y, positionArray[Y]);

        swap(P[firstPosition], P[secondPosition]);
        swap(positionArray[X], positionArray[Y]);

        auto addContribution = [&](int value, int newPos) {
            if (newPos > value) {
                segmentArray.updateRange(value, newPos - 1, +1);
            }
        };
        addContribution(X, positionArray[X]);
        addContribution(Y, positionArray[Y]);

        cout << segmentArray.getZeroCount() << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }

    return 0;
}
