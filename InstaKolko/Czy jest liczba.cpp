#include <bits/stdc++.h>

using namespace std;

int main()

{

  int N, Q;

  cin >> N >> Q;

  int tab[N];

  for (int i = 0; i < N; i++) {

    cin >> tab[i];
  }

  sort(tab, tab + N);

  for (int i = 0; i < Q; i++) {

    int Z;

    cin >> Z;

    int start = 0;

    int end = N - 1;

    int middle;

    bool found = false;

    while (start <= end) {

      middle = (start + end) / 2;

      if (tab[middle] > Z) {

        end = middle - 1;

      }

      else if (tab[middle] == Z) {

        found = true;

        break;

      }

      else {

        start = middle + 1;
      }
    }

    if (found) {

      cout << "TAK" << endl;

    }

    else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}