#include <bits/stdc++.h>

using namespace std;

string multiplyStrings(string num1, string num2) {
  int len1 = num1.length();
  int len2 = num2.length();

  int result[len1 + len2] = {0};

  for (int i = len1 - 1; i >= 0; i--) {
    for (int j = len2 - 1; j >= 0; j--) {
      int product = (num1[i] - '0') * (num2[j] - '0');
      int sum = product + result[i + j + 1];
      result[i + j] += sum / 10;
      result[i + j + 1] = sum % 10;
    }
  }

  string resultStr = "";
  bool leadingZeros = true;
  for (int i = 0; i < len1 + len2; i++) {
    if (result[i] != 0 || !leadingZeros) {
      resultStr += to_string(result[i]);
      leadingZeros = false;
    }
  }

  if (resultStr.empty()) {
    return "0";
  }

  return resultStr;
}

int main() {
  string a, b;
  cin >> a >> b;

  cout << multiplyStrings(a, b);

  return 0;
}