#include <bits/stdc++.h>

using namespace std;

void BFS(int start, vector > &neighbourList, vector &component, int compNum) {

  queue q;

  q.push(start);

  component[start] = compNum;

  while (!q.empty()) {

    int current = q.front();

    q.pop();

    for (int neighbor : neighbourList[current]) {

      if (component[neighbor] == -1) {

        component[neighbor] = compNum;

        q.push(neighbor);
      }
    }
  }
}

int main() {

  int n, m, t;

  cin >> n >> m >> t;

  vector > neighbourList(n + 1);

  vector component(n + 1, -1);

  for (int i = 0; i < m; ++i) {

    int a, b;

    cin >> a >> b;

    neighbourList[a].push_back(b);

    neighbourList[b].push_back(a);
  }

  int compNum = 0;

  for (int i = 1; i <= n; ++i) {

    if (component[i] == -1) {

      BFS(i, neighbourList, component, compNum++);
    }
  }

  for (int i = 0; i < t; ++i) {

    int c, d;

    cin >> c >> d;

    if (component[c] == component[d]) {

      cout << "TAK" << endl;

    } else {

      cout << "NIE" << endl;
    }
  }

  return 0;
}