#include <bits/stdc++.h>

using namespace std;

int main() {

  string s1, s2;

  cin >> s1 >> s2;

  int m = s1.length();

  int n = s2.length();

  vector > dp(m + 1, vector(n + 1, 0));

  for (int i = 1; i <= m; i++) {

    for (int j = 1; j <= n; j++) {

      if (s1[i - 1] == s2[j - 1]) {

        dp[i][j] = dp[i - 1][j - 1] + 1;

      } else {

        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  cout << dp[m][n] << endl;

  return 0;
}