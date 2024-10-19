#include <bits/stdc++.h>

using namespace std;

int main() {

  long long a;

  cin >> a;

  vector cyfry;

  if (a == 0) {

    cyfry.push_back(0);

  } else if (a < 0) {

    cout << "-";

    a = -a;
  }

  while (a > 0) {

    int cyfra = a % 10;

    cyfry.push_back(cyfra);

    a /= 10;
  }

  for (int i = cyfry.size() - 1; i >= 0; i--) {

    cout << cyfry[i] << " ";
  }

  return 0;
}