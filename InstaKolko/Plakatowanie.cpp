#include <bits/stdc++.h>

using namespace std;

int main() {

  int N;

  cin >> N;

  int liczbaPlakatow = 0;

  stack stosBudynkow;

  for (int i = 0; i < N; i++) {

    int D, W;

    cin >> D >> W;

    if (stosBudynkow.empty()) {

      stosBudynkow.push(W);

      liczbaPlakatow++;

    }

    else {

      if (stosBudynkow.top() != W) {

        liczbaPlakatow++;
      }
    }
  }

  cout << liczbaPlakatow;

  return 0;
}