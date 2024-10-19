#include <bits/stdc++.h>

using namespace std;

int main()

{

  int N;

  cin >> N;

  pair > tab[N];

  for (int i = 0; i < N; i++) {

    int firstColor;

    int secondColor;

    cin >> firstColor >> secondColor;

    tab[i] = make_pair(firstColor, make_pair(secondColor, i));
  }

  sort(tab, tab + N);

  int Q;

  cin >> Q;

  for (int i = 0; i < Q; i++) {

    int firstColor;

    int secondColor;

    cin >> firstColor >> secondColor;

    int start = 0;

    int end = N - 1;

    int middle;

    bool found = false;

    while (start <= end) {

      middle = (start + end) / 2;

      if (tab[middle].first > firstColor ||
          (tab[middle].first == firstColor &&
           tab[middle].second.first > secondColor)) {

        end = middle - 1;

      }

      else if (tab[middle].first == firstColor &&
               tab[middle].second.first == secondColor) {

        found = true;

        break;

      }

      else {

        start = middle + 1;
      }
    }

    if (found) {

      cout << tab[middle].second.second + 1 << endl;

    }

    else {

      cout << "nieklasyfikowana" << endl;
    }
  }

  return 0;
}