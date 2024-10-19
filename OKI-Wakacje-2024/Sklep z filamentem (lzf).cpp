#include <iostream>
#include <map>

using namespace std;

struct filamentVar {
    int price;
    bool available;
    string color;
};

int main()
{
    int N;
    cin >> N;
    
    map<string, filamentVar> filamentStorage;
    
    for(int i = 0; i < N; i++) {
        string filamentName;
        int filamentPrice;
        bool filamentAvailable;
        string filamentColor;
        
        cin >> filamentName >> filamentPrice >> filamentAvailable >> filamentColor;
        
        filamentVar tempFilament;
        tempFilament.price = filamentPrice;
        tempFilament.available = filamentAvailable;
        tempFilament.color = filamentColor;
        
        filamentStorage[filamentName] = tempFilament;
    }
    
    int M;
    cin >> M;
    
    for(int i = 0; i < M; i++) {
        string Q;
        cin >> Q;
        
        if (filamentStorage.count(Q) == 1) {
            if(filamentStorage[Q].available) {
                cout << "Nazwa: " << Q << endl;
                cout << "Kolor: " << filamentStorage[Q].color << endl;
                cout << "Cena: " << filamentStorage[Q].price << endl;
            } else {
                cout << "Produkt ktorego szukasz jest niedostepny" << endl;
            }
        } else {
            cout << "Produkt ktorego szukasz nie istnieje" << endl;
        }
    }
    return 0;
}