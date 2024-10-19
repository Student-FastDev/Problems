#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string text;
  cin >> text;

  int suma = 0;

  for (int i = 0; i < text.length(); i++) {
    if (text[i] != '?') {
      suma = suma + text[i] - '0';
    }
  }

  for (int i = 0; i < 10; i++) {
    if ((suma + i) % 3 == 0) {
      cout << i;
      return 0;
    }
  }
  return 0;
}