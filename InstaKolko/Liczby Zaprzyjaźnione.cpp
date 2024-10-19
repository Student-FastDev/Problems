#include <bits/stdc++.h>

using namespace std;

int divisSum(int n) {

  int sum = 0;

  for (int i = 1; i <= n / 2; ++i) {

    if (n % i == 0) {

      sum += i;
    }
  }

  return sum;
}

int main() {

  int t;

  cin >> t;

  vector > questionArray(t);

  for (int i = 0; i < t; ++i) {

    int a, b;

    cin >> a >> b;

    questionArray[i] = make_pair(a, b);
  }

  for (int i = 0; i < t; ++i) {

    int a = questionArray[i].first;

    int b = questionArray[i].second;

    if (divisSum(a) == b && divisSum(b) == a) {

      cout << "TAK" << endl;

    } else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}