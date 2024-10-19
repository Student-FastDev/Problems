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

int sprawdzZdania(string napis) {
  int zdania = 0;
  for (int i = 0; i < napis.length(); i++) {
    if (napis[i] != '.') {
      string temp = "";
      while (napis[i] != '.') {
        if (i == napis.length() - 1) {
          return zdania;
        }
        temp = temp + napis[i];
        i++;
      }

      if (sprawdzSlowa(temp) >= 1) {
        zdania++;
      }
    }
  }
  return zdania;
}

int main() {
  string text;
  getline(cin, text);

  cout << sprawdzZdania(text);

  return 0;
}