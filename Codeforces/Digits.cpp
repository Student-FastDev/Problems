#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        ll N, D;
        cin >> N >> D;
        vector<int> result;

        result.push_back(1);

        if (D % 3 == 0 || N >= 3) {
            result.push_back(3);
        }

        if (D == 5) {
            result.push_back(5);
        }

        if (N >= 3) {
            result.push_back(7);
        } else {
            if (N == 1 && D == 7) {
                result.push_back(7);
            } else if (N == 2 && D == 7) {
                result.push_back(7);
            }
        }

        if (D % 9 == 0 || N >= 6 || (N >= 3 && D % 3 == 0)) {
            result.push_back(9);
        }

        for (int digit : result) {
            cout << digit << " ";
        }
        cout << "\n";
    }

    return 0;
}
