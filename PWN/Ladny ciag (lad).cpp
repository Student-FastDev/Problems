#include <iostream>
using namespace std;

int main()
{
  int n, k, q;
  cin >> n >> k >> q;
  
  int zapytania[n];
  int maxZapytania = -1;
  
  for(int i = 0; i < n; i++) {
    cin >> zapytania[i];
    maxZapytania = max(maxZapytania, zapytania[i]);
  }
  
  int DP[maxZapytania+1][k+1] = {0};
  
  for(int i = 1; i <= maxZapytania; i++) {
    for(int j = 0; j <= k; j++) {
      if(i == 1) {
        DP[i][j] = 1;
        continue;
      }

      DP[i][j] = (j > 0 ? DP[i-1][j-1] : 0);
      DP[i][j] += DP[i-1][j];
      DP[i][j] += (j < k ? DP[i-1][j+1] : 0);
      
      DP[i][j] %= q;
    }
  }
  
  for(int i = 0; i < n; i++) {
    int suma = 0;
    for(int j = 0; j <= k; j++) {
      suma += DP[zapytania[i]][j];
    }
    cout << suma % q << " ";
  }
  
}
