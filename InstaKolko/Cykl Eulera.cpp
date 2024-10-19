#include <bits/stdc++.h>

using namespace std;

int main()

{

  int N;

  cin >> N;

  int matrixArray[N][N];

  bool isPossible = true;

  for (int i = 0; i < N; i++) {

    int edgeAmount = 0;

    for (int j = 0; j < N; j++) {

      int A;

      cin >> A;

      matrixArray[i][j] = A;

      if (A == 1) {

        edgeAmount++;
      }
    }

    if (edgeAmount % 2 != 0) {

      isPossible = false;
    }
  }

  if (isPossible) {

    cout << "TAK" << endl;

  }

  else {

    cout << "NIE" << endl;
  }

  return 0;
}