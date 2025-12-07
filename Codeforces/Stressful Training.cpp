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
typedef pair<ll, int> pli;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 200005;

int N;
ll K;
vector<ll> A;
vector<ll> B;

bool check(ll x) {
    priority_queue<pli, vector<pli>, greater<pli>> priorityQueue;
    vector<int> countArray(N, 0);

    for (int i = 0; i < N; ++i) {
        if (B[i] == 0) continue;
        ll timeFail = A[i] / B[i] + 1;
        if (timeFail < K) {
            priorityQueue.push({timeFail, i});
        }
    }

    for (int t = 0; t < K - 1; ++t) {
        if (priorityQueue.empty()) return true;

        pli topElement = priorityQueue.top();
        if (topElement.first <= t) return false;

        priorityQueue.pop();
        int index = topElement.second;
        countArray[index]++;

        __int128 currentCapacity = (__int128)A[index] + (__int128)countArray[index] * x;
        __int128 neededCapacity = (__int128)B[index] * (K - 1);

        if (currentCapacity < neededCapacity) {
            ll nextFailTime = (ll)(currentCapacity / B[index]) + 1;
            if (nextFailTime < K) {
                priorityQueue.push({nextFailTime, index});
            }
        }
    }

    return priorityQueue.empty();
}

void solveTestCase() {
    cin >> N >> K;
    A.resize(N);
    B.resize(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];

    ll lowValue = 0, highValue = 2000000000005LL;
    ll answer = -1;

    if (!check(highValue)) {
        cout << -1 << endl;
        return;
    }

    while (lowValue <= highValue) {
        ll midValue = lowValue + (highValue - lowValue) / 2;
        if (check(midValue)) {
            answer = midValue;
            highValue = midValue - 1;
        } else {
            lowValue = midValue + 1;
        }
    }
    cout << answer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}