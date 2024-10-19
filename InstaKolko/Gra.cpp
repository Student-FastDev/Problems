#include <bits/stdc++.h>

using namespace std;

int main() {

  long long N;

  cin >> N;

  long long numbersArray[N];

  for (long long i = 0; i < N; i++) {

    cin >> numbersArray[i];
  }

  long long outputArray[N] = {0};

  outputArray[0] = numbersArray[0];

  for (long long i = 1; i < N; i++) {

    long long maxNumber = -10000000;

    for (long long j = 1; j <= 6; j++) {

      if (i - j >= 0) {

        maxNumber = max(maxNumber, outputArray[i - j]);
      }
    }

    outputArray[i] = maxNumber + numbersArray[i];
  }

  cout << outputArray[N - 1];

  return 0;
}