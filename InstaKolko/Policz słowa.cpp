#include <bits/stdc++.h>

using namespace std;

int sprawdzSlowa(string napis) {
  int slowa = 0;
  for (int i = 0; i < napis.size(); i++) {
    if ((napis[i] >= 'a' && napis[i] <= 'z') ||
        (napis[i] >= 'A' && napis[i] <= 'Z')) {
      slowa++;
      while ((napis[i] >= 'a' && napis[i] <= 'z') ||
             (napis[i] >= 'A' && napis[i] <= 'Z')) {
        i++;
      }
    }
  }
  return slowa;
}

int main() {
  string text;
  getline(cin, text);

  cout << sprawdzSlowa(text);

  return 0;
}