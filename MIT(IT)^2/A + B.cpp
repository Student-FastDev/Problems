#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int a, b, c;
  cin >> a >> b >> c;
  if (c == 0)
    cout << a + b << "\n";
  else
    cout << a * b << "\n";
}
