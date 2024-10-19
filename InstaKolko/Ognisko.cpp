#include <bits/stdc++.h>

using namespace std;

int main()

{

  int N;

  cin >> N;

  stack G;

  G.push(2147483648);

  for (int i = 0; i < N; i++) {

    int L;

    cin >> L;

    while (G.top() < L) {

      G.pop();
    }

    G.push(L);
  }

  cout << G.size() - 1;
}