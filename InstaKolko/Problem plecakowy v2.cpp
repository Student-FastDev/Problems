#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, W;
    cin >> N >> W;

    vector<int> DP(W + 1, 0);

    for (int i = 0; i < N; ++i) {
        int A, B;
        cin >> A >> B;

        for (int w = W; w >= A; --w) {
            DP[w] = max(DP[w], DP[w - A] + B);
        }
    }

    cout << DP[W] << endl;

    return 0;
}
