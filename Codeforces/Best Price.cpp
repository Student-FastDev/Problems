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
        int N, K;
        cin >> N >> K;
        
        vector<int> A(N);
        vector<int> B(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < N; i++) {
            cin >> B[i];
        }

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        long long maxAnswer = 0;
        for(int i = 0; i < N; i++) {
            auto checkAnswer = [&](long long value) -> long long {
                auto X = lower_bound(B.begin(), B.end(), value);
                auto Y = lower_bound(A.begin(), A.end(), value);
                int distanceFirst = distance(X, B.end());
                int distanceSecond = distance(Y, A.end());

                if(abs(distanceFirst - distanceSecond) <= K) {
                    return distanceFirst * value;
                }
                return 0;
            };

            maxAnswer = max(maxAnswer, checkAnswer(A[i]));
            maxAnswer = max(maxAnswer, checkAnswer(B[i]));
        }

        cout << maxAnswer << endl;
    }
    return 0;
}
