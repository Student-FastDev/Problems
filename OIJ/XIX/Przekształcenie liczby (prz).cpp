#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    long long N, M;
    cin >> N >> M;
    
    long long gcdValue = __gcd(N, M);
    long long sumOfFactors = 0;

    if (N == M) {
        cout << 0;
    }
    else {
        long long reducedN = N / gcdValue;
        long long reducedM = M / gcdValue;
        
        for (long long i = 2; i * i <= reducedN; i++) {
            while (reducedN % i == 0) {
                sumOfFactors += i;
                reducedN /= i;
            }
        }
        
        if (reducedN > 1) {
            sumOfFactors += reducedN;
        }

        for (long long i = 2; i * i <= reducedM; i++) {
            while (reducedM % i == 0) {
                sumOfFactors += i;
                reducedM /= i;
            }
        }
        
        if (reducedM > 1) {
            sumOfFactors += reducedM;
        }

        cout << sumOfFactors;
    }
    return 0;
}
