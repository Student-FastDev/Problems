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

long long sumDivisors(long long N) {
    if (N <= 0) return 0;
    long long answerValue = 0;

    for (long long i = 1; i <= N; ) {
        long long divisorNumbers = N / i;
        long long maxI = N / divisorNumbers;
        if (maxI > N) maxI = N;
        answerValue += divisorNumbers * (maxI - i + 1);
        i = maxI + 1;
        LOG(i, maxI, divisorNumbers, answerValue);
    }
    return answerValue;
}

long long iSqrt(long long X) {
    if (X < 0) return -1;

    long long R = (long long) floor(sqrt((long double) X) );
    while ((R + 1) * (long long)(R + 1) <= X) R++;
    while (R * R > X) R--;
    return R;
}

long long F(long long N) {
    if (N <= 0) return 0;
    return sumDivisors(N);
}

void solveTestCase() {
    long long L, R;
    cin >> L >> R;

    if (L <= -1 && -1 <= R) {
        cout << -1 << endl;
        return;
    }

    long long M = L + 1;
    long long N = R + 1;

    long long answerValue = 0;

    if (N < 0) {
        long long A = llabs(M), B = llabs(N) - 1; 
        if (B < 0) B = 0;
        answerValue = F(A) - F(B);
    } else {
        long long segmentSize = (M - 1 >= 1 ? (M - 1) : 0); 
        answerValue = ( F(N) + iSqrt(N) ) - ( F(segmentSize) + iSqrt(segmentSize) );
        LOG(F(N), iSqrt(N), F(segmentSize), iSqrt(segmentSize));
    }

    cout << answerValue << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int F;
    cin >> F;

    while(F--) {
        solveTestCase();
    }
    return 0;
}
