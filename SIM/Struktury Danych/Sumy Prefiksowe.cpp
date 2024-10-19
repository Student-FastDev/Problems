#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int N, M, Q;
    scanf("%d %d %d", &N, &M, &Q);

    vector<vector<long long>> numberArray(N + 1, vector<long long>(M + 1, 0));
    vector<vector<long long>> prefixSums(N + 1, vector<long long>(M + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%lld", &numberArray[i][j]);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            prefixSums[i][j] = numberArray[i][j] 
                             + prefixSums[i-1][j] 
                             + prefixSums[i][j-1] 
                             - prefixSums[i-1][j-1];
        }
    }

    for (int i = 0; i < Q; i++) {
        ll A, B, C, D;
        scanf("%lld %lld %lld %lld", &A, &B, &C, &D);

        if (A > C) swap(A, C);
        if (B > D) swap(B, D);
        
        ll resultVariable = prefixSums[C][D] 
                         - (A > 1 ? prefixSums[A-1][D] : 0)
                         - (B > 1 ? prefixSums[C][B-1] : 0)
                         + (A > 1 && B > 1 ? prefixSums[A-1][B-1] : 0);
        
        printf("%lld\n", resultVariable);
    }

    return 0;
}
