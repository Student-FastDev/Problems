#include <bits/stdc++.h>

using namespace std;

bool sito[1000001] = {0};

int main() {
  int n;
  cin >> n;

  sito[0] = 1;
  sito[1] = 1;
  for (long long i = 2; i <= n; i++) {
    if (sito[i] == 0) {
      for (long long j = i * i; j <= n; j += i) {
        sito[j] = 1;
      }
    }
  }

  for (long long i = 2; i <= n; i++) {
    if (sito[i] == 0) {
      bool hasSeven = false;
      int liczba = i;

      while (liczba > 0) {
        if (liczba % 10 == 7) {
          hasSeven = true;
        }
        liczba = liczba / 10;
      }

      if (hasSeven) {
        cout << i << " ";
      }
    }
  }

  return 0;
}