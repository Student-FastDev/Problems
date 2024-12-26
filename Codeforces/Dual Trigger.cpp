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

    while(T--) {
        int N;
        string S;
        cin >> N >> S;

        int countOnes = count(S.begin(), S.end(), '1');

        if (countOnes == 0) {
            cout << "YES\n";
        } else if (countOnes % 2 == 1) {
            cout << "NO\n";
        } else if (countOnes == 2) {
            bool adjacent = false;
            for (int i = 0; i < N - 1; ++i) {
                if (S[i] == '1' && S[i + 1] == '1') {
                    adjacent = true;
                    break;
                }
            }
            cout << (adjacent ? "NO\n" : "YES\n");
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
