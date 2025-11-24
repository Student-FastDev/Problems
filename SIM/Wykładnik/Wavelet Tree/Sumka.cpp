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
    vector<ll> prefAll;
    vector<ll> prefLeft;

    WaveletTree(vector<int>::iterator fromArray, vector<int>::iterator toArray, int X, int Y) {
        leftRange = X; rightValue = Y;
        if (fromArray >= toArray) return;
        int n = distance(fromArray, toArray);
        B.reserve(n + 1); B.push_back(0);
        prefAll.reserve(n + 1); prefAll.push_back(0);
        prefLeft.reserve(n + 1); prefLeft.push_back(0);

        if (leftRange == rightValue) {
            for (auto i = fromArray; i != toArray; ++i) {
                B.push_back(B.back() + 1);
                prefAll.push_back(prefAll.back() + *i);
                prefLeft.push_back(prefLeft.back() + *i);
            }
            return;
        }

        int middleValue = (leftRange + rightValue) >> 1;
        vector<int> leftPart, rightPart;
        leftPart.reserve(n / 2 + 1);
        rightPart.reserve(n / 2 + 1);

        for (auto i = fromArray; i != toArray; ++i) {
            bool isLeft = ((*i) <= middleValue);
            B.push_back(B.back() + (isLeft ? 1 : 0));
            prefAll.push_back(prefAll.back() + *i);
            prefLeft.push_back(prefLeft.back() + (isLeft ? *i : 0));
            if (isLeft) leftPart.push_back(*i);
            else rightPart.push_back(*i);
        }

        if (!leftPart.empty()) left = new WaveletTree(leftPart.begin(), leftPart.end(), leftRange, middleValue);
        if (!rightPart.empty()) right = new WaveletTree(rightPart.begin(), rightPart.end(), middleValue + 1, rightValue);
    }

    ll sumKLargest(int l, int r, int k) {
        if (l > r || k <= 0) return 0;
        if (leftRange == rightValue) {
            int cnt = r - l + 1;
            int take = min(k, cnt);
            return (ll)leftRange * (ll)take;
        }
        int leftCount = B[r] - B[l - 1];
        int total = r - l + 1;
        int rightCount = total - leftCount;

        if (rightCount == 0) {
            int nL = B[l - 1] + 1;
            int nR = B[r];
            return left->sumKLargest(nL, nR, k);
        }
        if (rightCount >= k) {
            int nL = l - B[l - 1];
            int nR = r - B[r];
            return right->sumKLargest(nL, nR, k);
        } else {
            ll sumAll = prefAll[r] - prefAll[l - 1];
            ll sumLeft = prefLeft[r] - prefLeft[l - 1];
            ll sumRight = sumAll - sumLeft;

            int nL_left = B[l - 1] + 1;
            int nR_left = B[r];
            ll takeFromLeft = left ? left->sumKLargest(nL_left, nR_left, k - rightCount) : 0;
            return sumRight + takeFromLeft;
        }
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
        int take = min(k, length);
        ll answer = wt.sumKLargest(l, r, take);
        cout << answer << endl;
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
