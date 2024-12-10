#include <iostream>
using namespace std;

int main() {
    unsigned long long N;
    cin >> N;

    int zeroCount = 0;

    while (N) {
        unsigned long long bit = N & 1;
        if (bit + bit == 0) {
            zeroCount = zeroCount + 1;
        }
        N >>= 1;
    }

    cout << zeroCount << endl;
    return 0;
}
