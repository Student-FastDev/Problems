#include <bits/stdc++.h>

using namespace std;

int main()

{

  int N;

  cin >> N;

  int matrixArray[N][N];

  for (int i = 0; i < N; i++) {

    for (int j = 0; j < N; j++) {

      int A;

      cin >> A;

      matrixArray[i][j] = A;
    }
  }

  int K;

  cin >> K;

  for (int i = 0; i < K; i++) {

    int A;

    cin >> A;

    for (int j = 0; j < N; j++) {

      if (matrixArray[A][j] == 1) {

        cout << j << " ";
      }
    }

    cout << endl;
  }

  return 0;
}