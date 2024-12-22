#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;
        
        vector<int> a(M);
        for (int i = 0; i < M; ++i) {
            cin >> a[i];
        }
        
        vector<bool> known(N + 1, false);
        for (int i = 0; i < K; ++i) {
            int Q;
            cin >> Q;
            known[Q] = true;
        }
        
        vector<int> prefixKnown(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            prefixKnown[i] = prefixKnown[i - 1] + (known[i] ? 1 : 0);
        }
        
        string result = "";
        for (int i = 0; i < M; ++i) {
            int missingQuestion = a[i];
            int knownCount = prefixKnown[N] - prefixKnown[missingQuestion] + prefixKnown[missingQuestion - 1];
            if (knownCount == N - 1) {
                result += '1';
            } else {
                result += '0';
            }
        }
        
        cout << result << endl;
    }
    return 0;
}
