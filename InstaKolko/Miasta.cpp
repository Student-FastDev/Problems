#include <bits/stdc++.h>

using namespace std;

int main() {

  int n, m;

  cin >> n >> m;

  vector > graf(n + 1);

  for (int i = 0; i < m; i++) {

    int a, b;

    cin >> a >> b;

    graf[a].push_back(b);

    graf[b].push_back(a);
  }

  int maxDrog = 0, miasto = 1;

  for (int i = 1; i <= n; i++) {

    if (graf[i].size() > maxDrog) {

      maxDrog = graf[i].size();

      miasto = i;
    }
  }

  cout << miasto << endl;

  for (int miastoPolaczone : graf[miasto]) {

    cout << miastoPolaczone << " ";
  }

  return 0;
}