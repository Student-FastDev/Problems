#include <iostream>
#include <string> 
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;
    
    int tab[N];
    for(int i = 0; i < N; i++) {
        cin >> tab[i];
    }
    
    int sumyPrefiksoweLewo[N];
    sumyPrefiksoweLewo[0] = tab[0];
    for(int i = 1; i < N; i++) {
        int sumaBack = sumyPrefiksoweLewo[i-1]/2;
        sumyPrefiksoweLewo[i] = sumaBack + tab[i];
    }
    
    int sumyPrefiksowePrawo[N];
    sumyPrefiksowePrawo[N-1] = tab[N-1];
    for(int i = N-2; i >= 0; i--) {
        int sumaBack = sumyPrefiksowePrawo[i+1]/2;
        sumyPrefiksowePrawo[i] = sumaBack + tab[i]; 
    }
    
    int maksStos = -1;
    for(int i = 0; i < N; i++) {
        int sumaStos;
        if(i == 0) {
            sumaStos = sumyPrefiksoweLewo[0] + sumyPrefiksowePrawo[N - (N) + 1] / 2;
        }
        else if(i == N-1) {
            sumaStos = sumyPrefiksoweLewo[i - 1] / 2 + sumyPrefiksowePrawo[N-1];
        }
        else {
            sumaStos = sumyPrefiksoweLewo[i - 1] / 2 + sumyPrefiksowePrawo[N - (N-i) + 1] / 2 + tab[i];
        }
        if(sumaStos > maksStos) {
            maksStos = sumaStos;
        }
    }
    
    cout << maksStos;
    
}
