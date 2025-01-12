#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long N, M, K;
    cin >> N >> M >> K;

    long long Y = 2LL * M;

    for (long long i = 0; i < K; i++) {
        long long X = min(N, Y);
        if (X == 0LL) {
            break;
        }
        N -= X;
        Y += X;
    }

    long long integerPart = Y / 2;
    long long r = Y % 2;

    if (r == 0) {
        cout << integerPart << "\n";
    } else {
        cout << integerPart << ".5\n";
    }

    return 0;
}
