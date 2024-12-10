#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    unsigned long long xorResult = 0;

    for (int i = 0; i < N; i++) {
        unsigned long long a;
        cin >> a;
        xorResult ^= a;
    }

    if (xorResult == 0) {
        cout << "zaczyna maszyna!" << endl;
    } else {
        cout << "ja zaczynam!" << endl;
    }

    return 0;
}
