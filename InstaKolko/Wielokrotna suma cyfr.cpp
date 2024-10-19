#include <bits/stdc++.h>

using namespace std;

long long digitSum(long long N) {

  if (N < 10) {

    return N;
  }

  long long sum = 0;

  while (N > 0) {

    sum += N % 10;

    N /= 10;
  }

  return digitSum(sum);
}

int main() {

  long long N;

  cin >> N;

  cout << digitSum(N);

  return 0;
}