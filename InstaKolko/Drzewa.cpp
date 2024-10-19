#include <bits/stdc++.h>

using namespace std;

int main() {

  string opis_sadu;

  cin >> opis_sadu;

  int n = opis_sadu.length();

  vector sumy_prefiksowe(n + 1, 0);

  for (int i = 1; i <= n; ++i) {

    if (opis_sadu[i - 1] == 'b') {

      sumy_prefiksowe[i] = sumy_prefiksowe[i - 1] + 1;

    }

    else {

      sumy_prefiksowe[i] = sumy_prefiksowe[i - 1] + 0;
    }
  }

  int q;

  cin >> q;

  for (int i = 0; i < q; ++i) {

    int a, b;

    cin >> a >> b;

    int ilosc_brzoz = sumy_prefiksowe[b] - sumy_prefiksowe[a - 1];

    cout << ilosc_brzoz << endl;
  }

  return 0;
}