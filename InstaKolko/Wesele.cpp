#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000;

vector neighbourList[MAX_N];

int main()

{

  int N, K;

  cin >> N >> K;

  for (int i = 0; i < N; i++) {

    int A;

    cin >> A;

    for (int j = 0; j < A; j++) {

      int B;

      cin >> B;

      neighbourList[i].push_back(B);

      neighbourList[B].push_back(i);
    }
  }

  for (int i = 0; i < K; i++) {

    int A, B;

    cin >> A >> B;

    bool isThere = false;

    for (int i = 0; i < neighbourList[A].size(); i++) {

      if (neighbourList[A][i] == B) {

        isThere = true;

        break;
      }
    }

    if (isThere) {

      cout << "TAK" << endl;

    }

    else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}