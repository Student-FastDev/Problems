#include <iostream>
#include <vector>
#include <set>

using namespace std;
typedef long long ll;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    long long N;
    cin >> N;

    long long moves = 0;
    long long currentValue = 0;
    multiset<long long> bossValue;
    for (long long i = 0; i < N; ++i) {
        long long thisValue;
        cin >> thisValue;
        
        if (thisValue >= 0) {
            currentValue += thisValue;
        } else {
            long long placeholderValue = abs(thisValue);
            currentValue -= placeholderValue;
            bossValue.insert(2 * thisValue);
            while (currentValue < 0) {
                moves++;
                currentValue += abs(*bossValue.begin());
                bossValue.erase(bossValue.begin());
            }
        }
    }

    cout << moves;

    return 0;
}
