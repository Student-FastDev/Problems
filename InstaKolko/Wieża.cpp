#include <bits/stdc++.h>

using namespace std;

int main() {

  int N, M;

  cin >> N >> M;

  vector stairsArray(N);

  for (int i = 0; i < N; i++) {

    cin >> stairsArray[i];
  }

  vector personArray(M);

  for (int i = 0; i < M; i++) {

    cin >> personArray[i];
  }

  for (int i = 1; i < N; i++) {

    stairsArray[i] = max(stairsArray[i], stairsArray[i - 1]);
  }

  for (int i = 0; i < M; i++) {

    int personHeight = personArray[i];

    int start = 0, end = N - 1, result = -1;

    while (start <= end) {

      int middle = (start + end) / 2;

      if (stairsArray[middle] < personHeight) {

        result = middle;

        start = middle + 1;

      } else {

        end = middle - 1;
      }
    }

    cout << (result + 1) << " ";
  }

  cout << endl;

  return 0;
}