// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define size(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define endl '\n';

const ll MOD = 1e9 + 7;
const int MAX_N = 567;

ll N;
ll A[MAX_N], B[MAX_N];
ll DP[MAX_N];
ll rightSum[MAX_N];
ll factorialsArray[MAX_N], inverseFactorialsArray[MAX_N];
ll prefixArray[MAX_N], suffixArray[MAX_N];
ll lagrangeCoefficients[MAX_N];
ll S[MAX_N];

ll fastPower(ll base, ll power) {
    if(power == 0) return 1;
    if(power == 1) return base;

    if(power % 2 == 0) {
        ll powerValue = fastPower(base, power / 2) % MOD;
        return (powerValue * powerValue) % MOD;
    }
    else {
        return ((fastPower(base, power - 1) % MOD) * base) % MOD;
    }
}

ll getInverse(ll N) {
    return fastPower(N, MOD - 2);
}

void precomputeFactorials() {
    factorialsArray[0] = 1;
    inverseFactorialsArray[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        factorialsArray[i] = (factorialsArray[i - 1] * i) % MOD;
        inverseFactorialsArray[i] = getInverse(factorialsArray[i]);
    }
}

void precomputeLagrange(ll currentLength, int K) {
    prefixArray[0] = 1;
    for(int i = 0; i <= K; ++i) prefixArray[i+1] = (prefixArray[i] * ((currentLength - i) % MOD)) % MOD;
    
    suffixArray[K+1] = 1;
    for(int i = K; i >= 0; --i) suffixArray[i] = (suffixArray[i+1] * ((currentLength - i) % MOD)) % MOD;
    
    for(int i = 0; i <= K; ++i) {
        ll numeratorValue = (prefixArray[i] * suffixArray[i+1]) % MOD;
        ll denumeratorValue = (inverseFactorialsArray[i] * inverseFactorialsArray[K-i]) % MOD;
        if ((K - i) % 2 == 1) denumeratorValue = (MOD - denumeratorValue);
        
        lagrangeCoefficients[i] = (numeratorValue * denumeratorValue) % MOD;
    }
}

void solveTestCase() {
    cin >> N;
    for(int i = 1; i <= N; ++i) cin >> A[i] >> B[i];

    vector<ll> pointsArray;
    pointsArray.push_back(0); 
    for(int i=1; i<=N; ++i) {
        pointsArray.push_back(A[i]);
        pointsArray.push_back(B[i] + 1);
    }
    sort(all(pointsArray));
    pointsArray.erase(unique(all(pointsArray)), pointsArray.end());

    for(int i = 0; i <= N; ++i) rightSum[i] = 0;

    precomputeFactorials();

    int K = N + 1;

    for(int j = size(pointsArray) - 2; j >= 0; --j) {
        ll L = pointsArray[j];
        ll R = pointsArray[j+1] - 1;
        ll currentLength = R - L + 1;
        if (currentLength <= 0) continue;

        if(currentLength > K) {
            precomputeLagrange(currentLength, K);
        }

        for(int m = 0; m <= K; ++m) DP[m] = 1;

        for(int i = N; i >= 1; --i) {
            S[0] = 0;
            for(int m = 0; m <= K; ++m) {
                ll currentValue = S[m] + DP[m];
                if (currentValue >= MOD) currentValue -= MOD;
                S[m + 1] = currentValue;
            }
            
            ll T = 0;
            if (currentLength <= K) {
                T = S[currentLength];
            } else {
                unsigned __int128 sumT = 0;
                for(int m = 0; m <= K; ++m) {
                    sumT += (unsigned __int128)S[m] * lagrangeCoefficients[m];
                }
                T = sumT % MOD;
            }
            
            bool isInside = (L >= A[i] && R <= B[i]);
            bool isAbove = (A[i] > R);

            if (isInside) {
                rightSum[i] += T;
                if (rightSum[i] >= MOD) rightSum[i] -= MOD;
                
                ll currentRightSum = rightSum[i];
                for(int m = 0; m <= K; ++m) {
                    ll currentValue = DP[m] + currentRightSum;
                    if (currentValue >= MOD) currentValue -= MOD;
                    currentValue -= S[m + 1];
                    if (currentValue < 0) currentValue += MOD;
                    DP[m] = currentValue;
                }
            }
            else if (isAbove) {
                ll currentRightSum = rightSum[i];
                for(int m = 0; m <= K; ++m) {
                    ll currentValue = DP[m] + currentRightSum;
                    if (currentValue >= MOD) currentValue -= MOD;
                    DP[m] = currentValue;
                }
            }
        }
    }
    
    cout << (DP[0] - 1 + MOD) % MOD << endl;
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
