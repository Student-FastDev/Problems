#include <bits/stdc++.h>

#include mapaZliczanie;

for (int i = 0; i < N; i++) {
  int tempNumber;
  cin >> tempNumber;

  mapaZliczanie[tempNumber]++;
}

for (auto const &i : mapaZliczanie) {
  for (int j = 0; j < i.second; j++) {
    cout << i.first << " ";
  }
}

return 0;
}