#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, q;
  cin >> n >> q;
  int prefix[n + 1] = {};

  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    prefix[i] = prefix[i - 1] + a;
  }

  for (int i = 1; i <= q; i++) {
    int b;
    cin >> b;
    cout << prefix[b] << " ";
  }

  return 0;
}