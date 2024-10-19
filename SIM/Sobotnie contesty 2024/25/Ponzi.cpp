#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        long long D, K, X;
        cin >> D >> K >> X;

        vector<long long> kPower(D + 1);
        vector<long long> sumTable(D + 1);

        kPower[0] = 1;
        for (long long j = 1; j <= D; j++) {
            kPower[j] = kPower[j - 1] * K;
        }

        sumTable[0] = kPower[0];
        for (long long j = 1; j <= D; j++) {
            sumTable[j] = sumTable[j - 1] + kPower[j];
        }

        long long finalSum = sumTable[D];
        long long stepNumber = 0;

        for (long long j = D; j >= 0; j--) {
            if (sumTable[j] == 0) continue;
            if (finalSum >= X) {
                stepNumber += (finalSum - X) / sumTable[j];
                finalSum = ((finalSum - X) % sumTable[j]) + X;
            }
            if (finalSum == X) {
                cout << stepNumber << endl;
                break;
            }
        }
    }

    return 0;
}