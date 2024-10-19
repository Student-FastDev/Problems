#include <bits/stdc++.h>

using namespace std;

void crownGenerator(int N) {

  if (N == 1) {

    cout << ">" << endl;

  } else {

    int middle = N / 2;

    crownGenerator(middle);

    for (int i = 0; i < N; i++) {

      cout << ">";
    }

    cout << endl;

    crownGenerator(middle);
  }
}

int main() {

  int N;

  cin >> N;

  crownGenerator(N);

  return 0;
}