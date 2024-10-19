#include <bits/stdc++.h>

using namespace std;

int main() {

  int N, K;

  cin >> N >> K;

  vector zeroArray;

  int numbersArray[N];

  for (int i = 0; i < N; i++) {

    cin >> numbersArray[i];

    if (numbersArray[i] == 0) {

      zeroArray.push_back(i);
    }
  }

  int minDel = 10000000000;

  for (int i = K - 1; i < zeroArray.size(); i++) {

    minDel = min((zeroArray[i] - zeroArray[i - (K - 1)]) + 1 - K, minDel);
  }

  cout << minDel;

  return 0;
}