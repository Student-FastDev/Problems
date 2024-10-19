#include <bits/stdc++.h>

using namespace std;

bool porownajMiasta(const pair > &a, const pair > &b) {

  if (a.first != b.first) {

    return a.first > b.first;
  }

  return a.second < b.second;
}

int main() {

  int liczbaMiast, miastaDoOdwiedzenia;

  cin >> liczbaMiast >> miastaDoOdwiedzenia;

  vector >> miasta;

  for (int i = 0; i < liczbaMiast; ++i) {

    int liczbaKawiarni;

    cin >> liczbaKawiarni;

    vector numeryKawiarni(liczbaKawiarni);

    for (int j = 0; j < liczbaKawiarni; ++j) {

      cin >> numeryKawiarni[j];
    }

    sort(numeryKawiarni.begin(), numeryKawiarni.end());

    miasta.push_back(pair > (liczbaKawiarni, numeryKawiarni));
  }

  sort(miasta.begin(), miasta.end(), porownajMiasta);

  vector wszystkieNumeryKawiarni;

  for (int i = 0; i < miastaDoOdwiedzenia && i < miasta.size(); ++i) {

    wszystkieNumeryKawiarni.insert(wszystkieNumeryKawiarni.end(),
                                   miasta[i].second.begin(),
                                   miasta[i].second.end());
  }

  sort(wszystkieNumeryKawiarni.begin(), wszystkieNumeryKawiarni.end());

  cout << wszystkieNumeryKawiarni.size() << endl;

  for (int numerKawiarni : wszystkieNumeryKawiarni) {

    cout << numerKawiarni << " ";
  }

  cout << endl;

  return 0;
}