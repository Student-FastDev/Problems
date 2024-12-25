#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const long long MAX_N = 1e9 + 1;
const long long MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;

    while (T--) {
        ll L, R, G;
        cin >> L >> R >> G;

        L = (L + G - 1) / G;
        R /= G;

        ll answerValue = -1, possibleLeft, possibleRight;

        for (ll i = L; i <= R; i++) {
            if (R - i + 1 <= answerValue) break;
            for (ll j = R; j >= i; j--) {
                if (j - i + 1 <= answerValue) break;
                if (__gcd(i, j) == 1) {
                    possibleLeft = i;
                    possibleRight = j;
                    answerValue = j - i + 1;
                    break;
                }
            }
        }

        if (answerValue == -1) {
            cout << "-1 -1\n";
        } else {
            cout << possibleLeft * G << " " << possibleRight * G << "\n";
        }
    }
    return 0;
}
