#include <bits/stdc++.h>

using namespace std;

int MEM[31];

int FIB(int A) {
  if (MEM[A] != 0) {
    return MEM[A];
  }

  if (A == 0) {
    return 0;
  }
  if (A == 1) {
    return 1;
  }

  MEM[A] = FIB(A - 1) + FIB(A - 2);
  return MEM[A];
}

int main() {
  int N;
  cin >> N;

  cout << FIB(N) << endl;

  return 0;
}