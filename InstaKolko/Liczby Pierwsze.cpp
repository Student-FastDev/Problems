#include <bits/stdc++.h>

using namespace std;

int main() {
  int t, l;
  cin >> t;

  for (int i = 0; i < t; i++) {
    cin >> l;
    bool isPrime = true;

    for (int j = 2; j <= sqrt(l); j++) {
      if (l % j == 0) {
        isPrime = false;
        break;
      }
    }

    if (isPrime) {
      cout << "TAK" << endl;
    } else {
      cout << "NIE" << endl;
    }
  }

  return 0;
}