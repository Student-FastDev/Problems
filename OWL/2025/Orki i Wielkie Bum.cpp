#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto& o, auto p)->decltype(p.first, o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto& o, auto x)->decltype(x.end(), o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll, ll> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define sz(x)   (ll)x.size()

const ll INF = 1e18 / 2;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

class SegmentTree {
private:
    struct Node {
        ll minValue;
        int firstIndex;
        ll lazy;
        Node() : minValue(INF), firstIndex(-1), lazy(0) {}
    };

    int N;
    vector<Node> tree;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node].minValue = INF;
            tree[node].firstIndex = l;
            return;
        }
        int mid = (l + r) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        tree[node].minValue = min(tree[2*node].minValue, tree[2*node+1].minValue);
        tree[node].firstIndex = (tree[2*node].minValue <= tree[2*node+1].minValue) ? tree[2*node].firstIndex : tree[2*node+1].firstIndex;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0) return;
        tree[node].minValue += tree[node].lazy;
        if (l != r) {
            tree[2*node].lazy += tree[node].lazy;
            tree[2*node+1].lazy += tree[node].lazy;
        }
        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ul, int ur, ll val) {
        push(node, l, r);
        if (r < ul || l > ur) return;
        if (ul <= l && r <= ur) {
            tree[node].lazy += val;
            push(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(2*node, l, mid, ul, ur, val);
        update(2*node+1, mid+1, r, ul, ur, val);
        tree[node].minValue = min(tree[2*node].minValue, tree[2*node+1].minValue);
        tree[node].firstIndex = (tree[2*node].minValue <= tree[2*node+1].minValue) ? tree[2*node].firstIndex : tree[2*node+1].firstIndex;
    }

public:
    SegmentTree(int size) : N(size) {
        tree.resize(4 * N);
        build(1, 0, N-1);
    }

    void addRange(int l, int r, ll value) {
        update(1, 0, N-1, l, r, value);
    }

    pii minimumValue() {
        push(1, 0, N-1);
        if (tree[1].minValue > 1e12) {
            return {-1, -1};
        } else {
            return {tree[1].firstIndex, tree[1].minValue};
        }
    }
};

struct moduleVariable {
    ll firstB, firstR, secondB, secondR;
    moduleVariable(ll A, ll B, ll C, ll D) {
        firstB = A; firstR = B; secondB = C; secondR = D;
    }
};

void solveTestCase() {
    ll N;
    cin >> N;

    vector<moduleVariable> moduleArray;

    for(ll i = 0; i < N; i++) {
        ll A, B, C, D;
        cin >> A >> B >> C >> D;

        if(B - A > D - C) { swap(B, D); swap(A, C); }
        if(C <= A) { A = C; B = D; }

        moduleVariable tempModule(A, B, C, D);
        moduleArray.push_back(tempModule);
    }

    SegmentTree changeTree(N);
    ll treeSize = N-1;

    ll changeValue = 0;
    ll finalCost = 0;

    auto restFunction = [&](ll value) {
        return value - finalCost - changeValue;
    };

    for(ll i = 0; i < N; i++) {
        pii minIndex = changeTree.minimumValue();
        while(minIndex.first != -1 && minIndex.second <= restFunction(moduleArray[i].firstB)) {
            changeTree.addRange(minIndex.first, minIndex.first, INF);
            if(minIndex.second > 0) {
                changeTree.addRange(0, treeSize, -minIndex.second);
                finalCost += minIndex.second;
            }
            ll differenceValue = moduleArray[minIndex.first].secondR - moduleArray[minIndex.first].secondB - moduleArray[minIndex.first].firstR + moduleArray[minIndex.first].firstB;
            changeTree.addRange(minIndex.first, treeSize, -differenceValue);
            changeValue += differenceValue;
            minIndex = changeTree.minimumValue();
        }
        if(restFunction(moduleArray[i].firstB) > 0) {
            changeTree.addRange(0, treeSize, -restFunction(moduleArray[i].firstB));
            finalCost += restFunction(moduleArray[i].firstB);
        }
        ll differenceValue = moduleArray[i].firstR - moduleArray[i].firstB;
        changeTree.addRange(i+1, treeSize, -differenceValue);
        changeValue += differenceValue;
        changeTree.addRange(i, i, -(INF) + moduleArray[i].secondB);
        cout << finalCost << " ";
    }

    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    ll T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
