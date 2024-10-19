#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000;

vector neighbourList[MAX_N];

bool visitedList[MAX_N];

void dfs(int W) {

  cout << W << " ";

  visitedList[W] = true;

  for (auto i : neighbourList[W]) {

    if (!visitedList[i]) {

      dfs(i);
    }
  }
}

int main()

{

  int N, M;

  cin >> N >> M;

  for (int i = 0; i < M; i++) {

    int A, B;

    cin >> A >> B;

    neighbourList[A].push_back(B);

    neighbourList[B].push_back(A);
  }

  int S;

  cin >> S;

  dfs(S);

  return 0;
}