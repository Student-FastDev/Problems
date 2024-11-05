#include <iostream>
using namespace std;

const int MOD = 1000000007;

long long powerCalc(long long a, long long b) {
    long long result = 1;
    a = a % MOD;
    
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % MOD;
        
        a = (a * a) % MOD;
        b /= 2;
    }
    
    return result;
}

int main() {
    long long a, b;
    cin >> a >> b;

    long long result = powerCalc(a, b);
    cout << result << endl;

    return 0;
}
