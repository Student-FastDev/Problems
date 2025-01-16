#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<LL> generatePowers() {
    set<LL> powerSet;
    const LL LIMIT = 1000000000000000000;
    
    for (__int128_t i = 2; i <= 1000007; ++i) {
        long double sqrtVal = sqrtl(static_cast<long double>(i));
        if (floor(sqrtVal) * sqrtVal == i)
            continue;
        
        __int128_t currentPower = i;
        for (int exponent = 3; exponent <= 60; exponent += 2) {
            if (currentPower * i * i > LIMIT)
                break;
            currentPower *= i * i;
            powerSet.insert(static_cast<LL>(currentPower));
        }
    }
    
    vector<LL> powerVector(powerSet.begin(), powerSet.end());
    return powerVector;
}

LL findNthNumber(LL n, const vector<LL>& powers) {
    LL low = 1;
    LL high = 5000000000000000002;
    
    while (low < high) {
        LL mid = low + (high - low) / 2;
        LL count = 1 + mid - static_cast<LL>(sqrtl(static_cast<long double>(mid))) 
                     - static_cast<LL>(lower_bound(powers.begin(), powers.end(), mid + 1) - powers.begin());
        
        if (count < n) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    
    return low;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<LL> powers = generatePowers();
    
    LL queryCount;
    cin >> queryCount;
    
    while(queryCount--){
        LL n;
        cin >> n;
        LL result = findNthNumber(n, powers);
        cout << result << "\n";
    }
    
    return 0;
}
