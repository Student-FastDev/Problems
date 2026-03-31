// Catling
#include <bits/stdc++.h>
using namespace std;

#define size(X) X.size()
#define all(X) X.begin(),X.end()
#define endl '\n'

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int MAX_N = 1505;
const ll MOD = 1e9 + 9;
const ll INF = LLONG_MAX / 4;

ll getMinutes(ll D, ll H, ll M) {
    ll totalMinutes = D * 24 * 60 + H * 60 + M;
    if (D > 29 || (D == 29 && H >= 3)) totalMinutes -= 60;
    
    return totalMinutes;
}

void solveTestCase() {
    ll X, D, H, M;
    cin >> X >> D >> H >> M;
    ll endDay = 0;
        
    if (X == 1) endDay = 25;
    else if (X == 2) endDay = 26;
    else if (X == 3) endDay = 27;
    else if (X == 4) endDay = 28;
    else if (X == 5) endDay = 30;
        
    ll startTime = getMinutes(D, H, M);
    ll endTime = getMinutes(endDay, 0, 0);
    cout << endTime - startTime << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
}