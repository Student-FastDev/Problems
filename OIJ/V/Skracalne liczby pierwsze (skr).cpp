#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void dfs(int num, int limit, vector<int> &result) {
    if (num > limit) return;
    if (num > 0 && is_prime(num)) {
        result.push_back(num);
    }
    for (int digit = 0; digit <= 9; digit++) { 
        int next_num = num * 10 + digit;
        if (next_num != 0 && is_prime(next_num)) {
            dfs(next_num, limit, result);
        }
    }
}

int main() {
    int a, b;
    cin >> a >> b;
    
    vector<int> truncatable_primes;
    
    vector<int> initial_primes = {2, 3, 5, 7};
    for (int prime : initial_primes) {
        dfs(prime, b, truncatable_primes);
    }
    
    int count = 0;
    for (int prime : truncatable_primes) {
        if (prime >= a && prime <= b) {
            count++;
        }
    }
    
    cout << count << endl;
    
    return 0;
}
