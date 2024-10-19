#include <bits/stdc++.h>

using namespace std;

int main() {

  long long n;

  cin >> n;

  long long numbersArray[n];

  for (long long i = 0; i < n; i++) {

    cin >> numbersArray[i];
  }

  long long maxSum[n];

  maxSum[0] = numbersArray[0];

  maxSum[1] = max(numbersArray[0], numbersArray[1]);

  for (long long i = 2; i < n; i++) {

    maxSum[i] = max(maxSum[i - 1], maxSum[i - 2] + numbersArray[i]);
  }

  cout << maxSum[n - 1] << endl;

  return 0;
}