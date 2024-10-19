#include <bits/stdc++.h>

using namespace std;

int main()

{

  vector liczbyZwyczajne;

  for (long long i = 1; i <= 18; i++) {

    for (long long j = 1; j <= 9; j++) {

      string temp;

      for (long long k = 0; k < i; k++) {

        temp += to_string(j);
      }

      liczbyZwyczajne.push_back(stoll(temp));
    }
  }

  int T;

  cin >> T;

  for (int i = 0; i < T; i++) {

    long long A;

    cin >> A;

    int licznik = 0;

    for (int j = 0; j < liczbyZwyczajne.size(); j++) {

      if (liczbyZwyczajne[j] <= A) {

        licznik++;
      }
    }

    cout << licznik << endl;
  }

  return 0;
}