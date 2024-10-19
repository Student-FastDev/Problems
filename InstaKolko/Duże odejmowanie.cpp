#include <bits/stdc++.h>

using namespace std;

string subtractStrings(string num1, string num2) {
  int len1 = num1.length();
  int len2 = num2.length();

  int maxLen = max(len1, len2);

  while (len1 < maxLen) {
    num1 = "0" + num1;
    len1++;
  }
  while (len2 < maxLen) {
    num2 = "0" + num2;
    len2++;
  }

  string result = "";
  int borrow = 0;

  for (int i = maxLen - 1; i >= 0; i--) {
    int digit1 = num1[i] - '0';
    int digit2 = num2[i] - '0';

    int diff = digit1 - digit2 - borrow;
    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    result = to_string(diff) + result;
  }

  while (result.length() > 1 && result[0] == '0') {
    result = result.substr(1);
  }

  return result;
}

int main() {
  string a, b;
  cin >> a >> b;

  cout << subtractStrings(a, b);

  return 0;
}