#include <bits/stdc++.h>

using namespace std;

int main() {

  int N;

  cin >> N;

  int squadArray[N];

  for (int i = 0; i < N; i++) {

    cin >> squadArray[i];
  }

  int prefixSum[N];

  int suffixSum[N];

  prefixSum[0] = squadArray[0];

  for (int i = 1; i < N; i++) {

    prefixSum[i] = squadArray[i] + prefixSum[i - 1];
  }

  suffixSum[N - 1] = squadArray[N - 1];

  for (int i = N - 2; i >= 0; i--) {

    suffixSum[i] = squadArray[i] + suffixSum[i + 1];
  }

  int minDifference = INT_MAX;

  for (int i = 1; i < N - 1; i++) {

    int leftSum = prefixSum[i - 1];

    int rightSum = suffixSum[i + 1];

    int difference = abs(leftSum - rightSum);

    if (difference < minDifference) {

      minDifference = difference;
    }
  }

  cout << minDifference << endl;

  return 0;
}