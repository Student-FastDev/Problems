#include <bits/stdc++.h>

using namespace std;

int main()

{

  ios_base::sync_with_stdio(0);

  cin.tie(0);

  cout.tie(0);

  int n, d = 0;

  cin >> n;

  int tab1[n];

  int tab2[n];

  for (int i = 0; i < n; i++) {

    cin >> tab1[i];
  }

  for (int i = 0; i < n; i++) {

    cin >> tab2[i];
  }

  for (int i = 0; i < n; i++) {

    if (tab1[i] > tab2[i]) {

      d++;
    }
  }

  cout << d++;
}