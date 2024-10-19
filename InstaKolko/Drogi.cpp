#include <bits/stdc++.h>

using namespace std;

int main() {

  int t;

  cin >> t;

  for (int i = 0; i < t; i++) {

    int a, b, k;

    cin >> a >> b >> k;

    vector > tab(a, vector(b, 0));

    for (int j = 0; j < a; j++) {

      for (int l = 0; l < b; l++) {

        if (j == 0 && l == 0) {

          tab[j][l] = 0;

        }

        else if (j == 0) {

          tab[j][l] = tab[j][l - 1] + j + 1;

        }

        else if (l == 0) {

          tab[j][l] = tab[j - 1][l] + l + 1;

        }

        else {

          tab[j][l] = min(tab[j][l - 1] + j + 1, tab[j - 1][l] + l + 1);
        }
      }
    }

    if (tab[a - 1][b - 1] == k) {

      cout << "TAK" << endl;

    }

    else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}