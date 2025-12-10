// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.rightRange(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).rightRange()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct Element {
    ll H;
    int index;
};

struct Node {
    ll maxArea;
    vector<Element> prefix;
    vector<Element> suffix;
    bool empty;

    Node() : maxArea(0), empty(true) {}
};

Node mergeNodes(const Node& left, const Node& right) {
    if (left.empty) return right;
    if (right.empty) return left;

    Node finalResult;
    finalResult.empty = false;
    
    finalResult.maxArea = max(left.maxArea, right.maxArea);

    int rightPointer = -1;
    for (auto& s : left.suffix) {
        while (rightPointer + 1 < (int)size(right.prefix) && right.prefix[rightPointer + 1].H >= s.H) {
            rightPointer++;
        }
        if (rightPointer != -1) {
            finalResult.maxArea = max(finalResult.maxArea, s.H * (right.prefix[rightPointer].index - s.index + 1));
        }
    }

    int leftPointer = -1;
    for (auto& p : right.prefix) {
        while (leftPointer + 1 < (int)size(left.suffix) && left.suffix[leftPointer + 1].H >= p.H) {
            leftPointer++;
        }
        if (leftPointer != -1) {
            finalResult.maxArea = max(finalResult.maxArea, p.H * (p.index - left.suffix[leftPointer].index + 1));
        }
    }

    finalResult.prefix = left.prefix;
    ll currentMin = left.prefix.empty() ? 2e18 : left.prefix.back().H;
    
    for (auto& p : right.prefix) {
        ll H = min(currentMin, p.H);
        if (finalResult.prefix.empty() || H < finalResult.prefix.back().H) {
            finalResult.prefix.push_back({H, p.index});
        } else {
            finalResult.prefix.back().index = p.index;
        }
    }

    finalResult.suffix = right.suffix;
    currentMin = right.suffix.empty() ? 2e18 : right.suffix.back().H;
    
    for (auto& s : left.suffix) {
        ll H = min(currentMin, s.H);
        if (finalResult.suffix.empty() || H < finalResult.suffix.back().H) {
            finalResult.suffix.push_back({H, s.index});
        } else {
            finalResult.suffix.back().index = s.index;
        }
    }

    return finalResult;
}

int N, Q;
vector<ll> H;
vector<Node> treeArray;

void buildTree(int node, int leftRange, int rightRange) {
    if (leftRange == rightRange) {
        treeArray[node].maxArea = H[leftRange];
        treeArray[node].prefix = {{H[leftRange], leftRange}};
        treeArray[node].suffix = {{H[leftRange], leftRange}};
        treeArray[node].empty = false;
    } else {
        int middleValue = (leftRange + rightRange) / 2;
        buildTree(2 * node, leftRange, middleValue);
        buildTree(2 * node + 1, middleValue + 1, rightRange);
        treeArray[node] = mergeNodes(treeArray[2 * node], treeArray[2 * node + 1]);
    }
}

void updateTree(int node, int leftRange, int rightRange, int index, ll value) {
    if (leftRange == rightRange) {
        treeArray[node].maxArea = value;
        treeArray[node].prefix = {{value, leftRange}};
        treeArray[node].suffix = {{value, leftRange}};
        return;
    }
    int middleValue = (leftRange + rightRange) / 2;
    if (index <= middleValue) updateTree(2 * node, leftRange, middleValue, index, value);
    else updateTree(2 * node + 1, middleValue + 1, rightRange, index, value);
    
    treeArray[node] = mergeNodes(treeArray[2 * node], treeArray[2 * node + 1]);
}

Node queryTree(int node, int leftRange, int rightRange, int left, int right) {
    if (right < leftRange || rightRange < left) return Node();
    if (left <= leftRange && rightRange <= right) return treeArray[node];
    
    int middleValue = (leftRange + rightRange) / 2;
    Node firstNode = queryTree(2 * node, leftRange, middleValue, left, right);
    Node secondNode = queryTree(2 * node + 1, middleValue + 1, rightRange, left, right);
    
    return mergeNodes(firstNode, secondNode);
}

void solveTestCase() {
    cin >> N;

    H.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> H[i];
    }

    treeArray.resize(4 * N + 1);
    buildTree(1, 1, N);

    cin >> Q;
    while (Q--) {
        int queryType;
        cin >> queryType;
        if (queryType == 1) {
            int left, right;
            cin >> left >> right;
            cout << queryTree(1, 1, N, left, right).maxArea << endl;
        } else {
            int p;
            ll x;
            cin >> p >> x;
            updateTree(1, 1, N, p, x);
        }
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
