#include <bits/stdc++.h>

using namespace std;

int main() {
  int N;
  cin >> N;

  vector ballCounter;

  for (int i = 0; i < N; i++) {
    string A;
    cin >> A;

    ballCounter.push_back(A.length());
  }

  sort(ballCounter.begin(), ballCounter.end());

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < ballCounter[i]; j++) {
      cout << "O";
    }
    cout << endl;
  }

  return 0;
}