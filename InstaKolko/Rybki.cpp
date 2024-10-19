#include <bits/stdc++.h>

using namespace std;

int main() {

  ios_base::sync_with_stdio(0);

  cin.tie(0);

  cout.tie(0);

  int n;

  cin >> n;

  vector liczbaRybekDoDnia(n + 1, 0);

  for (int i = 0; i < n; ++i) {

    int dni;

    cin >> dni;

    liczbaRybekDoDnia[dni]++;
  }

  int suma = 0;

  for (int i = 1; i <= n; ++i) {

    suma += liczbaRybekDoDnia[i];

    cout << suma << endl;
  }

  return 0;
}