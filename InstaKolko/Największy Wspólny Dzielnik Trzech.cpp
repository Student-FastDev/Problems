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

  int a, b, c;

  cin >> a >> b >> c;

  cout << NWD(a, NWD(b, c));

  return 0;
}