#include <iostream>
#include <cmath>

using namespace std;

long long countDigits(long long n, long long base) {
    long long digits = 0;
    while (n > 0) {
        n /= base;
        digits++;
    }
    return digits;
}


bool check(long long n, long long base, long long m) {
    return countDigits(n, base) <= m;
}

bool checkTo(long long n, long long base, long long m) {
    return countDigits(n, base) == m;
}

long long findBase(long long n, long long m) {
    long long low = 2;
    long long high = 1000000000000000000;
    long long result = -1;

    while (low <= high) {
        long long mid = (low + high) / 2;
        if (check(n, mid, m)) {
            if (checkTo(n, mid, m)) {
                result = mid;
                high = mid - 1;
            } else {
                high = mid - 1;
            }
        } else {
            low = mid + 1;
        }
    }
    
    return result;
}

int main() {
    long long N;
    cin >> N;

    for (long long i = 0; i < N; i++) {
        long long n, m;
        cin >> n >> m;
    
        long long base = findBase(n, m);
        if (base != -1) {
            cout << base << endl;
        } else {
            cout << "NIE" << endl;
        }
    }

    return 0;
}
