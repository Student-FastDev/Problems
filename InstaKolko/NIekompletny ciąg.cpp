#include <bits/stdc++.h>

using namespace std;

int main() {

  int N, K;

  cin >> N >> K;

  int maxValue = 0;

  vector uniqueArray(N);

  for (int i = 0; i < N; i++) {

    cin >> uniqueArray[i];

    maxValue = max(maxValue, uniqueArray[i]);
  }

  vector isAlready(maxValue + 1, 0);

  int uniqueNow = 0;

  int begin = 0;

  int maxA = -1;

  for (int end = 0; end < N; end++) {

    isAlready[uniqueArray[end]]++;

    if (isAlready[uniqueArray[end]] == 1) {

      uniqueNow++;
    }

    while (uniqueNow == K) {

      isAlready[uniqueArray[begin]]--;

      if (isAlready[uniqueArray[begin]] == 0) {

        uniqueNow--;
      }

      begin++;
    }

    maxA = max(maxA, (end - begin) + 1);
  }

  cout << maxA << endl;

  return 0;
}