#include <bits/stdc++.h>

using namespace std;

bool isChar(const string &x) {

  return x.length() == 1 && (x == "+" || x == "-" || x == "*" || x == "/");
}

int xToInt(const string &x) { return stoi(x); }

int main()

{

  int len;

  cin >> len;

  stack s;

  int i = 0;

  while (i < len) {

    string x;

    cin >> x;

    if (isChar(x)) {

      double a = s.top();

      s.pop();

      double b = s.top();

      s.pop();

      if (x[0] == '+')
        s.push(b + a);

      if (x[0] == '-')
        s.push(b - a);

      if (x[0] == '*')
        s.push(b * a);

      if (x[0] == '/')
        s.push(b / a);

    } else {

      s.push(xToInt(x));
    }

    i++;
  }

  cout << s.top();
}