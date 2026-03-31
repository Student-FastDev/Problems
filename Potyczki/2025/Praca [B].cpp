#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int N, K, T;
    cin >> N >> K >> T;
    string S;
    cin >> S;
 
    vector<int> prefixSums(N+1, 0), prefixSumsSecond(N+1, 0), prefixSumsThird(N+1, 0);
    for(int i = 1; i <= N; i++){
        prefixSums[i] = prefixSums[i-1];
        prefixSumsSecond[i] = prefixSumsSecond[i-1];
        prefixSumsThird[i] = prefixSumsThird[i-1];
        char C = S[i-1];
        if(C == '1') prefixSums[i]++;
        else if(C == '2') prefixSumsSecond[i]++;
        else if(C == '3') prefixSumsThird[i]++;
    }
 
    int totalValue = prefixSums[N], totalValueSecond = prefixSumsSecond[N], totalValueThird = prefixSumsThird[N];
    long long best = -1;
    if(totalValue <= K){
        long long candidateValue = totalValue + totalValueThird + min(totalValueSecond, K - totalValue);
        best = candidateValue;
    }
 
    for (int L = 1; L <= N - T + 1; L++){
        for (int R = L + T; R <= N - T + 1; R++){
            int homeHFirst = prefixSums[L-1];
            int homeHSecond = prefixSumsSecond[L-1];
            int homeHThird = prefixSumsThird[L-1];
            homeHFirst += (prefixSums[N] - prefixSums[R+T-1]);
            homeHSecond += (prefixSumsSecond[N] - prefixSumsSecond[R+T-1]);
            homeHThird += (prefixSumsThird[N] - prefixSumsThird[R+T-1]);
 
            int transitOut = (prefixSums[L+T-1] - prefixSums[L-1]) + (prefixSumsSecond[L+T-1] - prefixSumsSecond[L-1]);
            int transitIn  = (prefixSums[R+T-1] - prefixSums[R-1]) + (prefixSumsSecond[R+T-1] - prefixSumsSecond[R-1]);
            int transitMiss = transitOut + transitIn;
 
            if(transitMiss + homeHFirst > K) continue;
 
            int available = K - transitMiss - homeHFirst;
            int solvedType2 = (homeHSecond <= available ? homeHSecond : available);
 
            long long candidateValue = (long long)homeHFirst + homeHThird + solvedType2;
            best = max(best, candidateValue);
        }
    }
 
    cout << best << "\n";
    return 0;
}
