#include <bits/stdc++.h>

using namespace std;

long long fastPower(long long A, long long B, long long MOD) {
    if(B == 0) {
        return 1 % MOD;
    }

    if(B % 2 == 1) {
        return (fastPower(A, B-1, MOD) * A) % MOD; 
    }

    long long calculateVariable = fastPower(A, B/2, MOD);
    return (calculateVariable * calculateVariable) % MOD;
}


int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    long long A, B, M;
    cin >> A >> B >> M;

    cout << fastPower(A, B, M);
    return 0;
}
