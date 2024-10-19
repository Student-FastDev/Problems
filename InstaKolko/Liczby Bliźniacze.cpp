#include <bits/stdc++.h>

using namespace std;

int main() {
  int t, l1, l2;
  cin >> t;

  for (int i = 0; i < t; i++) {
    cin >> l1 >> l2;
    bool isPrime1 = true;
    bool isPrime2 = true;

    for (int j = 2; j <= sqrt(l1); j++) {
      if (l1 % j == 0) {
        isPrime1 = false;
        break;
      }
    }

    for (int j = 2; j <= sqrt(l2); j++) {
      if (l2 % j == 0) {
        isPrime2 = false;
        break;
      }
    }

    if (isPrime1 && isPrime2 && l2 - l1 == 2) {
      cout << "TAK" << endl;
    } else {
      cout << "NIE" << endl;
    }
  }

  return 0;
}