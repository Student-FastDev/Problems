#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> values(5 * n);
  for (int i = 0; i < n * 5; i++)
    cin >> values[i];
  sort(values.begin(), values.end());
  long double x = 0;
  for (int i = n; i < n*4; i++) {
    x += values[i];
  }
  x /= 3*n;
  cout << setprecision(20) << x << "\n";
}
