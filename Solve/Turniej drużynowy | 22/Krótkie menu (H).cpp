#include <bits/stdc++.h>
using namespace std;

int main() {
    string N;
    cin >> N;

    string equalNines = "";
    string minusNines = "";
    for (int i = 0; i < N.length(); i++) {
        equalNines += '9';
    }
    for (int i = 0; i < N.length() - 1; i++) {
        minusNines += '9';
    }

    long long nNumber = stoll(N);
    long long equalNumber = stoll(equalNines);
    long long minusNumber = minusNines.empty() ? 0 : stoll(minusNines);

    if (equalNumber > nNumber) {
        long long changeNumber = nNumber - minusNumber;
        long long changeDigitSum = 0;
        while (changeNumber > 0) {
            changeDigitSum += changeNumber % 10;
            changeNumber /= 10;
        }
        cout << 9 * minusNines.length() + changeDigitSum;
    } else {
        cout << 9 * equalNines.length();
    }

    return 0;
}
