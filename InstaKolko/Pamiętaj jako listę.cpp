#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000;

vector neighbourList[MAX_N];

int main()

{

  int N, K;

  cin >> N >> K;

  for (int i = 0; i < K; i++) {

    int A, B;

    cin >> A >> B;

    neighbourList[A].push_back(B);
  }

  for (int i = 0; i < N; i++) {

    for (int j = 0; j < neighbourList[i].size(); j++) {

      cout << neighbourList[i][j] << " ";
    }

    cout << endl;
  }

  return 0;
}