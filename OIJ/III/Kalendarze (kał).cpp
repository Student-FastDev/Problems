#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> arbuzanMonths(n);
    vector<int> bananitMonths(m);

    vector<int> arbuzanPrefixSum(n + 1, 0);
    vector<int> bananitPrefixSum(m + 1, 0);

    for (int i = 0; i < n; ++i) {
        cin >> arbuzanMonths[i];
        arbuzanPrefixSum[i + 1] = arbuzanPrefixSum[i] + arbuzanMonths[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> bananitMonths[i];
        bananitPrefixSum[i + 1] = bananitPrefixSum[i] + bananitMonths[i];
    }

    int q;
    cin >> q;

    while (q--) {
        int day, month;
        char type;
        cin >> day >> month >> type;

        int totalDays;
        if (type == 'A') {
            totalDays = arbuzanPrefixSum[month - 1] + day;

            int bananitMonth = lower_bound(bananitPrefixSum.begin(), bananitPrefixSum.end(), totalDays) - bananitPrefixSum.begin();
            int bananitDay = totalDays - bananitPrefixSum[bananitMonth - 1];
            cout << bananitDay << " " << bananitMonth << endl;
        } else {
            totalDays = bananitPrefixSum[month - 1] + day;

            int arbuzanMonth = lower_bound(arbuzanPrefixSum.begin(), arbuzanPrefixSum.end(), totalDays) - arbuzanPrefixSum.begin();
            int arbuzanDay = totalDays - arbuzanPrefixSum[arbuzanMonth - 1];
            cout << arbuzanDay << " " << arbuzanMonth << endl;
        }
    }

    return 0;
}