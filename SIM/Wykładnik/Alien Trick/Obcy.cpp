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
    int l, r;
};

bool compareIntervals(const Interval& a, const Interval& b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r > b.r;
}

struct Line {
    ll m, c;
    int ID;
    ll evaluate(ll x) const { return m * x + c; }
};

struct State {
    ll value;
    int count;
};

int N;
ll K;
vector<Interval> intervals;

bool isRedudant(const Line& firstLine, const Line& secondLine, const Line& thirdLine) {
    __int128 firstNumerator = thirdLine.c - firstLine.c;
    __int128 firstDenumerator = firstLine.m - thirdLine.m;
    __int128 secondNumerator = secondLine.c - firstLine.c;
    __int128 secondDenumerator = firstLine.m - secondLine.m;
    return firstNumerator * secondDenumerator <= secondNumerator * firstDenumerator;
}

State solveDP(ll lambda) {
    deque<Line> dequeArray;
    
    auto addLine = [&](ll m, ll c, int count) {
        Line newLine = {m, c, count};
        while (size(dequeArray) >= 2) {
            if (isRedudant(dequeArray[size(dequeArray)-2], dequeArray.back(), newLine)) {
                dequeArray.pop_back();
            } else {
                break;
            }
        }
        dequeArray.push_back(newLine);
    };

    addLine(-2LL * intervals[0].l, (ll)intervals[0].l * intervals[0].l, 0);

    ll currentValue = 0;
    int currentCount = 0;

    for (int i = 1; i <= N; ++i) {
        ll x = intervals[i-1].r + 1;
        while (size(dequeArray) >= 2 && dequeArray[0].evaluate(x) > dequeArray[1].evaluate(x)) dequeArray.pop_front();

        ll bestValue = dequeArray[0].evaluate(x) + x * x + lambda;
        int bestCount = dequeArray[0].ID + 1;
        
        currentValue = bestValue;
        currentCount = bestCount;

        if (i < N) {
            ll nextLeft = intervals[i].l;
            ll currentRight = intervals[i-1].r;
            ll overlap = max(0LL, currentRight - nextLeft + 1);
            
            ll m = -2LL * nextLeft;
            ll c = currentValue + nextLeft * nextLeft - overlap * overlap;
            
            addLine(m, c, currentCount);
        }
    }
    
    return {currentValue, currentCount};
}

void solveTestCase() {
    int gridM;
    cin >> N >> gridM >> K;

    vector<Interval> rawIntervals;
    rawIntervals.reserve(N);
    for(int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        rawIntervals.push_back({min(a, b), max(a, b)});
    }

    sort(all(rawIntervals), compareIntervals);

    for (auto interval : rawIntervals) {
        if (intervals.empty() || interval.r > intervals.back().r) {
            intervals.push_back(interval);
        }
    }

    N = size(intervals); K = min(K, (ll)N); 

    ll leftRange = 0, rightRange = (ll)gridM * gridM + 7;
    ll finalAnswer = -1;

    while (leftRange <= rightRange) {
        ll middleValue = leftRange + (rightRange - leftRange) / 2;
        State thisResult = solveDP(middleValue);

        if (thisResult.count <= K) {
            finalAnswer = thisResult.value - middleValue * K;
            rightRange = middleValue - 1;
        } else {
            leftRange = middleValue + 1;
        }
    }

    cout << finalAnswer << endl;
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
