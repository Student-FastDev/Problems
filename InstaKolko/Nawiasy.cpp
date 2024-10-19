#include <bits/stdc++.h>

using namespace std;

bool czyPoprawneNawiasy(const string &ciagNawiasow) {

  stack stosNawiasow;

  for (char nawias : ciagNawiasow) {

    switch (nawias) {

    case '(':

    case '{':

    case '[':

    case '<':

      stosNawiasow.push(nawias);

      break;

    case ')':

      if (stosNawiasow.empty() || stosNawiasow.top() != '(')
        return false;

      stosNawiasow.pop();

      break;

    case '}':

      if (stosNawiasow.empty() || stosNawiasow.top() != '{')
        return false;

      stosNawiasow.pop();

      break;

    case ']':

      if (stosNawiasow.empty() || stosNawiasow.top() != '[')
        return false;

      stosNawiasow.pop();

      break;

    case '>':

      if (stosNawiasow.empty() || stosNawiasow.top() != '<')
        return false;

      stosNawiasow.pop();

      break;

    default:

      return false;
    }
  }

  return stosNawiasow.empty();
}

int main() {

  string ciagNawiasow;

  getline(cin, ciagNawiasow);

  if (czyPoprawneNawiasy(ciagNawiasow)) {

    cout << "Tak" << endl;

  } else {

    cout << "Nie" << endl;
  }

  return 0;
}