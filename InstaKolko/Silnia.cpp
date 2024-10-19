#include <bits/stdc++.h>

using namespace std;

long long silnia(long long n) {

  if (n == 0) {

    return 1;
  }

  return n * silnia(n - 1);
}

int main() {

  long long n;

  cin >> n;

  cout << silnia(n) << endl;

  return 0;
}