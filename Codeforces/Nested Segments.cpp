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

struct Segment {
    int leftEndpoint;
    int rightEndpoint;
    int originalIndex;
};

bool compareSegments(const Segment& firstSegment, const Segment& secondSegment) {
    if (firstSegment.leftEndpoint != secondSegment.leftEndpoint) {
        return firstSegment.leftEndpoint < secondSegment.leftEndpoint;
    }
    return firstSegment.rightEndpoint > secondSegment.rightEndpoint;
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<Segment> segments(N);
    for(int i = 0; i < N; ++i) {
        cin >> segments[i].leftEndpoint >> segments[i].rightEndpoint;
        segments[i].originalIndex = i + 1;
    }

    sort(all(segments), compareSegments);

    int maxRightEndpoint = -1;
    int bestSegmentIndex = -1;

    for(int i = 0; i < N; ++i) {
        if (segments[i].rightEndpoint <= maxRightEndpoint) {
            cout << segments[i].originalIndex << " " << bestSegmentIndex << endl;
            return;
        }
        maxRightEndpoint = segments[i].rightEndpoint;
        bestSegmentIndex = segments[i].originalIndex;
    }

    cout << "-1 -1" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}