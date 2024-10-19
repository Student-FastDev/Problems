#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> numberArray(N);

    for (int i = 0; i < N; ++i) {
        cin >> numberArray[i];
    }

    vector<int> abs_values(N);
    for (int i = 0; i < N; ++i) {
        abs_values[i] = abs(numberArray[i]);
    }

    sort(abs_values.begin(), abs_values.end());

    for (int i = 0; i < N; i++) {
        cout << abs_values[i];
        if (i < N - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}