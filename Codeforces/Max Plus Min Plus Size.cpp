// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct Node {
    ll m00, m01, m10, m11;
    ll s00, s01, s10, s11;
};

Node merge(const Node& leftNode, const Node& rightNode) {
    Node result;
    
    result.m00 = max({leftNode.m00 + rightNode.m00, leftNode.m00 + rightNode.m10, leftNode.m01 + rightNode.m00});
    result.m01 = max({leftNode.m00 + rightNode.m01, leftNode.m00 + rightNode.m11, leftNode.m01 + rightNode.m01});
    result.m10 = max({leftNode.m10 + rightNode.m00, leftNode.m10 + rightNode.m10, leftNode.m11 + rightNode.m00});
    result.m11 = max({leftNode.m10 + rightNode.m01, leftNode.m10 + rightNode.m11, leftNode.m11 + rightNode.m01});

    ll specialInLeft = max({leftNode.s00 + rightNode.m00, leftNode.s00 + rightNode.m10, leftNode.s01 + rightNode.m00});
    result.s00 = specialInLeft;
    result.s01 = max({leftNode.s00 + rightNode.m01, leftNode.s00 + rightNode.m11, leftNode.s01 + rightNode.m01});
    result.s10 = max({leftNode.s10 + rightNode.m00, leftNode.s10 + rightNode.m10, leftNode.s11 + rightNode.m00});
    result.s11 = max({leftNode.s10 + rightNode.m01, leftNode.s10 + rightNode.m11, leftNode.s11 + rightNode.m01});

    result.s00 = max({result.s00, leftNode.m00 + rightNode.s00, leftNode.m00 + rightNode.s10, leftNode.m01 + rightNode.s00});
    result.s01 = max({result.s01, leftNode.m00 + rightNode.s01, leftNode.m00 + rightNode.s11, leftNode.m01 + rightNode.s01});
    result.s10 = max({result.s10, leftNode.m10 + rightNode.s00, leftNode.m10 + rightNode.s10, leftNode.m11 + rightNode.s00});
    result.s11 = max({result.s11, leftNode.m10 + rightNode.s01, leftNode.m10 + rightNode.s11, leftNode.m11 + rightNode.s01});

    return result;
}

vector<Node> segmentTree;
int treeSize;

void update(int position, bool active, bool special) {
    int idx = treeSize + position;
    if (!active) {
        segmentTree[idx] = {0, -INF, -INF, -INF, -INF, -INF, -INF, -INF};
    } else {
        segmentTree[idx] = {0, -INF, -INF, 1, -INF, -INF, -INF, (special ? 1 : -INF)};
    }
    for (idx /= 2; idx; idx /= 2) {
        segmentTree[idx] = merge(segmentTree[2 * idx], segmentTree[2 * idx + 1]);
    }
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<ll> A(N);
    map<ll, vector<int>> positions;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        positions[A[i]].push_back(i);
    }

    treeSize = 1;
    while (treeSize < N) treeSize *= 2;
    segmentTree.assign(2 * treeSize, {0, -INF, -INF, -INF, -INF, -INF, -INF, -INF});

    vector<ll> distinctValues;
    for (auto& p : positions) distinctValues.push_back(p.first);
    sort(all(distinctValues), greater<ll>());

    ll bestScore = 0;
    vector<bool> removed(N, false);

    for (ll M : distinctValues) {
        if (2 * M + N + 5 < bestScore) break;

        for (int i = 0; i < 2 * treeSize; ++i) {
            segmentTree[i] = {0, -INF, -INF, -INF, -INF, -INF, -INF, -INF};
        }

        auto itStart = lower_bound(all(distinctValues), M, greater<ll>());

        for (auto it = itStart; it != distinctValues.end(); ++it) {
            ll X = *it;
            for (int idx : positions[X]) {
                if (!removed[idx]) {
                    update(idx, true, (X == M));
                }
            }
            
            Node root = segmentTree[1];
            ll currentSize = max({root.s00, root.s01, root.s10, root.s11});
            
            if (currentSize > -INF / 2) {
                bestScore = max(bestScore, M + X + currentSize);
            }
        }

        for (int idx : positions[M]) {
            removed[idx] = true;
        }
    }

    cout << bestScore << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}