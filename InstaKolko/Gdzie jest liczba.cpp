#include <bits/stdc++.h>

using namespace std;

int main()

{

  int N, Q;

  cin >> N >> Q;

  int array[N];

  for (int i = 0; i < N; i++) {

    cin >> array[i];
  }

  for (int i = 0; i < Q; i++) {

    int Z;

    cin >> Z;

    int middle;

    int start = 0;

    int end = N - 1;

    bool found = false;

    while (start <= end) {

      middle = (start + end) / 2;

      if (array[middle] >= Z) {

        end = middle - 1;

        if (array[middle] == Z) {

          found = true;
        }

      }

      else {

        start = middle + 1;
      }
    }

    if (found) {

      cout << start + 1 << endl;

    }

    else {

      cout << 0 << endl;
    }
  }

  return 0;
}