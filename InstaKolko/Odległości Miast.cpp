#include <bits/stdc++.h>

using namespace std;

void BFS(vector > &neighbourList, int start, int destination) {

  int n = neighbourList.size();

  vector distance(n, INT_MAX);

  vector visited(n, false);

  queue q;

  distance[start] = 0;

  visited[start] = true;

  q.push(start);

  while (!q.empty()) {

    int current = q.front();

    q.pop();

    if (current == destination) {

      cout << distance[current];

      return;
    }

    for (int neighbor : neighbourList[current]) {

      if (!visited[neighbor]) {

        visited[neighbor] = true;

        distance[neighbor] = distance[current] + 1;

        q.push(neighbor);
      }
    }
  }

  cout << "NIE MA";
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

  int destination;

  cin >> destination;

  BFS(neighbourList, 1, destination);

  return 0;
}