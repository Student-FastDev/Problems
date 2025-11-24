// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto X)->decltype(X.end(),o){o<<'{';int i=2;for(auto e:X)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X);
#else
#define LOG(X...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(X)  (X).begin(),(X).end()
#define endl    '\n'
#define size(X)  X.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct WaveletTree {
    int leftRange, rightValue;
    WaveletTree *left = nullptr, *right = nullptr;
    vector<int> B;

    WaveletTree(vector<int>::iterator fromArray, vector<int>::iterator toArray, int X, int Y) {
        leftRange = X; rightValue = Y;
        if (fromArray >= toArray) return;
        if (leftRange == rightValue) {
            B.reserve(distance(fromArray, toArray) + 1);
            B.push_back(0);
            for (auto i = fromArray; i != toArray; ++i) B.push_back(B.back() + 1);
            return;
        }

        int middleValue = (leftRange + rightValue) >> 1;
        B.reserve(distance(fromArray, toArray) + 1);
        B.push_back(0);
        vector<int> leftPart, rightPart;
        leftPart.reserve(distance(fromArray, toArray) / 2 + 1);
        rightPart.reserve(distance(fromArray, toArray) / 2 + 1);

        for (auto i = fromArray; i != toArray; ++i) {
            B.push_back(B.back() + ((*i) <= middleValue));
            if ((*i) <= middleValue) leftPart.push_back(*i);
            else rightPart.push_back(*i);
        }

        if (!leftPart.empty()) left = new WaveletTree(leftPart.begin(), leftPart.end(), leftRange, middleValue);
        if (!rightPart.empty()) right = new WaveletTree(rightPart.begin(), rightPart.end(), middleValue + 1, rightValue);
    }

    void report(int l, int r, int margin, vector<int> &outArray) {
        if (l > r) return;
        if (leftRange == rightValue) {
            if (r - l + 1 > margin) outArray.push_back(leftRange);
            return;
        }
        int leftCount = B[r] - B[l - 1];
        if (leftCount > margin && left) {
            int nL = B[l - 1] + 1;
            int nR = B[r];
            left->report(nL, nR, margin, outArray);
        }
        int rightCount = (r - l + 1) - leftCount;
        if (rightCount > margin && right) {
            int nL = l - B[l - 1];
            int nR = r - B[r];
            right->report(nL, nR, margin, outArray);
        }
    }

    ~WaveletTree() {
        delete left;
        delete right;
    }
};

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    int maxV = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        maxV = max(maxV, A[i]);
    }
    int domainL = 1, domainR = max(maxV, 1);

    vector<int> array = A;
    WaveletTree wt(array.begin(), array.end(), domainL, domainR);

    for (int i = 0; i < Q; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        int length = r - l + 1;
        int margin = length / k;
        vector<int> candidates;
        wt.report(l, r, margin, candidates);
        if (candidates.empty()) {
            cout << -1 << endl;
        } else {
            int answer = *min_element(candidates.begin(), candidates.end());
            cout << answer << endl;
        }
    }

    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
