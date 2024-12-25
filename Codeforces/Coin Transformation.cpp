#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
const int MAX_N = 1e9+1;
const int MOD = 1e9+7;
 
ll maxCoins(ll N) {
    ll coins = 1;
    while (N > 3) {
        N /= 4;
        coins *= 2;
    }
    return coins;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int T;
    cin >> T;
    while (T--) {
        ll N;
        cin >> N;
        cout << maxCoins(N) << "\n";
    }
    return 0;
}
