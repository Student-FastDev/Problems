#include <bits/stdc++.h>

using namespace std;

vector findDivis(int n) {

  vector divisArray;

  for (int i = 1; i * i <= n; ++i) {

    if (n % i == 0) {

      divisArray.push_back(i);

      if (i != n / i) {

        divisArray.push_back(n / i);
      }
    }
  }

  sort(divisArray.rbegin(), divisArray.rend());

  return divisArray;
}

int main() {

  int t;

  cin >> t;

  while (t--) {

    int a;

    cin >> a;

    vector divisArray = findDivis(a);

    for (int divisNumber : divisArray) {

      cout << divisNumber << " ";
    }

    cout << endl;
  }

  return 0;
}