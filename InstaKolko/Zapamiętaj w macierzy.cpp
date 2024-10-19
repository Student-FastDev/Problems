#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000;

bool matrixArray[MAX_N][MAX_N] = {0};

int main() {
  int N, K;
  cin >> N >> K;

  for (int i = 0; i < K; i++) {
    int A, B;
    cin >> A >> B;

    matrixArray[A][B] = 1;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << matrixArray[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}