#include <bits/stdc++.h>

using namespace std;

int main() {

  int N, W;

  cin >> N >> W;

  vector > toysArray(N);

  for (int i = 0; i < N; i++) {

    cin >> toysArray[i].first >> toysArray[i].second;
  }

  vector > dp(N + 1, vector(W + 1, 0));

  for (int i = 1; i <= N; i++) {

    for (int j = 1; j <= W; j++) {

      if (toysArray[i - 1].first <= j) {

        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - toysArray[i - 1].first] +
                                         toysArray[i - 1].second);

      } else {

        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  cout << dp[N][W] << endl;

  return 0;
}