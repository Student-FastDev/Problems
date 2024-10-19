#include <bits/stdc++.h>

using namespace std;

int NWD(int a, int b)

{

  if (a < b)
    swap(a, b);

  while (b != 0) {

    a = a % b;

    if (b > a) {

      swap(a, b);
    }
  }

  return a;
}

int main() {

  long long a, b, c;

  cin >> a >> b >> c;

  if (c % NWD(a, b) == 0) {

    cout << "TAK";

  }

  else {

    cout << "NIE";
  }

  return 0;
}