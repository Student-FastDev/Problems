#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> a(N), b(N);
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> b[i];
        }
 
        vector<int> DP(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            DP[i + 1] = max(DP[i + 1], DP[i] + a[i] - (i + 1 < N ? b[i + 1] : 0));
            DP[i + 1] = max(DP[i + 1], DP[i]);
        }
 
        cout << DP[N] << endl;
    }
    return 0;
}
