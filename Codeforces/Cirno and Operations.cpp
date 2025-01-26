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

ll maxSumAfterOperations(int n, vector<ll>& a) {
    vector<ll> currentSeq = a;
    ll maxSum = accumulate(currentSeq.begin(), currentSeq.end(), 0LL);
    while (size(currentSeq) > 1) {
        ll sum1 = currentSeq.back() - currentSeq.front();
        ll sum2 = currentSeq.front() - currentSeq.back();
        vector<ll> newSeq;
        ll chosenSum;
        if (sum1 >= sum2) {
            for (size_t i = 0; i < size(currentSeq) - 1; ++i) {
                newSeq.push_back(currentSeq[i + 1] - currentSeq[i]);
            }
            chosenSum = sum1;
        } else {
            reverse(currentSeq.begin(), currentSeq.end());
            for (size_t i = 0; i < size(currentSeq) - 1; ++i) {
                newSeq.push_back(currentSeq[i + 1] - currentSeq[i]);
            }
            chosenSum = sum2;
        }
        if (chosenSum > maxSum) {
            maxSum = chosenSum;
        }
        currentSeq = newSeq;
    }
    return maxSum;
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    cout << maxSumAfterOperations(N, A) << endl;
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
