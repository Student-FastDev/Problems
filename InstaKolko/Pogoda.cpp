#include <bits/stdc++.h>

using namespace std;

int main() {
  double monthsMax[13];
  double weeksAverage[49];

  double maxThisMonth = -1;
  double averageThisWeek = 0;
  for (int i = 1; i <= 336; i++) {
    double tempNow;
    cin >> tempNow;

    maxThisMonth = max(tempNow, maxThisMonth);
    averageThisWeek += tempNow;

    if (i % 7 == 0) {
      weeksAverage[i / 7] = averageThisWeek / 7;
      averageThisWeek = 0;
    }

    if (i % 28 == 0) {
      monthsMax[i / 28] = maxThisMonth;
      maxThisMonth = -1;
    }
  }

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char dataType;
    int numerData;

    cin >> dataType >> numerData;
    if (dataType == 't') {
      cout << fixed << setprecision(6) << weeksAverage[numerData] << endl;
    } else if (dataType == 'm') {
      cout << fixed << setprecision(6) << monthsMax[numerData] << endl;
    }
  }

  return 0;
}