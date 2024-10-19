#include <bits/stdc++.h>

using namespace std;

int main() {

  string k, l;

  cin >> k >> l;

  if (k.length() != l.length()) {

    cout << "NIE" << endl;

    return 0;
  }

  int tab_k[127] = {0};

  int tab_l[127] = {0};

  for (int i = 0; i < k.length(); i++) {

    tab_k[k[i]]++;

    tab_l[l[i]]++;
  }

  for (int i = 0; i < 127; i++) {

    if (tab_k[i] != tab_l[i]) {

      cout << "NIE" << endl;

      return 0;
    }
  }

  cout << "TAK" << endl;

  return 0;
}