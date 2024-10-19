#include <bits/stdc++.h>

using namespace std;

long long nwd(long long a, long long b) {

  while (b != 0) {

    long long temp = b;

    b = a % b;

    a = temp;
  }

  return a;
}

void uproscUlamek(long long &licznik, long long &mianownik) {

  long long wspolnyDzielnik = nwd(licznik, mianownik);

  licznik /= wspolnyDzielnik;

  mianownik /= wspolnyDzielnik;
}

void dodajUlamek(long long licznik1, long long mianownik1, long long licznik2,
                 long long mianownik2, long long &wynikLicznik,
                 long long &wynikMianownik) {

  wynikLicznik = licznik1 * mianownik2 + licznik2 * mianownik1;

  wynikMianownik = mianownik1 * mianownik2;

  uproscUlamek(wynikLicznik, wynikMianownik);
}

int main() {

  long long q;

  cin >> q;

  for (long long i = 0; i < q; ++i) {

    long long licznik1, mianownik1, licznik2, mianownik2;

    cin >> licznik1 >> mianownik1 >> licznik2 >> mianownik2;

    long long wynikLicznik, wynikMianownik;

    dodajUlamek(licznik1, mianownik1, licznik2, mianownik2, wynikLicznik,
                wynikMianownik);

    cout << wynikLicznik << " " << wynikMianownik << endl;
  }

  return 0;
}