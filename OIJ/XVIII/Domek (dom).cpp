#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    char tab[n][m];
    int lowest[m];
    
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> tab[i][j];
        }
    }
    
    for(int i = n-1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (tab[i][j] == '#') {
                lowest[j] = i;
            }
            if (tab[i][j] == '*') {
                tab[i][j] = '.';
                tab[lowest[j]-1][j] = '*';
                lowest[j] = lowest[j]-1;
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << tab[i][j];
        }
        cout << endl;
    }
}
