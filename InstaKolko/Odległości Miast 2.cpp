#include <bits/stdc++.h>

using namespace std;

vector BFS(vector > &neighbourList, int start) {

  int n = neighbourList.size();

  vector visited(n, false);

  vector distance(n, INT_MAX);

  queue q;

  distance[start] = 0;

  visited[start] = true;

  q.push(start);

  while (!q.empty()) {

    int current = q.front();

    q.pop();

    for (int neighbor : neighbourList[current]) {

      if (!visited[neighbor]) {

        visited[neighbor] = true;

        distance[neighbor] = distance[current] + 1;

        q.push(neighbor);
      }
    }
  }

  return distance;
}

int main() {

  int n, m, t;

  cin >> n >> m >> t;

  vector > neighbourList(n + 1);

  for (int i = 0; i < m; i++) {

    int a, b;

    cin >> a >> b;

    neighbourList[a].push_back(b);

    neighbourList[b].push_back(a);
  }

  vector distance = BFS(neighbourList, 1);

  for (int i = 0; i < t; i++) {

    int temp;

    cin >> temp;

    if (distance[temp] == INT_MAX)

      cout << "NIE MA" << endl;

    else

      cout << distance[temp] << endl;
  }

  return 0;
}