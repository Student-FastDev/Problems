#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_INT = 300000;
int mapArray[MAX_INT];
int skoki[MAX_INT];
int f[MAX_INT];

int main()
{
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> mapArray[i];
    }
    
    int f[n];
    f[0] = 0;
    f[1] = 1;
    int index = 1;
    while(f[index] < n) {
        index++;
        f[index] = f[index-1] + f[index-2];
    }
    
    for(int i = 0; i <= n; i++) {
        skoki[i] = n + 1;
    }
    if(mapArray[0] == 0) {
        skoki[0] = 0;
    }
    for(int i = 1; i <= n; i++) {
        if(mapArray[i] == 0) {
            for(int j = 1; j <= index; j++) {
                if(i - f[j] >= 0) {
                    skoki[i] = min(skoki[i], skoki[i-f[j]] + 1);
                }
            }
        }
    }
    
    int wynik = -1;
    if(skoki[n] <= n) {
        wynik = skoki[n];
    }
    cout << wynik;
    
    return 0;
}
