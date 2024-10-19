#include <bits/stdc++.h>

using namespace std;

int main()

{

  int N;

  cin >> N;

  int array[N];

  for (int i = 0; i < N; i++) {

    cin >> array[i];
  }

  int Q;

  cin >> Q;

  int start = 0;

  int end = N - 1;

  bool empty = false;

  for (int i = 0; i < Q; i++) {

    int middle = (start + end) / 2;

    int Z;

    cin >> Z;

    if (end - start == 0) {

      empty = true;
    }

    if (Z == 0) {

      if ((start + end) % 2 == 0) {

        start = middle;

      }

      else {

        start = middle + 1;
      }

    }

    else if (Z == 1) {

      end = middle;
    }
  }

  if (empty) {

    cout << "PUSTO" << endl;

  }

  else {

    for (int i = start; i <= end; i++) {

      cout << array[i] << " ";
    }
  }

  return 0;
}