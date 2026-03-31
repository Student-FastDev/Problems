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

struct Interval {
    long long l, r;
    Interval(long long a, long long b) : l(a), r(b) {}
};

bool compareIntervals(const Interval &a, const Interval &b) {
    return a.l < b.l;
}

void solveTestCase() {
    long long N, M, S;
    cin >> N >> M >> S;
    
    vector<Interval> intervalsArray;
    for (int i = 0; i < M; ++i) {
        long long L, R;
        cin >> L >> R;
        intervalsArray.emplace_back(L, R);
    }
    
    sort(intervalsArray.begin(), intervalsArray.end(), compareIntervals);
    
    vector<Interval> freeIntervals;
    
    if (intervalsArray[0].l > 1) {
        freeIntervals.emplace_back(1, intervalsArray[0].l - 1);
    }
    
    for (int i = 1; i < size(intervalsArray); ++i) {
        long long previousInterval = intervalsArray[i-1].r;
        long long currentInterval = intervalsArray[i].l;
        if (previousInterval + 1 <= currentInterval - 1) {
            freeIntervals.emplace_back(previousInterval + 1, currentInterval - 1);
        }
    }
    
    long long lastR = intervalsArray.back().r;
    if (lastR < N) {
        freeIntervals.emplace_back(lastR + 1, N);
    }
    
    long long bestP = -1;
    long long minDistance = LLONG_MAX;
    
    for (const auto &freeInterval : freeIntervals) {
        long long a = freeInterval.l;
        long long b = freeInterval.r;
        long long candidate;
        if (b < S) {
            candidate = b;
        } else if (a > S) {
            candidate = a;
        } else {
            continue;
        }
        long long distanceValue = abs(S - candidate);
        if (distanceValue < minDistance || (distanceValue == minDistance && candidate < bestP)) {
            minDistance = distanceValue;
            bestP = candidate;
        }
    }
    
    cout << bestP << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
