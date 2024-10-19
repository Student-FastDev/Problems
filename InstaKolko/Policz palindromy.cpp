#include <bits/stdc++.h>

using namespace std;

int sprawdzPalindromy(string napis) {
  int palindromy = 0;
  for (int i = 0; i < napis.size(); i++) {
    if ((napis[i] >= 'a' && napis[i] <= 'z') ||
        (napis[i] >= 'A' && napis[i] <= 'Z')) {
      string temp = "";
      while ((napis[i] >= 'a' && napis[i] <= 'z') ||
             (napis[i] >= 'A' && napis[i] <= 'Z')) {
        temp = temp + napis[i];
        i++;
      }

      string temp_Reversed = temp;
      reverse(temp_Reversed.begin(), temp_Reversed.end());

      if (temp_Reversed == temp) {
        palindromy++;
      }
    }
  }
  return palindromy;
}

int main() {
  string text;
  getline(cin, text);

  cout << sprawdzPalindromy(text);

  return 0;
}