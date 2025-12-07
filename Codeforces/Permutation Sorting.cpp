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

struct Segment {
    int s, e, id;
};

struct BIT {
    int n;
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solveTestCase() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> isBad(2 * n + 1, 0);
    vector<Segment> queries;
    vector<Segment> pool;

    for (int i = 1; i <= n; ++i) {
        if (a[i] == i) continue;
        
        int start = i;
        int end = a[i];
        if (end < start) end += n;

        isBad[start] = 1;
        isBad[start + n] = 1; 

        queries.push_back({start, end, a[i]});
        
        pool.push_back({start, end, -1});
        if (end + n <= 2 * n) {
             pool.push_back({start + n, end + n, -1});
        }
    }

    vector<int> pref(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i) {
        pref[i] = pref[i - 1] + isBad[i];
    }

    sort(all(queries), [](const Segment& a, const Segment& b) {
        return a.e < b.e;
    });
    sort(all(pool), [](const Segment& a, const Segment& b) {
        return a.e < b.e;
    });

    vector<int> ans(n + 1, 0);
    BIT bit(2 * n + 2);
    
    int poolIdx = 0;
    int m = size(pool);
    
    for (const auto& q : queries) {
        while (poolIdx < m && pool[poolIdx].e <= q.e) {
            bit.add(pool[poolIdx].s, 1);
            poolIdx++;
        }
        
        int term1 = pref[q.e] - pref[q.s];
        int term2 = bit.query(q.s + 1, 2 * n);
        
        ans[q.id] = term1 - term2;
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << endl;
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