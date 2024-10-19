#include <bits/stdc++.h>

using namespace std;

void BFS(vector > &neighbourList, int start) {

  int n = neighbourList.size();

  vector visited(n, false);

  queue q;

  visited[start] = true;

  q.push(start);

  while (!q.empty()) {

    int current = q.front();

    q.pop();

    cout << current << " ";

    for (int neighbor : neighbourList[current]) {

      if (!visited[neighbor]) {

        visited[neighbor] = true;

        q.push(neighbor);
      }
    }
  }
}

int main() {

  int n, m;

  cin >> n >> m;

  vector > neighbourList(n + 1);

  for (int i = 0; i < m; ++i) {

    int a, b;

    cin >> a >> b;

    neighbourList[a].push_back(b);

    neighbourList[b].push_back(a);
  }

  int start;

  cin >> start;

  BFS(neighbourList, start);

  return 0;
}