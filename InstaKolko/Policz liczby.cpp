#include <bits/stdc++.h>

using namespace std;

int sprawdzLiczby(string napis) {
  int liczby = 0;
  for (int i = 0; i < napis.size(); i++) {
    if (napis[i] >= '0' && napis[i] <= '9') {
      liczby++;
      while (napis[i] >= '0' && napis[i] <= '9') {
        i++;
      }
    }
  }
  return liczby;
}

int main() {
  string text;
  getline(cin, text);

  cout << sprawdzLiczby(text);

  return 0;
}