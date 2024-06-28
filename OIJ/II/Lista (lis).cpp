#include <iostream>
using namespace std;

int main() {
    long long n, k, p, q;
    cin >> n >> k >> p >> q;

    long long new_start = (n - k) % n;

    long long adjusted_p = (p - 1 + new_start) % n;
    long long adjusted_q = (q - 1 + new_start) % n;

    if (adjusted_p > adjusted_q) {
        adjusted_q += n;
    }

    long long start_val = (adjusted_p % n) + 1;
    long long end_val = (adjusted_q % n) + 1;
    long long count = adjusted_q - adjusted_p + 1;

    long long sum = 0;
    if (start_val <= end_val) {
        sum = count * (start_val + end_val) / 2;
    } else {
        long long sum1 = (n * (n + 1)) / 2;
        long long sum2 = ((end_val) * (end_val + 1)) / 2;
        long long sum3 = ((start_val - 1) * start_val) / 2;
        sum = sum1 - sum3 + sum2;
    }

    cout << sum << endl;

    return 0;
}
