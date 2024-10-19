#include <bits/stdc++.h>

using namespace std;

int sumaDzielnikow(int n) {

  int suma = 1;

  for (int i = 2; i * i <= n; ++i) {

    if (n % i == 0) {

      suma += i;

      if (i != n / i) {

        suma += n / i;
      }
    }
  }

  return suma;
}

int main() {

  int t;

  cin >> t;

  vector pytania(t);

  for (int i = 0; i < t; ++i) {

    cin >> pytania[i];
  }

  for (int i = 0; i < t; ++i) {

    int liczba = pytania[i];

    int suma = sumaDzielnikow(liczba);

    if (suma == liczba) {

      cout << "TAK" << endl;

    } else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}