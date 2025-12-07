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
const ll MOD = 1e9+7; 

struct Node {
    int cnt;
    ll sum;
};

vector<Node> tree;
int treeSize;

void update(int node, int start, int end, int idx, int val, int cost) {
    if (start == end) {
        tree[node].cnt += val;
        tree[node].sum += (ll)val * cost;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val, cost);
    else update(2 * node + 1, mid + 1, end, idx, val, cost);
    tree[node].cnt = tree[2 * node].cnt + tree[2 * node + 1].cnt;
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
}

ll query(int node, int start, int end, int k) {
    if (k <= 0) return 0;
    if (tree[node].cnt <= k) return tree[node].sum;
    if (start == end) {
        return (ll)k * (tree[node].sum / tree[node].cnt);
    }
    int mid = (start + end) / 2;
    if (tree[2 * node].cnt >= k) {
        return query(2 * node, start, mid, k);
    } else {
        return tree[2 * node].sum + query(2 * node + 1, mid + 1, end, k - tree[2 * node].cnt);
    }
}

void solveTestCase() {
    int n, m, k;
    if (!(cin >> n >> m >> k)) return;

    vector<int> costs(n);
    for(int i=0; i<n; ++i) cin >> costs[i];

    int a;
    cin >> a;
    vector<int> mashaLikes(n, 0);
    for(int i=0; i<a; ++i) {
        int x; cin >> x; --x;
        mashaLikes[x] = 1;
    }

    int b;
    cin >> b;
    vector<int> arkadyLikes(n, 0);
    for(int i=0; i<b; ++i) {
        int x; cin >> x; --x;
        arkadyLikes[x] = 1;
    }

    vector<int> v0, v1, v2, v3;
    for(int i=0; i<n; ++i) {
        if (mashaLikes[i] && arkadyLikes[i]) v3.push_back(costs[i]);
        else if (mashaLikes[i]) v1.push_back(costs[i]);
        else if (arkadyLikes[i]) v2.push_back(costs[i]);
        else v0.push_back(costs[i]);
    }

    sort(all(v0));
    sort(all(v1));
    sort(all(v2));
    sort(all(v3));

    vector<int> allCosts = costs;
    sort(all(allCosts));
    allCosts.erase(unique(all(allCosts)), allCosts.end());
    
    auto getRank = [&](int val) {
        return lower_bound(all(allCosts), val) - allCosts.begin();
    };

    int sz = size(allCosts);
    treeSize = sz;
    tree.assign(4 * sz, {0, 0});

    for(int x : v0) {
        update(1, 0, sz - 1, getRank(x), 1, x);
    }

    ll currentMandatorySum = 0;
    int missingCnt = 0;

    int req1 = k;
    if (req1 <= (int)size(v1)) {
        for(int i=0; i<req1; ++i) currentMandatorySum += v1[i];
        for(int i=req1; i<(int)size(v1); ++i) update(1, 0, sz - 1, getRank(v1[i]), 1, v1[i]);
    } else {
        for(int x : v1) currentMandatorySum += x;
        missingCnt += (req1 - (int)size(v1));
    }

    int req2 = k;
    if (req2 <= (int)size(v2)) {
        for(int i=0; i<req2; ++i) currentMandatorySum += v2[i];
        for(int i=req2; i<(int)size(v2); ++i) update(1, 0, sz - 1, getRank(v2[i]), 1, v2[i]);
    } else {
        for(int x : v2) currentMandatorySum += x;
        missingCnt += (req2 - (int)size(v2));
    }

    ll minTotalCost = -1;

    for(int n3 = 0; n3 <= (int)size(v3); ++n3) {
        int taken1 = min(max(0, k - n3), (int)size(v1));
        int taken2 = min(max(0, k - n3), (int)size(v2));
        int currentFixedCount = n3 + taken1 + taken2;
        int rem = m - currentFixedCount;

        if (missingCnt == 0 && rem >= 0 && rem <= tree[1].cnt) {
            ll extraCost = query(1, 0, sz - 1, rem);
            ll total = currentMandatorySum + extraCost;
            if (minTotalCost == -1 || total < minTotalCost) {
                minTotalCost = total;
            }
        }

        if (n3 < (int)size(v3)) {
            currentMandatorySum += v3[n3];
            
            if (k - n3 > 0) {
                int idxReleased = k - n3 - 1;
                if (idxReleased < (int)size(v1)) {
                    currentMandatorySum -= v1[idxReleased];
                    update(1, 0, sz - 1, getRank(v1[idxReleased]), 1, v1[idxReleased]);
                } else {
                    missingCnt--;
                }
            }

            if (k - n3 > 0) {
                int idxReleased = k - n3 - 1;
                if (idxReleased < (int)size(v2)) {
                    currentMandatorySum -= v2[idxReleased];
                    update(1, 0, sz - 1, getRank(v2[idxReleased]), 1, v2[idxReleased]);
                } else {
                    missingCnt--;
                }
            }
        }
    }

    cout << minTotalCost << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
    return 0;
}