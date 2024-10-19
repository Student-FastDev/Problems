#include <bits/stdc++.h>

using namespace std;

const long long MAX_N = 1e5 + 1;
long long MEM[MAX_N];

const long long MOD = 1e9 + 7;

long long FIB(long long A) {
  if (MEM[A] != 0) {
    return MEM[A];
  }

  if (A == 0) {
    return 0;
  }
  if (A == 1) {
    return 1;
  }

  MEM[A] = (FIB(A - 1) + FIB(A - 2)) % MOD;
  return MEM[A];
}

int main() {
  long long N;
  cin >> N;

  cout << FIB(N) << endl;

  return 0;
}