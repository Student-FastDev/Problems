#include <bits/stdc++.h>

using namespace std;

bool sito[1000001] = {0};

int main() {
  int t, a;
  int n = 1000000;
  cin >> t;

  sito[0] = 1;
  sito[1] = 1;

  for (long long i = 2; i <= n; i++) {
    if (sito[i] == 0) {
      for (long long j = i * i; j <= n; j += i) {
        sito[j] = 1;
      }
    }
  }

  for (int i = 0; i < t; i++) {
    cin >> a;
    int j = a + 1;
    while (sito[j] == 1) {
      j++;
    }
    cout << j << endl;
  }

  return 0;
}