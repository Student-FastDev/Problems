#include <bits/stdc++.h>

using namespace std;

int main() {

  int N;

  cin >> N;

  int numbersArray[N];

  for (int i = 0; i < N; i++) {

    cin >> numbersArray[i];
  }

  int K;

  cin >> K;

  int sum = 0;

  int num = 0;

  int begin = 0;

  for (int end = 0; end < N; end++) {

    sum += numbersArray[end];

    while (sum > K) {

      sum -= numbersArray[begin];

      begin++;
    }

    if (sum == K) {

      num++;
    }
  }

  cout << num;

  return 0;
}