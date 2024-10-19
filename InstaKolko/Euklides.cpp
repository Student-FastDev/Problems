#include <bits/stdc++.h>

using namespace std;

int x, y;

void algorytmEuklidesa(int a, int b)

{

  if (b != 0)

  {

    algorytmEuklidesa(b, a % b);

    int z = y;

    y = x - a / b * y;

    x = z;
  }
}

int main()

{

  x = 1, y = 0;

  int a, b;

  cin >> a >> b;

  algorytmEuklidesa(a, b);

  cout << "nwd(" << a << "," << b << ")=" << a << "*" << x << "+" << b << "*"
       << y << "=" << a * x + b * y << endl;

  return 0;
}