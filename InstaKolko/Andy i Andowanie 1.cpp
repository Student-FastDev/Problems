#include <iostream>
using namespace std;

int main() {
    unsigned long long N;
    cin >> N;

    int count = 0;
    while (N) {
        count += N & 1;
        N >>= 1;
    }

    cout << count << endl;
    return 0;
}
