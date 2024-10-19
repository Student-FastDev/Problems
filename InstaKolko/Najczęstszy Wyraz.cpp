#include <bits/stdc++.h>
#include countingMap;

for (int i = 0; i < n; i++) {
  int a;
  cin >> a;

  countingMap[a]++;
}

int maxAppearance = -1;
int maxNumber = -1;

for (auto i : countingMap) {
  if (i.second > maxAppearance) {
    maxAppearance = i.second;
    maxNumber = i.first;
  }
}

cout << maxNumber;

return 0;
}