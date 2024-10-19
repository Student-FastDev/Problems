#include <bits/stdc++.h>

using namespace std;

int main() {
  string tab[3][3];

  for (int i = 0; i < 3; i++) {
    string text;
    for (int j = 0; j < 3; j++) {
      cin >> tab[i][j];
    }

    if (tab[i][0] == "Tomek") {
      cout << tab[i][2];
      return 0;
    }
  }

  return 0;
}