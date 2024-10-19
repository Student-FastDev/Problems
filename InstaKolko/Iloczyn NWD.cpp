#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {

  while (b != 0) {

    int temp = b;

    b = a % b;

    a = temp;
  }

  return a;
}

int main() {

  int n, m;

  cin >> n >> m;

  vector numbers(n);

  for (int i = 0; i < n; ++i) {

    cin >> numbers[i];
  }

  long long result = 1;

  for (int i = 0; i < n; ++i) {

    for (int j = i + 1; j < n; ++j) {

      int gcd_value = gcd(numbers[i], numbers[j]);

      result = (result * gcd_value) % m;
    }
  }

  cout << result << endl;

  return 0;
}