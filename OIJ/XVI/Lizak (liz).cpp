#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int N;
    cin >> N;
    int tab[N];
    unordered_map<int, int> liczbaSmakow;

    for(int i = 0; i < N; i++) {
        cin >> tab[i];
    }
    int ogon = 0;
    long long minVal = 213712312317237;
    bool minFound = false;
    
    
    for(int glowa = 0; glowa < N; glowa++) {
        liczbaSmakow[tab[glowa]]++;
        
        if(liczbaSmakow[tab[glowa]] == 3) {
            minFound = true;
            while(liczbaSmakow[tab[glowa]] > 2 && ogon <= glowa) {
                liczbaSmakow[tab[ogon]]--;
                ogon++;
            }
            
            if(glowa - ogon + 2 < minVal) {
                minVal = glowa - ogon + 2;
            }
        }
    }

    if(minFound){
        cout << minVal;
    }
    else {
        cout << "NIE";
    }

    return 0;
}
