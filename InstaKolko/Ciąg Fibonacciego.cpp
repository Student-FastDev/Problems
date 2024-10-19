#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

long long fib(long long n) {

  if (n == 0)
    return 0;

  if (n == 1)
    return 1;

  long long a = 0, b = 1, c;

  for (long long i = 2; i <= n; ++i) {

    c = (a + b) % MOD;

    a = b;

    b = c;
  }

  return b;
}

int main() {

  long long n;

  cin >> n;

  cout << fib(n);

  return 0;
}