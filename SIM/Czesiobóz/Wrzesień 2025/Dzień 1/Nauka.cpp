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

void solveTestCase() {
    int N;
    long long K;
    cin >> N >> K;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    sort(A.begin(), A.end());

    using P = pair<ll,int>;
    priority_queue<P, vector<P>, greater<P>> sortedQueue;
    if (N > 0) sortedQueue.push({A[0], 0});
    ll finalAnswer = 0;
    for (long long j = 0; j < K; ++j) {
        if (sortedQueue.empty()) break;
        auto currentElement = sortedQueue.top(); sortedQueue.pop();
        finalAnswer = currentElement.first;
        int i = currentElement.second;
        if (i + 1 < N) {
            sortedQueue.push({currentElement.first + A[i+1], i + 1});
            sortedQueue.push({currentElement.first - A[i] + A[i+1], i + 1});
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
