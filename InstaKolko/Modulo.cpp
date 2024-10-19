#include <bits/stdc++.h>

using namespace std;

int main() {

  const int rozmiarTablicy = 37;

  int reszty[rozmiarTablicy] = {0};

  for (int i = 0; i < 15; ++i) {

    int liczba;

    cin >> liczba;

    int reszta = liczba % 37;

    if (reszty[reszta] == 0) {

      reszty[reszta] = 1;
    }
  }

  int liczbaRoznychReszt = 0;

  for (int i = 0; i < rozmiarTablicy; ++i) {

    if (reszty[i] == 1) {

      liczbaRoznychReszt++;
    }
  }

  cout << liczbaRoznychReszt << endl;

  return 0;
}