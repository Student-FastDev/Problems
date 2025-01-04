#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll T;
    cin >> T;
    
    while (T--) {
        ll L, R;
        cin >> L >> R;
        ll sumValue = 0;
        ll maxPower = 30;
        while (maxPower >= 0) {
            if ((L & (1ll << maxPower)) == (R & (1ll << maxPower))) {
                if (L & (1ll << maxPower)) sumValue += (1ll << maxPower);
            } else break;
            --maxPower;
        }
        if (R > sumValue + (1ll << maxPower)) {
            cout << sumValue + (1ll << maxPower) - 1 << ' ' << sumValue + (1ll << maxPower) << ' ' << sumValue + (1ll << maxPower) + 1 << '\n';
        } else {
            cout << sumValue + (1ll << maxPower) - 2 << ' ' << sumValue + (1ll << maxPower) - 1 << ' ' << sumValue + (1ll << maxPower) << '\n';
        }
    }
    return 0;
}
