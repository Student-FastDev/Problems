#include <bits/stdc++.h>

#include, int> MEMO;

int EUK(int A, int B) {

  if (MEMO.find({A, B}) != MEMO.end()) {

    return MEMO[{A, B}];
  }

  if (A < 0) {

    cout << B << " ";

    cout << A + B << endl;

    return MEMO[{A, B}] = B;
  }

  return MEMO[{A, B}] = EUK(B - A, A);
}

int main() {

  int N, K;

  cin >> N >> K;

  EUK(N, K);

  return 0;
}