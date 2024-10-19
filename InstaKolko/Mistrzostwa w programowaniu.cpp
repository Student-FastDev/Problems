#include <bits/stdc++.h>

using namespace std;

struct teamResult {

  string name;

  vector results;
};

bool isBetter(const vector &a, const vector &b) {

  int common = min(a.size(), b.size());

  for (int i = 0; i < common; ++i) {

    if (a[i] != b[i]) {

      return a[i] < b[i];
    }
  }

  return a.size() < b.size();
}

bool compareResults(const teamResult &a, const teamResult &b) {

  return isBetter(a.results, b.results);
}

int main() {

  int n;

  cin >> n;

  vector results(n);

  for (int i = 0; i < n; ++i) {

    int m;

    cin >> m >> results[i].name;

    results[i].results.resize(m);

    for (int j = 0; j < m; ++j) {

      cin >> results[i].results[j];
    }

    sort(results[i].results.begin(), results[i].results.end());
  }

  sort(results.begin(), results.end(), compareResults);

  int t;

  cin >> t;

  while (t--) {

    int k;

    cin >> k;

    cout << results[k - 1].name << endl;
  }

  return 0;
}