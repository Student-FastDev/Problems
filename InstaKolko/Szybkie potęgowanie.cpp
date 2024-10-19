#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

long long powerCalc(long long a, long long b) {

  if (b == 0)

    return 1;

  if (b % 2 == 0) {

    long long powerHalf = powerCalc(a, b / 2) % MOD;

    return (powerHalf * powerHalf) % MOD;

  } else {

    return (a * powerCalc(a, b - 1)) % MOD;
  }
}

int main() {

  long long a, b;

  cin >> a >> b;

  long long result = powerCalc(a, b);

  cout << result << endl;

  return 0;
}