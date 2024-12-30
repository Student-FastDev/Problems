#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;

    while (T--) {
        ll number, threshold;
        cin >> number >> threshold;

        ll result = 0;
        ll coefficientZero = 1;
        ll coefficientOne = 0;

        while (number >= threshold) {
            if (number % 2 == 0) {
                number /= 2;
                coefficientOne = 2 * coefficientOne + coefficientZero * number;
                coefficientZero *= 2;
            } else {
                result += (number + 1) / 2 * coefficientZero + coefficientOne;
                number /= 2;
                coefficientOne = 2 * coefficientOne + coefficientZero * (number + 1);
                coefficientZero *= 2;
            }
        }
        cout << result << "\n";
    }

    return 0;
}
