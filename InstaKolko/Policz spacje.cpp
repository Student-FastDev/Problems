#include <bits/stdc++.h>

using namespace std;

int sprawdzSpacje(string napis) {
  int spacje = 0;
  for (int i = 0; i < napis.size(); i++) {
    if (napis[i] == ' ') {
      spacje++;
    }
  }
  return spacje;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin.ignore();

  string text;
  getline(cin, text);

  cout << sprawdzSpacje(text);

  return 0;
}