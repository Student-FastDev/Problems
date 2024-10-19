#include <bits/stdc++.h>

using namespace std;

vector generateFibonacci(int n) {

  vector fib;

  fib.push_back(0);

  fib.push_back(1);

  for (int i = 2; i <= n; ++i) {

    fib.push_back(fib[i - 1] + fib[i - 2]);
  }

  return fib;
}

pair findFibonacciPair(int m) {

  vector fib = generateFibonacci(50);

  for (int i = 0; i < fib.size(); ++i) {

    for (int j = i + 1; j < fib.size(); ++j) {

      if (fib[i] + fib[j] == m) {

        return make_pair(fib[i], fib[j]);
      }
    }
  }

  return make_pair(-1, -1);
}

int main() {

  int p;

  cin >> p;

  for (int i = 0; i < p; ++i) {

    int m;

    cin >> m;

    pair result = findFibonacciPair(m);

    if (result.first != -1 && result.second != -1) {

      cout << result.first << " " << result.second << endl;

    } else {

      cout << "NIE MA" << endl;
    }
  }

  return 0;
}