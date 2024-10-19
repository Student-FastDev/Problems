#include <bits/stdc++.h>

using namespace std;

void sortowanie_babelkowe(int tab[], int n)

{

  for (int i = 0; itab[j])

    swap(tab[j - 1], tab[j]);
}

int main()

{

  int l;

  cin >> l;

  int tab[l];

  for (int i = 0; i < l; i++) {

    cin >> tab[i];
  }

  sortowanie_babelkowe(tab, l);

  if (tab[0] > tab[l - 1]) {

    cout << tab[0] - tab[l - 1];

  }

  else {

    cout << tab[l - 1] - tab[0];
  }
}