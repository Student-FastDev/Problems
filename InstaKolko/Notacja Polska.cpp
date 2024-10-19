#include <bits/stdc++.h>

using namespace std;

int oblicz(const string &operator_, int a, int b) {

  if (operator_ == "+")
    return a + b;

  if (operator_ == "-")
    return a - b;

  if (operator_ == "*")
    return a * b;

  if (operator_ == "/")
    return a / b;

  return 0;
}

int main() {

  string wejscie;

  getline(cin, wejscie);

  istringstream iss(wejscie);

  vector tokeny;

  string token;

  while (iss >> token) {

    tokeny.push_back(token);
  }

  stack stos;

  for (int i = tokeny.size() - 1; i >= 0; --i) {

    token = tokeny[i];

    if (isdigit(token[0]) || (token.length() > 1 && isdigit(token[1]))) {

      stos.push(stoi(token));

    } else {

      int a = stos.top();
      stos.pop();

      int b = stos.top();
      stos.pop();

      stos.push(oblicz(token, a, b));
    }
  }

  cout << stos.top() << endl;

  return 0;
}