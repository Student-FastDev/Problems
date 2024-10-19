#include <bits/stdc++.h>
#include countArray;

int main() {
  int N;
  cin >> N;

  int maxValue = -1;

  for (int i = 0; i < N; i++) {
    int A;
    cin >> A;

    countArray[A]++;

    maxValue = max(maxValue, countArray[A]);
  }

  cout << maxValue << endl;

  return 0;
}