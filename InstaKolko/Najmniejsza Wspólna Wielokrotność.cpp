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

  long long n;

  cin >> n;

  for (int i = 0; i < n; i++) {

    long long a, b;

    cin >> a >> b;

    cout << (a * b) / NWD(a, b) << endl;
  }

  return 0;
}