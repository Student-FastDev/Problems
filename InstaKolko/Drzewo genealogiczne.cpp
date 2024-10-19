#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000;

vector neighbourList[MAX_N];

bool visitedList[MAX_N];

int sumList[MAX_N];

int dfs(int W) {

  visitedList[W] = true;

  int sum = 0;

  for (auto i : neighbourList[W]) {

    if (!visitedList[i]) {

      sum += dfs(i);
    }
  }

  sumList[W] = sum;

  return sum + 1;
}

int main()

{

  int N;

  cin >> N;

  for (int i = 2; i < N + 1; i++) {

    int A;

    cin >> A;

    neighbourList[A].push_back(i);
  }

  dfs(1);

  for (int i = 1; i <= N; i++) {

    cout << sumList[i] << " ";
  }

  return 0;
}