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
const ll MAX_N = 200005;
const ll MOD = 1e9+7; 

struct Node {
    int prio;
    int cnt;
    ll val;
    ll sum;
    ll lazy;
    Node *l, *r;
    Node(ll v) : prio((int)rng()), cnt(1), val(v), sum(v), lazy(0), l(nullptr), r(nullptr) {}
};

int getCnt(Node* t) { return t ? t->cnt : 0; }
ll getSum(Node* t) { return t ? t->sum : 0; }

void applyLazy(Node* t, ll val) {
    if (!t) return;
    t->val += val;
    t->sum += val * t->cnt;
    t->lazy += val;
}

void push(Node* t) {
    if (t && t->lazy) {
        applyLazy(t->l, t->lazy);
        applyLazy(t->r, t->lazy);
        t->lazy = 0;
    }
}

void update(Node* t) {
    if (t) {
        t->cnt = 1 + getCnt(t->l) + getCnt(t->r);
        t->sum = t->val + getSum(t->l) + getSum(t->r);
    }
}

void split(Node* t, int k, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);
    if (getCnt(t->l) < k) {
        split(t->r, k - getCnt(t->l) - 1, t->r, r);
        l = t;
    } else {
        split(t->l, k, l, t->l);
        r = t;
    }
    update(t);
}

void merge(Node*& t, Node* l, Node* r) {
    push(l); push(r);
    if (!l || !r) t = l ? l : r;
    else if (l->prio > r->prio) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    update(t);
}

void insert(Node*& root, int index, ll val) {
    Node *l, *r;
    split(root, index, l, r);
    Node* newNode = new Node(val);
    merge(root, l, newNode);
    merge(root, root, r);
}

void rangeAdd(Node*& root, int L, int R, ll val) {
    if (L > R) return;
    Node *t1, *t2, *t3;
    split(root, R + 1, t2, t3);
    split(t2, L, t1, t2);
    applyLazy(t2, val);
    merge(root, t1, t2);
    merge(root, root, t3);
}

ll querySum(Node*& root, int L, int R) {
    if (L > R) return 0;
    Node *t1, *t2, *t3;
    split(root, R + 1, t2, t3);
    split(t2, L, t1, t2);
    ll res = getSum(t2);
    merge(root, t1, t2);
    merge(root, root, t3);
    return res;
}

int bit[MAX_N];
void bitAdd(int idx, int val) {
    for (; idx < MAX_N; idx += idx & -idx) bit[idx] += val;
}
int bitQuery(int idx) {
    int s = 0;
    for (; idx > 0; idx -= idx & -idx) s += bit[idx];
    return s;
}

void solveTestCase() {
    int N;
    if (!(cin >> N)) return;

    for(int i = 0; i <= N; ++i) bit[i] = 0;

    vector<int> P(N);
    vector<int> pos(N + 1);
    for(int i = 0; i < N; ++i) {
        cin >> P[i];
        pos[P[i]] = i + 1;
    }

    Node* treapRoot = nullptr;
    ll currentInversions = 0;

    for (int k = 1; k <= N; ++k) {
        int position = pos[k];
        int smallerPositions = bitQuery(position);
        int largerPositions = (k - 1) - smallerPositions;
        
        currentInversions += largerPositions;
        
        bitAdd(position, 1);
        
        int rank = smallerPositions; 
        
        ll valToInsert = position - rank;
        insert(treapRoot, rank, valToInsert);
        
        rangeAdd(treapRoot, rank + 1, k - 1, -1);
        
        int mid = k / 2;
        ll leftSum = querySum(treapRoot, 0, mid - 1);
        ll rightSum = querySum(treapRoot, k - mid, k - 1);
        ll packingCost = rightSum - leftSum;
        
        cout << currentInversions + packingCost << (k == N ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    // cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}