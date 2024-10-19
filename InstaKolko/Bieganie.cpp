#include <bits/stdc++.h>

using namespace std;

int main() {

  long long n, q;

  cin >> n >> q;

  long long km[n + 1];

  for (long long i = 1; i <= n; ++i) {

    cin >> km[i];

    km[i] += km[i - 1];
  }

  for (long long i = 0; i < q; ++i) {

    long long b, c;

    cin >> b >> c;

    long long result = km[c] - km[b - 1];

    cout << result << endl;
  }

  return 0;
}