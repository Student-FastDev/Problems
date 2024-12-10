#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    unsigned long long xorSum = 0;
    bool allOnes = true;

    for (int i = 0; i < N; ++i) {
        unsigned long long a;
        cin >> a;
        xorSum ^= a;
        if (a != 1) {
            allOnes = false;
        }
    }

    if (allOnes) {
        if (N % 2 == 0) {
            cout << "wygralem!" << endl;
        } else {
            cout << "jestesmy zgubieni!" << endl;
        }
    } else if (xorSum == 0) {
        cout << "jestesmy zgubieni!" << endl;
    } else {
        cout << "wygralem!" << endl;
    }

    return 0;
}
