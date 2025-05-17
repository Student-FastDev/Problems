#include <bits/stdc++.h>

using namespace std;

set<long long> setvar;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int n;
  long long tt;
  string t;
  cin >> n;

  for (int i = 0; i < n; i++) {

    cin >> t;

    if (t == "maxdiff")
    {
      if (setvar.empty())
      {
        cout << 0 << '\n';
        continue;
      }

      long long min = *setvar.begin();
      long long max = *setvar.rbegin();
      cout << (max - min) << '\n';
      continue;
    }

    cin >> tt;

    if (t == "insert") {
      setvar.insert(tt);
    }
    else if (t == "erase") // I know.
    {
      setvar.erase(tt);
    }
  }
  return 0;
}