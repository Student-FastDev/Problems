#include <bits/stdc++.h>

using namespace std;

int main() {

  const int n = 1000001;

  vector pierwsze;

  bool sito[n];

  int sito_liczby[n] = {0};

  sito[0] = true;

  sito[1] = true;

  for (long long i = 2; i * i <= n; i++) {

    if (!sito[i]) {

      for (long long j = 2 * i; j <= n; j += i) {

        sito[j] = true;

        sito_liczby[j]++;
      }
    }
  }

  int a;

  cin >> a;

  int max = -1, max_liczba = -1;

  for (int i = 0; i < a; i++) {

    int b;

    cin >> b;

    if (sito_liczby[b] > max_liczba) {

      max_liczba = sito_liczby[b];

      max = i + 1;

    }

    else if (sito_liczby[b] == max_liczba) {

      max_liczba = sito_liczby[b];

      max = i + 1;
    }
  }

  cout << max;

  return 0;
}