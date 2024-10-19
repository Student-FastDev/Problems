#include <bits/stdc++.h>

using namespace std;

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    int N;
    string A;
    cin >> N;
    cin >> A;

    int symbolArray[100] = {0};
    symbolArray[int(A[0])]++;

    bool isPossible = true;

    for (int j = 1; j < A.length(); j++) {
      symbolArray[int(A[j])]++;
      if (symbolArray[int(A[j])] >= 2 && A[j] != A[j - 1]) {
        isPossible = false;
        break;
      }
    }

    if (isPossible) {
      cout << "TAK" << endl;
    } else {
      cout << "NIE" << endl;
    }
  }

  return 0;
}