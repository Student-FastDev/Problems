// Catling
#include <bits/stdc++.h>
using namespace std;

#define size(x) x.size()
#define all(x) x.begin(),x.end()
#define endl '\n'

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int MAX_N = 1e4 + 5;
const ll MOD = 1e9 + 9;
const ll INF = LLONG_MAX / 4; 

int T[MAX_N], P[2 * MAX_N];
int N, M, currentValue;
int d, k, c, L, R, i;

void solveTestCase() {
    cin >> N >> M;
    for(; i < N; ++i) cin >> T[i];
    for(i = 0; i < M; ++i) cin >> P[i], P[i + M] = P[i];
    for(d = M - N; d < M; ++d) {
        L = d < 0 ? -d : 0;
        R = N - 1 < 2 * M - 2 - d ? N - 1 : 2 * M - 2 - d;
        for(c = 0, k = L; k < L + M; ++k) c += T[k] == P[k + d];
        if(c > currentValue) currentValue = c;
        for(; k <= R; ++k) if(currentValue < (c += (T[k] == P[k + d]) - (T[k - M] == P[k - M + d]))) currentValue = c;
    }
    cout << M - currentValue;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
}
