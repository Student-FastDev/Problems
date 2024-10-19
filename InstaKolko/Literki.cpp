#include <bits/stdc++.h>

using namespace std;

int main() {

  string input;

  cin >> input;

  vector blokiTekstu;

  string tekstPlaceholder = "";

  for (int i = 0; i < input.length(); i++) {

    if (input[i] != '/') {

      tekstPlaceholder += input[i];

    }

    else {

      blokiTekstu.push_back(tekstPlaceholder);

      tekstPlaceholder = "";
    }
  }

  if (!tekstPlaceholder.empty()) {

    blokiTekstu.push_back(tekstPlaceholder);
  }

  for (int i = blokiTekstu.size() - 1; i >= 0; i--) {

    cout << blokiTekstu[i];

    if (i != 0) {

      cout << "/";
    }
  }

  return 0;
}