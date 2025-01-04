#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

struct SegmentNode {
    ll count, maxValue, minPrefix, maxPrefix, minSuffix, maxSuffix;

    SegmentNode() : count(0), maxValue(0), minPrefix(0), maxPrefix(0), minSuffix(0), maxSuffix(0) {}

    SegmentNode(ll value) {
        count = 1;
        maxValue = 0;
        minPrefix = minSuffix = value + 1;
        maxPrefix = maxSuffix = value - 1;
    }

    SegmentNode(const SegmentNode &left, const SegmentNode &right) {
        count = left.count + right.count;
        minPrefix = min(left.minPrefix, left.count + right.minPrefix);
        maxPrefix = max(left.maxPrefix, right.maxPrefix - left.count);
        minSuffix = min(right.minSuffix, right.count + left.minSuffix);
        maxSuffix = max(right.maxSuffix, left.maxSuffix - right.count);
        maxValue = max({left.maxValue, right.maxValue, -left.minSuffix + right.maxPrefix + 1, left.maxSuffix - right.minPrefix + 1});
    }
};

class SegmentTree {
    vector<SegmentNode> tree;
    int size;

    void updateTree(int index, ll value, int node, int start, int end) {
        if (start == end) {
            tree[node] = SegmentNode(value);
            return;
        }
        int mid = (start + end) / 2;
        if (index <= mid) {
            updateTree(index, value, 2 * node + 1, start, mid);
        } else {
            updateTree(index, value, 2 * node + 2, mid + 1, end);
        }
        tree[node] = SegmentNode(tree[2 * node + 1], tree[2 * node + 2]);
    }

public:
    SegmentTree(int N) : size(N) {
        tree.resize(4 * N);
    }

    void update(int index, ll value) {
        updateTree(index, value, 0, 0, size - 1);
    }

    ll getMaxValue() const {
        return tree[0].maxValue;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;

        SegmentTree segmentTree(N);

        for (int i = 0; i < N; ++i) {
            int value;
            cin >> value;
            segmentTree.update(i, value);
        }

        cout << segmentTree.getMaxValue() << "\n";

        while (Q--) {
            int index, value;
            cin >> index >> value;
            segmentTree.update(index - 1, value);
            cout << segmentTree.getMaxValue() << "\n";
        }
    }
    return 0;
}
