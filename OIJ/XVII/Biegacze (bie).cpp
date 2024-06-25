#include <iostream>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    long long A, B, C;
    cin >> A >> B >> C;

    long long LCM = lcm(A, B);

    if (LCM > C) {
        cout << 0 << endl;
    } else {
        cout << C / LCM << endl;
    }

    return 0;
}
