#include <bits/stdc++.h>

using namespace std;

int main() {

  int N;

  cin >> N;

  vector > GALAXIES;

  for (int i = 0; i < N; i++) {

    int ID;

    string NAME;

    cin >> ID >> NAME;

    GALAXIES.push_back(make_pair(ID, NAME));
  }

  int M;

  cin >> M;

  for (int i = 0; i < M; i++) {

    int SWAP1, SWAP2;

    cin >> SWAP1 >> SWAP2;

    swap(GALAXIES[SWAP1 - 1], GALAXIES[SWAP2 - 1]);
  }

  for (int i = 0; i < N; i++) {

    pair GALAXY = GALAXIES[i];

    cout << GALAXY.first << " " << GALAXY.second << endl;
  }

  return 0;
}