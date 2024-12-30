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
        int numberOfSticks;
        cin >> numberOfSticks;
        vector<int> sticksLengths(numberOfSticks);

        for (int I = 0; I < numberOfSticks; ++I) {
            cin >> sticksLengths[I];
        }

        bool isPossible = false;
        for (int I = 0; I < numberOfSticks - 1; ++I) {
            if (2 * sticksLengths[I] > sticksLengths[I + 1] && 
                2 * sticksLengths[I + 1] > sticksLengths[I]) {
                isPossible = true;
                break;
            }
        }

        if (isPossible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
