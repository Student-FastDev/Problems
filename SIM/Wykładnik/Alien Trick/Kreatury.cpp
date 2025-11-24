// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&phasesValue,auto p)->decltype(p.first,phasesValue){return phasesValue<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&phasesValue,auto x)->decltype(x.end(),phasesValue){phasesValue<<'{';int i=2;for(auto e:x)phasesValue<<(", ")+i<<e,i=0;return phasesValue<<'}';}
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
const ll MAX_N = 2002;
const ll MOD = 1e9+7; // 998244353

const double minimalEpsilon = 1e-8;
int N, A, B, optimalArray[MAX_N];
double DP[MAX_N], arrayA[MAX_N], arrayB[MAX_N], mixedArray[MAX_N];

pii solveDP(double &D_penalty, double &C_penalty) {
    for (int i = 1; i <= N; i++) {
        double &D = DP[i]; 
        int &phasesValue = optimalArray[i];

        D = DP[i - 1];
        phasesValue = 0;

        double currentCandidate;
        currentCandidate = DP[i - 1] + arrayA[i] - D_penalty;
        if (D < currentCandidate) {
            D = currentCandidate;
            phasesValue = 1;
        }

        currentCandidate = DP[i - 1] + arrayB[i] - C_penalty;
        if (D < currentCandidate) {
            D = currentCandidate;
            phasesValue = 2;
        }

        currentCandidate = DP[i - 1] + mixedArray[i] - C_penalty - D_penalty;
        if (D < currentCandidate) {
            D = currentCandidate;
            phasesValue = 3;
        }
    }

    pii returnValue = pii(0, 0);
    for (int i = 1; i <= N; i++) {
        if (optimalArray[i] > 1) returnValue.second++;
        if (optimalArray[i] & 1) returnValue.first++;
    }

    return returnValue;
}

void solveTestCase() {
    cin >> N >> A >> B;

    for(int i = 1; i <= N; i++) cin >> arrayA[i];
    for(int i = 1; i <= N; i++) cin >> arrayB[i];
    for(int i = 1; i <= N; i++) mixedArray[i] = arrayA[i] + arrayB[i] - arrayA[i] * arrayB[i];

    double firstLeft = 0, firstRight = 1, firstMiddle, secondLeft, secondRight, secondMiddle;

    for(int i = 0; i < 50; i++){
        firstMiddle = (firstLeft + firstRight) / 2;
        secondLeft = 0, secondRight = 1, secondMiddle;

        for(int j = 0; j < 50; j++){
            secondMiddle = (secondLeft + secondRight) / 2;
            if(solveDP(firstMiddle, secondMiddle).second > B) secondLeft = secondMiddle;
            else secondRight = secondMiddle;
        }

        if(solveDP(firstMiddle, secondRight).first > A) firstLeft = firstMiddle;
        else firstRight = firstMiddle;
    }

    solveDP(firstRight, secondRight);

    cout << fixed << setprecision(10) << DP[N] + secondRight * B + firstRight * A << endl;
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