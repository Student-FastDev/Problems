#include <bits/stdc++.h>

using namespace std;

bool sito[100000] = {0};

int main() {
  int t, a;
  int n = 100000;
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
    if (sito[a]) {
      cout << "NIE" << endl;
    } else {
      cout << "TAK" << endl;
    }
  }

  return 0;
}