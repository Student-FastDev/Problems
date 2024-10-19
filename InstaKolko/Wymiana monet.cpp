#include <bits/stdc++.h>

using namespace std;

long long jeden, dwa;

int main() {

  cin >> dwa >> jeden;

  jeden = jeden / 2;

  if (dwa > jeden) {

    cout << jeden;

  }

  else {

    cout << (jeden + dwa) / 2;
  }

  return 0;
}