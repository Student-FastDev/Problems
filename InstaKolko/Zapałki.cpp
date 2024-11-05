#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> numbersArray(N);

    for (int i = 0; i < N; i++) {
        cin >> numbersArray[i];
    }

    vector<int> leftBurn(N, 1), rightBurn(N, 1);

    for (int i = 1; i < N; i++) {
        if (numbersArray[i] >= numbersArray[i - 1]) {
            leftBurn[i] = leftBurn[i - 1] + 1;
        }
    }

    for (int i = N - 2; i >= 0; i--) {
        if (numbersArray[i] >= numbersArray[i + 1]) {
            rightBurn[i] = rightBurn[i + 1] + 1;
        }
    }

    int maxBurnedMatches = 0;
    for (int i = 0; i < N; i++) {
        maxBurnedMatches = max(maxBurnedMatches, leftBurn[i] + rightBurn[i] - 1);
    }

    cout << maxBurnedMatches << endl;
    return 0;
}
