#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {

    int tab[4];
    for (int j = 0; j < 4; j++) {
      cin >> tab[j];
    }

    int wonFirst = max(tab[0], tab[1]);

    int wonSecond = max(tab[2], tab[3]);

    sort(tab, tab + 4);

    if ((wonFirst == tab[2] || wonFirst == tab[3]) &&
        (wonSecond == tab[2] || wonSecond == tab[3])) {
      cout << "TAK" << endl;
    } else {
      cout << "NIE" << endl;
    }
  }

  return 0;
}