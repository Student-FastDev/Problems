#include <bits/stdc++.h>

using namespace std;

string DodajDwieDużeLiczby(string a, string b) {

  int carry = 0;

  string wynik;

  int max_len = max(a.length(), b.length());

  a = string(max_len - a.length(), '0') + a;

  b = string(max_len - b.length(), '0') + b;

  for (int i = max_len - 1; i >= 0; i--) {

    int cyfra_a = a[i] - '0';

    int cyfra_b = b[i] - '0';

    int suma = cyfra_a + cyfra_b + carry;

    carry = suma / 10;

    suma %= 10;

    wynik = to_string(suma) + wynik;
  }

  if (carry > 0) {

    wynik = to_string(carry) + wynik;
  }

  return wynik;
}

int main() {

  string a, b;

  cin >> a;

  cin >> b;

  string suma = DodajDwieDużeLiczby(a, b);

  cout << suma << endl;

  return 0;
}